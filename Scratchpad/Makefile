.PHONY: all clean

all: scratchpad.exe

%.exe : %.o
	$(CXX) $< -o $@

clean:
	$(RM) *.exe
