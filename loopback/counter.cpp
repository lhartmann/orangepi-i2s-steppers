#include <stdint.h>
#include <unistd.h>

int main() {
	uint32_t buff[128], n=0;
	while (true) {
		buff[0] = 0x11223344;
		for (uint32_t i=1; i<128; ++i) buff[i] = n++;
		write(STDOUT_FILENO, buff, sizeof(buff));
	}
	return 0;
}
