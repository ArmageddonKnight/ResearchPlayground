obj-m += procfs2.o 


.PHONY: all clean module

all: module procfs2_user_space.exe

procfs2_user_space.exe: procfs2_user_space.o
	$(CXX) $< -o $@

module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
 
clean: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
