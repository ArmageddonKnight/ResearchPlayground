.PHONY: all clean

all: main.cpp.exe main.c.exe

LDFLAGS := -L/usr/lib/x86_64-linux-gnu/ -lpci

%.cpp.exe : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

%.c.exe : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	$(RM) *.exe
