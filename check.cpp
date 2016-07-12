#include <iostream>
#include <iomanip>
#include <stdint.h>

using namespace std;

int main() {
	uint32_t r, c=0;
	while (cin.read((char*)&r, 4)) {
		if (r & 2) {
			cout << c << endl;
			c = 0;
		}
	}
	return 0;
}
