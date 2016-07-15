#include <cstring>
#include <stdint.h>
#include <unistd.h>

using namespace std;

inline uint32_t step(uint32_t x) {
	static uint32_t y=0, div=1;
	y++;
	div--;
	if (!div) {
		div = 192000;
		x = y-x;
		write(STDERR_FILENO, &x, sizeof(uint32_t));
		x = 0x55AA55AA;
		write(STDERR_FILENO, &x, sizeof(uint32_t));
	}
	return y;
}

int main() {
	uint32_t buff[1024];
	
	// Byte offset fixer
	memset(buff, 0, sizeof(buff));
	for (int i=0; i<100; ++i)
		write(STDOUT_FILENO, buff, sizeof(buff));
	read(STDIN_FILENO, buff, sizeof(buff));
	memset(buff, 0xFF, sizeof(buff));
	for (int i=0; i<100; ++i)
		write(STDOUT_FILENO, buff, sizeof(buff));
	if (true) {
		uint32_t w;
		do read(STDIN_FILENO, &w, sizeof(w)); while ( w); // Remove garbage
		do read(STDIN_FILENO, &w, sizeof(w)); while (!w); // Remove zeroed buffers
		switch (w) {
			case 0x000000FFU: read(STDIN_FILENO, &w, 3); break;
			case 0x0000FFFFU: read(STDIN_FILENO, &w, 2); break;
			case 0x00FFFFFFU: read(STDIN_FILENO, &w, 1); break;
			case 0xFFFFFFFFU: break;
			default:
				write(STDERR_FILENO, &w, sizeof(w));
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
