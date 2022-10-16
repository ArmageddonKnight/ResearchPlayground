.PHONY: all clean

ALL_SRCS := $(wildcard *.cpp)
ALL_EXES := $(ALL_SRCS:.cpp=.exe)

CXXFLAGS := -Wall -Werror -std=c++14 -I./dmlc-core/include

all: $(ALL_EXES)

%.exe: %.cpp Makefile common_utilities.h
	$(CXX) $(CXXFLAGS) $< -o $@ 

clean:
	$(RM) *.exe
