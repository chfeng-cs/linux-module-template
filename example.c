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


static int __init krping_init(void)
{
	DEBUG_LOG("example_mod_start\n");
	return 0;
}



static void __exit krping_exit(void)
{
	DEBUG_LOG("example_mod_exit\n");
}

module_init(krping_init);
module_exit(krping_exit);
