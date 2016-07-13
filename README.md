# orangepi-i2s-steppers

This code demonstrates a technique for realtime 32-bit parallel outputs on any Single Board Computer with an I2S output.

I2S is a digital high quality sound output, and uses signals extremely similar to SPI or plain simple shift registers. It is designed to transport audio data, but bits are bits... So here I hooked up 4 serial-in paralllel-out shift registers to the I2S signals, fixed some phase shifting by software, and got a 32 bit parallel port updated at 192kHz. This should be more than enough to run a 3D printer or CNC machine without any additional microcontrollers.

For discussion check: http://forums.reprap.org/read.php?2,685993
For the custom shifter PCB check: https://github.com/lhartmann/esp8266_reprap
For a video check: https://www.youtube.com/watch?v=BX-CLXqmRqE
