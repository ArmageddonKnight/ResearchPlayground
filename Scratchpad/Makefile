.PHONY: all clean

CXXFLAGS := -I./quik_fix/include

all: main.cpp.exe main.c.exe

%.cpp.exe : %.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	$(RM) *.exe
