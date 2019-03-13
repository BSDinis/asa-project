CC := g++
VPATH := .:network
INCLUDES := -I. -Inetwork
CXXFLAGS := -Wall -Werror -g -fdiagnostics-color=always $(INCLUDES)
LDFLAGS := -Wall -Werror -fdiagnostics-color=always $(INCLUDES) -L. -L../../graph -L../../network

SOURCES=$(wildcard *.cpp) network.cpp net_algs.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET =solver

LOGFILE=tests.log

all: $(TARGET)

$(TARGET): $(OBJECTS)

log_test:
	date >> tests.log
	VERSION="$(shell cat tests.log | wc -l)"
	echo $(VERSION)

test: log_test $(TARGET)
	./network_generator.py | tee test$(shell cat tests.log | wc -l).in | ./$(TARGET) | tee test$(shell cat tests.log | wc -l).out ; cat test$(shell cat tests.log | wc -l).in


.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET) vgcore*

.PHONY: depend
depend: $(SOURCES)
	$(CC) $(INCLUDES) -MM $(SOURCES) > autodep
	@echo $(SOURCES)
