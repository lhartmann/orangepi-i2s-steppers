#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdint.h>
#include <unistd.h>

using namespace std;

void full_write(int fd, void *p, size_t sz) {
	size_t s = 0;
	while (s < sz) s += write(fd, (uint8_t*)p+s, sz-s);
}
void full_read(int fd, void *p, size_t sz) {
	size_t s = 0;
	while (s < sz) s += read(fd, (uint8_t*)p+s, sz-s);
}

#define NOT_FOUND uint32_t(~0ULL)
uint32_t find_tag(uint8_t *p, uint32_t sz) {
	for (uint32_t o=0; o<sz-4; ++o) {
		if (p[o]==0x44 && p[o+1]==0x33 && p[o+2]==0x22 && p[o+3]==0x11)
			return o;
	}
	return NOT_FOUND;
}

int main() {
	union {
		uint8_t b[1];
		uint32_t w[128];
	} buff;
	uint32_t n=0;
	
	full_read(STDIN_FILENO, buff.b, 2);
	while (true) {
		full_read(STDIN_FILENO, buff.b, sizeof(buff));
		uint32_t off = find_tag(buff.b, sizeof(buff));
		if (off == NOT_FOUND) {
			cout << "?" << flush;
			continue;
		}
		if (off) {
			uint32_t validbytes = sizeof(buff)-off;
			memmove(buff.b, buff.b+off, validbytes);
			full_read(STDIN_FILENO, buff.b+validbytes, sizeof(buff)-validbytes);
		}
		
		cout
			<< dec << setw(4) << off << ' ' << hex
			<< setw(8) << buff.w[0] << ' '
			<< setw(8) << buff.w[1] << ' '
			<< setw(8) << buff.w[2] << ' '
			<< setw(8) << buff.w[3] << ' '
			<< setw(8) << buff.w[125] << ' '
			<< setw(8) << buff.w[126] << ' '
			<< setw(8) << buff.w[127] << endl;
		
		continue;
		for (int i=2; i<128; ++i) {
			if (buff.w[i] - buff.w[i-1] != 1) {
				cout << "." << flush;
				break;
			}
		}
	}
	return 0;
}
