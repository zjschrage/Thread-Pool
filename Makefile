CC = g++ --std=c++2a -g -Wall
O = -o threads
DEPS = *.cpp
CPPFLAGS = -Iinclude


all: clean threads

threads:
	$(CC) $(CPPFLAGS) $(O) $(DEPS) 

clean:
	$(RM) threads