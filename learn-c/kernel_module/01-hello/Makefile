obj-m += hello.o

PWD := $(CURDIR)
KERNELVERSION := $(shell uname -r)

all:
	make -C /lib/modules/$(KERNELVERSION)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KERNELVERSION)/build M=$(PWD) clean

.PHONY: clean
