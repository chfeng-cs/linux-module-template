KSRC=/lib/modules/`uname -r`/build
KOBJ=/lib/modules/`uname -r`/build
module_name=example_mod
obj-m += ${module_name}.o
${module_name}-y			:=  example.o


default:
	make -C $(KSRC) M=`pwd` modules

install:
	@# make -C $(KSRC) M=`pwd` modules_install
	@# depmod -a
	@sudo dmesg -C
	sudo insmod ${module_name}.ko
	@dmesg

clean:
	make -C $(KSRC) M=`pwd` clean

remove:
	@sudo dmesg -C
	sudo rmmod ${module_name}
	@dmesg
