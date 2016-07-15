#! /bin/bash

# Single process I2S Input and Output: not working yet.
# ./arecord | ./loopback | ./aplay

# One process input, one process output
#  Start writeron the backgroud
./counter | ./aplay &
#  and reader on the foreground
./arecord | ./counter_in 
#  Kills the writer when reader is exitted.
kill `pidof counter`
kill `pidof aplay`
