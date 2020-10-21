#include <linux/version.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
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

#include "debug.h"

static LIST_HEAD(krping_cbs);

MODULE_AUTHOR("Chuanheng Feng");
MODULE_DESCRIPTION("Example Module");
MODULE_LICENSE("Dual BSD/GPL");

// wait_queue_head_t my_queue;
// init_waitqueue_head(&my_queue);
DECLARE_WAIT_QUEUE_HEAD(my_queue);

// void* tsk;
// DECLARE_WAITQUEUE(q1,tsk);

static int __init krping_init(void)
{
	// add_wait_queue();
	printk(KERN_ERR PFX "Invalid Parameter");
	DEBUG_LOG("example_mod_start\n");
	return 0;
}


static void __exit krping_exit(void)
{
	DEBUG_LOG("example_mod_exit\n");
}

module_init(krping_init);
module_exit(krping_exit);
