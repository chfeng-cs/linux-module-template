PAGE_SHIFT 12
PAGE_SIZE  2^(PAGE_SHIFT)=2^12=4096=0x000000001 000
                                    0x558a02a0e 000
PAGE_MASK		(~(PAGE_SIZE-1))
                 ~(0x000000000 FFF)
                   0xFFFFFFFFF 000

pfn 页帧号 内核会将所有struct page* 放到一个全局数组（mem_map）中，而内核中我们常会看到pfn，说得就是页帧号，也就是数组的index


