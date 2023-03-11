.PHONY: all clean

CXXFLAGS := -I./quik_fix/include

all: a.exe

a.exe : main.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	$(RM) *.exe
