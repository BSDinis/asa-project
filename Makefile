CC := g++
VPATH := .:network
INCLUDES := -I. -Inetwork
CXXFLAGS := -O3 --std=c++11 -Wall -Werror -g -fdiagnostics-color=always $(INCLUDES)
LDFLAGS := -Wall -Werror -fdiagnostics-color=always $(INCLUDES) -L. -L../../graph -L../../network

SOURCES=$(wildcard *.cpp) network.cpp net_algs.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET =solver

LOGFILE=tests.log

all: $(TARGET)

$(TARGET): $(OBJECTS)

test: $(TARGET)
	@date >> tests.log
	./network_generator.py | tee test$(shell cat tests.log | wc -l).in | ./$(TARGET) | tee test$(shell cat tests.log | wc -l).out ;# cat test$(shell cat tests.log | wc -l).in

correctness: $(TARGET)
	@for input in test0*.in ; do \
	  ./$(TARGET) < $$input > $${input%.in}.outhyp ; \
	  echo "./$(TARGET) < $$input > $${input%.in}.outhyp" ; \
	  done
	@for output in test0*.out ; do \
	  diff $$output $${output%.out}.outhyp ; \
	  done


.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET) vgcore* *outhyp

.PHONY: depend
depend: $(SOURCES)
	$(CC) $(INCLUDES) -MM $(SOURCES) > autodep
	@echo $(SOURCES)
