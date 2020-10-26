KSRC=/lib/modules/`uname -r`/build
KOBJ=/lib/modules/`uname -r`/build

# Supress warngings of unused_function and unused_variable.
EXTRA_CFLAGS+=-Wno-unused-function
EXTRA_CFLAGS+=-Wno-unused-variable
# # Supress warning of format.
# EXTRA_CFLAGS+=-Wno-format

module_name=example_mod
obj-m += ${module_name}.o
${module_name}-y			:=  example.o


compile:
	make -C $(KSRC) M=`pwd` modules -s

install: remove
	@# make -C $(KSRC) M=`pwd` modules_install
	@# depmod -a
	@sudo dmesg -C
	@sudo insmod ${module_name}.ko
	@dmesg -e

clean:
	make -C $(KSRC) M=`pwd` clean

remove:
	@ if [ `lsmod | grep $(module_name) | wc -l` != 0 ]; then\
		sudo dmesg -C;\
		sudo rmmod ${module_name};\
		dmesg -e;\
		echo -----Remove installed ${module_name}.----- ;\
	fi

all: compile install
