CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES=cache-sim.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cache-sim

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE) *.stackdump output.txt
