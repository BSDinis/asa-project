CC := g++
VPATH := .:../../graph
INCLUDES := -I. -I../../graph
CXXFLAGS := -Wall -Werror -g -fdiagnostics-color=always $(INCLUDES)
LDFLAGS := -Wall -Werror -fdiagnostics-color=always $(INCLUDES) -L. -L../../graph

SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp:.o)
TARGET  := basic_func


all: $(TARGET)

$(TARGET): $(OBJECTS)  graph.hpp

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET) vgcore*

.PHONY: depend
depend: $(SOURCES)
	$(CC) $(INCLUDES) -MM $(SOURCES) > autodep
	@echo $(SOURCES)
