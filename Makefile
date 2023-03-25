CC = g++ --std=c++2a -g -Wall
O = -o threads
CPPFLAGS = -Iinclude
DEPS = *.cpp



all: clean threads

threads:
	$(CC) $(CPPFLAGS) $(O) $(DEPS) 

clean:
	$(RM) threads