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


static void mtest_list_vma(void)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	down_read(&mm->mmap_sem);
	DEBUG_LOG("list_vma");
	for (vma=mm->mmap; vma; vma=vma->vm_next) {
		char property[4] = {0};
		if (vma->vm_flags & VM_READ) {
			property[0] = 'r';
		} else {
			property[0] = '-';
		}
		if (vma->vm_flags & VM_WRITE) {
			property[1] = 'w';
		} else {
			property[1] = '-';
		}
		if (vma->vm_flags & VM_EXEC) {
			property[2] = 'x';
		} else {
			property[2] = '-';
		}
		// print_value(vma, 0x%p);
		printk("VMA 0x%lx-0x%lx %s", vma->vm_start, vma->vm_end, property);
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
	mtest_list_vma();
	return len;
}
struct file_operations proc_fp = {
	.write = proc_write,
};
struct proc_dir_entry *entry;
static int __init krping_init(void)
{
	// add_wait_queue();
	// printk(KERN_ERR PFX "Invalid Parameter");
	entry = proc_create("chfeng", 0666, NULL, &proc_fp);
	if (entry == NULL) {
		DEBUG_LOG("Create failed.");
	}
	mtest_list_vma();
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
