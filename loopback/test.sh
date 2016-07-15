#! /bin/bash

# Single process I2S Input and Output: not working yet.
# ./arecord | ./loopback | ./aplay

# One process input, one process output
#  Start writeron the backgroud
./writer | ./aplay &
#  and reader on the foreground
./arecord | ./reader 
#  Kills the writer when reader is exitted.
kill `pidof writer`
kill `pidof aplay`
