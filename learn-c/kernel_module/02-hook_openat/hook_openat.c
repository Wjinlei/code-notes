#include "khook/engine.c"

#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jerry Wang <freebufer.wang@gmail.com>");
MODULE_DESCRIPTION("Hello World");
MODULE_VERSION("0.1");

// long sys_kill(const struct pt_regs *regs) -- modern kernels
KHOOK_EXT(long, __x64_sys_openat, const struct pt_regs*);
static long khook___x64_sys_openat(const struct pt_regs* regs)
{
        pr_info("Hello World\n");
        return KHOOK_ORIGIN(__x64_sys_openat, regs);
}

int init_module(void)
{
        return khook_init();
}

void cleanup_module(void)
{
        khook_cleanup();
}
