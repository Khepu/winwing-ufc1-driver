obj-m += winwing_ufc1_devdrv.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
install:
	sudo insmod ./winwing_ufc1_devdrv.ko
uninstall:
	sudo rmmod winwing_ufc1_devdrv
