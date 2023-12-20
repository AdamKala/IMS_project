all: build

build:
	g++ -g -O2 -std=c++11 -lsimlib -lm main.cpp data.cpp generator.cpp visitor.cpp -o ims

run:
	./ims -w

clean:
	rm -f ims