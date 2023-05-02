.PHONY: all clean

CXXFLAGS := -I./quik_fix/include -std=c++11

all: a.exe

a.exe : main.cpp \
./quik_fix/include/quik_fix/logging.h \
quik_fix/include/quik_fix/logging.h \
Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	$(RM) *.exe
