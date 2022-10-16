.PHONY: all clean

ALL_SRCS := $(wildcard *.cpp)
ALL_EXES := $(ALL_SRCS:.cpp=.exe)

CXXFLAGS := -Wall -Werror -std=c++14

all: $(ALL_EXES)

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ 

clean:
	$(RM) *.exe
