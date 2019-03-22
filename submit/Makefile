CC := g++
INCLUDES := -I.
CXXFLAGS := -O3 --std=c++11 -Wall -Werror -g -fdiagnostics-color=always $(INCLUDES)
LDFLAGS := -Wall -Werror -fdiagnostics-color=always $(INCLUDES) -L.

SOURCES=solver.cpp net_algs.cpp network.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET = solver

all: $(TARGET)
$(TARGET): $(OBJECTS)

correctness: $(TARGET)
	@for input in ../test0*.in ; do \
	  ./$(TARGET) < $$input > $${input%.in}.outhyp ; \
	  echo "./$(TARGET) < $$input > $${input%.in}.outhyp" ; \
	  done
	@for output in ../test0*.out ; do \
	  diff $$output $${output%.out}.outhyp ; \
	  done


.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET) vgcore* *outhyp

.PHONY: depend
depend: $(SOURCES)
	$(CC) $(INCLUDES) -MM $(SOURCES) > autodep
	@echo $(SOURCES)
