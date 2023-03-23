CC = g++ --std=c++2a -g -Wall
O = -o threads
DEPS = *.cpp

all: clean threads

threads:
	$(CC) $(O) $(DEPS)

clean:
	$(RM) threads