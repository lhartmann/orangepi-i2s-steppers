#include <unistd.h>
#include <stdint.h>

#include "stepper.h"
#include "throttle.h"
#include "maskedtransportdelay.h"

#define RATE       192000 // Sample rate
#define MAXSPD   (32*1000) // Max Speed, steps/s
#define MOVE    (5*MAXSPD) // Move distance, steps
#define ACCEL     (2*RATE) // Ramp up/down duration, samples

#define STEP_MASK 0x00000001U
#define DIR_MASK  0x00010000U
#define NUM_STEPPERS 4

uint32_t forward = 0;
Throttle throttle;
Stepper  stepper[NUM_STEPPERS];
MaskedTransportDelay<uint32_t, 1, 0x7FFFFFFFU> td;

uint32_t step() {
	uint32_t out = 0;
	
	// If motion has completed, prepare new move
	bool done = throttle.done();
	for (int s=0; s<NUM_STEPPERS; ++s) done = done && stepper[s].done();
	
	if (done) {
		// Reverse direction
		if (++forward == 16) forward = 0;
		
		// Move Duration (samples), considering max-speed.
		// Beware of this expression, RATE*MOVE may overflow.
		uint32_t duration = RATE * 1. * MOVE/MAXSPD;
		
		// Prepare the speed controllers
		for (int s=0; s<NUM_STEPPERS; ++s)
			stepper[s].prepare(MOVE/(s+1), duration);
		
		// Prepare the acceleration controller
		throttle.prepare(duration, ACCEL, ACCEL/100, ACCEL/100);
	}
	
	// Render movement
	out += forward*DIR_MASK;
	if (throttle.step()) {
		for (int s=0; s<NUM_STEPPERS; ++s) {
			if (stepper[s].step()) {
				out |= STEP_MASK<<s;
			}
		}
	}
	
	// Encode for I2S output:
	//   Apply selective transport delay (31 LSBs delayed by 1 clock)
	out = td(out);
	//   Fix word clock phase by shifting bits around.
	//   Hardware will delay 1 MSB by 1 clock, resyncing the word.
	out = (out<<1) | (out>>31); 
	
	return out;
}

int main() {
	uint32_t buff[1024];
	while (true) {
		for (uint32_t i=0; i<1024; ++i) {
			buff[i] = step();
		}
		write(STDOUT_FILENO, buff, sizeof(buff));
	}
}
