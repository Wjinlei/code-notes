#include "khook/engine.c"

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jerry Wang <freebufer.wang@gmail.com>");
MODULE_DESCRIPTION("Hello World");
MODULE_VERSION("0.1");

static char* duplicate_filename(const char __user* filename)
{
        char* kernel_filename;
        kernel_filename = kmalloc(4096, GFP_KERNEL);
        if (!kernel_filename) {
                return NULL;
        }
        if (strncpy_from_user(kernel_filename, filename, 4096) < 0) {
                kfree(kernel_filename);
                return NULL;
        }
        return kernel_filename;
}

// hook openat reject create testfile
KHOOK_EXT(long, __x64_sys_openat, const struct pt_regs*);
static long khook___x64_sys_openat(const struct pt_regs* regs)
{
        char* kernel_filename;
        kernel_filename = duplicate_filename((char*)regs->si);
        if (strcmp(kernel_filename, "testfile") == 0) {
                pr_info("hook: %d %s\n", current->pid, kernel_filename);
                kfree(kernel_filename);
                return 0;
        }
        kfree(kernel_filename);
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
