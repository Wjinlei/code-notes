#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jerry Wang <freebufer.wang@gmail.com>");
MODULE_DESCRIPTION("Hello World");
MODULE_VERSION("0.1");

static int _init_module(void)
{
        pr_info("Hello World!\n");
        return 0;
}

static void _exit_module(void)
{
        return;
}

module_init(_init_module);
module_exit(_exit_module);
