#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#include "khook/engine.c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jerry Wang <freebufer.wang@gmail.com>");
MODULE_DESCRIPTION("Hook openat demo");
MODULE_VERSION("0.1");

/* hook openat reject create testfile */
KHOOK_EXT(long, __x64_sys_openat, const struct pt_regs*);
static long khook___x64_sys_openat(const struct pt_regs* regs)
{
        char kernel_filename[2048];
        if (strncpy_from_user(kernel_filename, (char*)regs->si, 2048) > 0) {
                if (strcmp(kernel_filename, "testfile") == 0) {
                        pr_info("Hook openat: [%d] %s -> %s\n", current->pid, current->comm, kernel_filename);
                        return -1;
                }
        }
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
