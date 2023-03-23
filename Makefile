CC = g++ --std=c++2a -g -Wall
G_INC = -Iinclude $(CPPFLAGS)
O = -o threads
DEPS = *.cpp

all: clean threads

threads:
	$(CC) $(G_INC) $(O) $(DEPS)

clean:
	$(RM) threads