#include <linux/version.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/parser.h>
#include <linux/list.h>
#include <linux/device.h>
#include <linux/time.h>
#include <linux/random.h>
#include <linux/sched/signal.h>
#include <linux/proc_fs.h>
#include <linux/mm.h>

#include "debug.h"

static LIST_HEAD(krping_cbs);

MODULE_AUTHOR("Chuanheng Feng");
MODULE_DESCRIPTION("Example Module");
MODULE_LICENSE("Dual BSD/GPL");


static void mtest_list_vma(struct task_struct *task)
{
	struct mm_struct *mm;
	struct vm_area_struct *vma;
	int i = 0;
	char property[4] = "---";
	if (task == NULL) {
		task = current;
	}
	mm = task->mm;
	down_read(&mm->mmap_sem);
	DEBUG_LOG("list_vma");
	for (vma=mm->mmap; vma; vma=vma->vm_next, i++) {
		if (vma->vm_flags & VM_READ) {
			property[0] = 'r';
		}
		if (vma->vm_flags & VM_WRITE) {
			property[1] = 'w';
		}
		if (vma->vm_flags & VM_EXEC) {
			property[2] = 'x';
		}
		// printk("VMA 0x%lx-0x%lx %s", vma->vm_start, vma->vm_end, property);
		if ( i == 10) break;
	}
	if (vma != NULL) {
		DEBUG_LOG("VMA 0x%lx-0x%lx %s", vma->vm_start, vma->vm_end, property);
	} else {
		DEBUG_LOG("end");
	}
	up_read(&mm->mmap_sem);
}
static void mtest_list_vma111(void)
{
	struct task_struct *mc = current;
	struct mm_struct *mm = mc->mm;
	pgd_t *pgd = mm -> pgd;
	PRINT_MACRO(PTE_SHIFT);
	PRINT_MACRO(PGDIR_SHIFT);
	PRINT_MACRO(PTRS_PER_PGD);
	DEBUG_LOG("name: %s", mc->comm);
	DEBUG_LOG("pgd_t: %p", pgd);
	// pgd_offset
	// pgd_none
	// pgd_bad
	// p4d_offset
	// pud_offset
	// page_to_phys
	PRINT_MACRO(PAGE_MASK);
	PRINT_MACRO(P4D_SHIFT);
	PRINT_MACRO(PTRS_PER_P4D);
	// DEBUG_LOG("0x%p\n", mc);
	DEBUG_LOG("pid: %d", mc->pid);
	// DEBUG_LOG("files: %p", mc->files);
} 

ssize_t proc_write (struct file *f, const char __user *user_buff, size_t len, loff_t * offset) {
	char buf[100];
	copy_from_user(buf, user_buff, len);
	buf[len] = 0;
	print_value(buf, %s);
	print_value(len, %u);
	print_value(*offset, %u);
	return len;
}
struct file_operations proc_fp = {
	.write = proc_write,
};
struct proc_dir_entry *entry;
static int __init krping_init(void)
{
	struct task_struct *p;
	for_each_process(p) {
		if (p->pid == 10986) {
			DEBUG_LOG("addr: 0x%p\tpid: %-5d\tname: %s", p, p->pid, p->comm);
			break;
		}
	}
	entry = proc_create("chfeng", 0666, NULL, &proc_fp);
	if (entry == NULL) {
		DEBUG_LOG("Create failed.");
	}
	mtest_list_vma(p);
	DEBUG_LOG("example_mod_start\n");
	return 0;
}


static void __exit krping_exit(void)
{
	proc_remove(entry);
	DEBUG_LOG("example_mod_exit\n");
}

module_init(krping_init);
module_exit(krping_exit);
