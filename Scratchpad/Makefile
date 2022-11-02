.PHONY: all clean

all: main.exe

%.exe : %.o
	$(CXX) $< -o $@

clean:
	$(RM) *.exe
