#include <stdint.h>
#include <unistd.h>

void full_write(int fd, void *p, size_t sz) {
	size_t s = 0;
	while (s < sz) s += write(fd, (uint8_t*)p+s, sz-s);
}
void full_read(int fd, void *p, size_t sz) {
	size_t s = 0;
	while (s < sz) s += read(fd, (uint8_t*)p+s, sz-s);
}

int main() {
	uint32_t buff[128], n=0;
	while (true) {
		buff[0] = 0x11223344;
		for (uint32_t i=1; i<128; ++i) buff[i] = n++;
		full_write(STDOUT_FILENO, buff, sizeof(buff));
	}
	return 0;
}
