
CPPUTEST_HOME = /home/ladislavondris/cpputest
SRC_HOME = /home/ladislavondris/projects/C-data-structures
TESTS_DIR = tests

CPPFLAGS += -I$(CPPUTEST_HOME)/include -I$(SRC_HOME)
CXXFLAGS += "" # -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -std=c++11 -Wall -Wextra -pedantic -g 
TEST_CLAGS = "" # -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h

TEST_FLAGS = $(CPPFLAGS)
TEST_FLAGS += $(CXXFLAGS)
TEST_FLAGS += $(TEST_CFLAGS)

LD_LIBRARIES = -L$(CPPUTEST_HOME)/cpputest_build/lib -lCppUTest -lCppUTestExt
CC = g++

TEST_SRCS = $(wildcard tests/*.c) # Find all test files
SRCS = $(filter-out main.c, $(wildcard *.c)) # Find all source files, except main
TEST_OBJS := $(patsubst %.c, %.o, $(TEST_SRCS)) # Convert test .c files to .o files 
SRC_OBJS := $(patsubst %.c, %.o, $(SRCS)) # Convert source .c files to .o files

.PHONY: main test clean

main: $(SRC_OBJS) main.o
	$(eval TEST_FLAGS = "")
	$(CC) $(CFLAGS) -o $@ $^ 

test: $(TEST_OBJS) $(SRC_OBJS)
	$(CC) $(CFLAGS) $(TESTFLAGS) -o $@ $^ $(LD_LIBRARIES)

%.o: %.c %.h
	$(CC) $(CFLAGS) $(TESTFLAGS) -c $< -o $@

clean:
	rm -rf tests/*.o
	rm -rf *.o
	rm -rf test
	rm -rg main

