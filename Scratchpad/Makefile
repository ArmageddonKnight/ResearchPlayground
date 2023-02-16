.PHONY: all clean

CXXFLAGS := -rdynamic

all: main.cpp.exe main.c.exe

%.cpp.exe : %.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

%.c.exe : %.c Makefile
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	$(RM) *.exe
