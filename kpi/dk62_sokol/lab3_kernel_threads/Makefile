# based on https://linux.die.net/lkmpg/hello2.html by Peter Jay Salzman
# (!) using paths with spaces may not work with Kbuild

# this is what is used by Kbuild
obj-m += src/firstmod.o

obj-n += src/firstmod.ko

# directory containing Makefile for kernel build
KBUILDDIR := /lib/modules/$(shell uname -r)/build/

.PHONY: modules clean tidy run
all: build run
build: clean modules
run: run1 run2 run3

# recur to the original kernel Makefile with some additions
modules:
	$(MAKE) -C "$(KBUILDDIR)" M="$(PWD)" modules

tidy:
	$(MAKE) -C "$(KBUILDDIR)" M="$(PWD)" clean

# we link original clean to target named tidy
clean:
	-rm -f modules.order Module.symvers
	-rm -rf .tmp_versions
	-rm -f $(obj-m) $(obj-m:.o=.mod.o) $(obj-m:.o=.mod.c)
	-rm -f $(addsuffix .cmd,$(addprefix .,$(obj-m)))
	-rm -f $(addsuffix .cmd,$(addprefix .,$(obj-m:.o=.ko)))
	-rm -f $(addsuffix .cmd,$(addprefix .,$(obj-m:.o=.mod.o)))


run1:
	sudo insmod $(obj-n)
run2:
	sudo dmesg -k | tail -30
run3:
	sudo rmmod $(obj-n)



