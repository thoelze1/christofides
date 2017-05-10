CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES=eulerCircuit.cpp graph.cpp matching.cpp mst.cpp multigraph.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=christofides

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE) *.stackdump
