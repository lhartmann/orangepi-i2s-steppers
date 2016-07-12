#! /bin/bash

g++ cnt.cpp -o cnt && ./cnt \
| aplay \
	-D hw:CARD=snddaudio,DEV=0 \
	-r 192000 \
	-c 2 \
	-f S16_LE \
	--disable-resample \
	--disable-channels \
	--disable-format \
	--disable-softvol
