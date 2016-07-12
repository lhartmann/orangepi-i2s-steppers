#include <iostream>
#include <iomanip>
#include <stdint.h>
#include "throttle.h"

using namespace std;

int main() {
	Throttle t;
	t.prepare(100, 40, 5, 5);
	for (int i=0; i<200; ++i) {
		cout
			<< i << " "
			<< (t.step() ? "STEP " : "     ")
			<< (t.done() ? "DONE " : "     ")
			<< t.acc << " "
			<< t.r << " "
			<< endl;
	}
	return 0;
}
