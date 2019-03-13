CC := g++
VPATH := .:../../network
INCLUDES := -I. -I../../network
CXXFLAGS := -Wall -Werror -g -fdiagnostics-color=always $(INCLUDES)
LDFLAGS := -Wall -Werror -fdiagnostics-color=always $(INCLUDES) -L. -L../../graph

SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp:.o)
TARGET  := net_basic_func


all: $(TARGET)

$(TARGET): $(OBJECTS) network.hpp

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET) vgcore*

.PHONY: depend
depend: $(SOURCES)
	$(CC) $(INCLUDES) -MM $(SOURCES) > autodep
	@echo $(SOURCES)
