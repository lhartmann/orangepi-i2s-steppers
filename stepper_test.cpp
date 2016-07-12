#include <iostream>
#include <iomanip>
#include <stdint.h>
#include "stepper.h"

using namespace std;

int main() {
	Stepper s;
	s.prepare(10,100);
	for (int i=0; i<120; ++i) {
		cout
			<< i << " "
			<< (s.step() ? "STEP " : "     ")
			<< (s.done() ? "DONE " : "     ")
			<< endl;
	}
	return 0;
}
