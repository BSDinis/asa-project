CC := g++
VPATH := .:network
INCLUDES := -I. -Inetwork
CXXFLAGS := -Wall -Werror -g -fdiagnostics-color=always $(INCLUDES)
LDFLAGS := -Wall -Werror -fdiagnostics-color=always $(INCLUDES) -L. -L../../graph -L../../network

SOURCES=$(wildcard *.cpp) network.cpp net_algs.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET =solver


all: $(TARGET)

$(TARGET): $(OBJECTS)

test: $(TARGET)
	./network_generator.py | tee trace | ./$(TARGET) ; cat trace ; rm trace


.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET) vgcore*

.PHONY: depend
depend: $(SOURCES)
	$(CC) $(INCLUDES) -MM $(SOURCES) > autodep
	@echo $(SOURCES)
