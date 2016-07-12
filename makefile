all: cnt check stepper_test throttle_test

clean:
	rm -f cnt check stepper_test throttle_test

cnt: cnt.cpp *.h
	g++ -o cnt cnt.cpp

stepper_test: stepper_test.cpp stepper.h
	g++ -o stepper_test stepper_test.cpp

throttle_test: throttle_test.cpp throttle.h
	g++ -o throttle_test throttle_test.cpp
