obj-m += simple_chrdev.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load:
	sudo insmod simple_chrdev.ko
	sudo dmesg -c

unload:
	sudo rmmod simple_chrdev.ko
	sudo dmesg -c
