PAGE_SHIFT 12
PAGE_SIZE  2^(PAGE_SHIFT)=2^12=4096=0x000000001 000
                                    0x558a02a0e 000
PAGE_MASK		(~(PAGE_SIZE-1))
                 ~(0x000000000 FFF)
                   0xFFFFFFFFF 000

pfn 页帧号 内核会将所有struct page* 放到一个全局数组（mem_map）中，而内核中我们常会看到pfn，说得就是页帧号，也就是数组的index

--------------------------

一个task_strcut有一个mm_struct(mm),一个mm_struct有多个vm_area_struct(mmap),通过双链表的形式组织起来,双链表的第一个节点的pre和最后一个节点的next都是NULL

每个vm_area_struct有start和end 都是虚拟地址.
每个vm_area_struct有一个指向mm_struct的指针(vm_mm),是否都是一样的?(后来通过编程发现同一个task_struct的每一个vm_area_struct的vm_mm都是指向那个mm_struct,即一个mm_struct代表一个地址空间)

通过mm_struct和address获取pgd
pgd_offset_pgd((mm)->pgd, (address))

address and mm_struct(虚拟地址与其地址空间)
mm_struct有指向pgd的的指针
pgd_offset(mm, addr)
  pgd_offset_pgd((mm)->pgd, (address))
  (mm)->pgd + pgd_index((address))
  (mm)->pgd + ((address) >> PGDIR_SHIFT) & (PTRS_PER_PGD - 1)   
  # PGDIR_SHIFT=39=(48-9), PTRS_PER_PGD=512=2^9,因为pgd占前9位


linux kernel中每个指针自增运算很奇怪
-------------------------
spdk 安装
real    0m0.014s
user    0m0.000s
sys     0m0.011s
 05:31:28       $ xtrace_disable
 05:31:28       $ '[' no '!=' yes ']'
 05:31:28       $ PREV_BASH_OPTS=ehxBET
 05:31:28       $ [[ ehxBET == *\x* ]]
 05:31:28       $ XTRACE_DISABLED=yes
 05:31:28       $ set +x
************************************
END TEST unittest_vhost
************************************
 05:31:29       $ xtrace_enable
 05:31:29       $ '[' no = yes ']'
 05:31:29       $ set +x


=====================
All unit tests passed
=====================
WARN: lcov not installed or SPDK built without coverage!
WARN: neither valgrind nor ASAN is enabled!

Valgrind 
发音 well-greened https://www.youtube.com/watch?v=_xZIPB5leCg
Valgrind是一个GPL的软件，用于Linux（For x86, amd64 and ppc32）程序的内存调试和代码剖析。你可以在它的环境中运行你的程序来监视内存的使用情况，比如C 语言中的malloc和free或者 C++中的new和 delete。使用Valgrind的工具包，你可以自动的检测许多内存管理和线程的bug，避免花费太多的时间在bug寻找上，使得你的程序更加稳固。
————————————————
版权声明：本文为CSDN博主「andylauren」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/andylauren/article/details/93189740


spdk 位nvme ssd开发的套件，完全开源，基于BSD lisence
storage virtualization

blob binary large object 二进制大对象 发音 布烙波
SCSI 斯卡sei
iSCSI i 斯卡sei
RAID 发音 red

spdk最成熟的：用户态nvme驱动 vhost
ztcp 腾讯云开发的用户态tcp

---------------------------
/dev/dm*设备
dm是device mapper的缩写，


LVM
Logical Volume Manager(逻辑卷管理)的简写

------------------
rmmod 
-f, --force
           This option can be extremely dangerous: it has no effect unless CONFIG_MODULE_FORCE_UNLOAD was set when the kernel was compiled. With this option, you can remove modules which are being used, or which are not
           designed to be removed, or have been marked as unsafe (see lsmod(8)).
只有在编译内核的时候设置CONFIG_MODULE_FORCE_UNLOAD才能强制移除模块
参考：
https://elixir.bootlin.com/linux/v3.2/source/kernel/module.c#L826

