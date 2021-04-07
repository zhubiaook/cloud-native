obj-m := simple_param.o
PWD = $(shell pwd)
KDIR = /lib/modules/`uname -r`/build/

all: default

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
