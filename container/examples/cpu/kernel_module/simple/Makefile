obj-m := simple.o

KDIR := /lib/modules/`uname -r`/build
PWD := `pwd`

all: default
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE)	-C $(KDIR) M=$(PWD) clean
