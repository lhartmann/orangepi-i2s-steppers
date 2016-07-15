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

uint32_t step(uint32_t x) {
	static uint32_t y=0, div=1;
	y++;
	div--;
	if (!div) {
		div = 192000;
		cerr << y-x << endl;
	}
	return y;
}

int main() {
	uint32_t buff[1024];
	
	// Byte offset fixer
	memset(buff, 0, sizeof(buff));
	buff[100] = 0xFFFFFFFF;
	full_write(STDOUT_FILENO, buff, sizeof(buff));
	full_write(STDOUT_FILENO, buff, sizeof(buff));
	full_write(STDOUT_FILENO, buff, sizeof(buff));
	buff[100] = 0;
	full_write(STDOUT_FILENO, buff, sizeof(buff));
	full_write(STDOUT_FILENO, buff, sizeof(buff));
	if (true) {
		uint32_t w;
		do full_read(STDIN_FILENO, &w, sizeof(w)); while ( w); // Remove garbage
		do full_read(STDIN_FILENO, &w, sizeof(w)); while (!w); // Remove zeroed buffers
		switch (w) {
			case 0xFF000000U: read(STDIN_FILENO, &w, 3); break;
			case 0xFFFF0000U: read(STDIN_FILENO, &w, 2); break;
			case 0xFFFFFF00U: read(STDIN_FILENO, &w, 1); break;
			case 0xFFFFFFFFU: break;
			default:
				cerr << hex << w << endl;
				return 1;
		}
	}
	
	while (true) {
		read(STDIN_FILENO, buff, sizeof(buff));
		for (size_t i=0; i<sizeof(buff)/sizeof(uint32_t); ++i) {
			buff[i] = step(buff[i]);
		}
		write(STDOUT_FILENO, buff, sizeof(buff));
	}
	return 0;
}
