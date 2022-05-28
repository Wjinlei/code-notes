/*
 * 关于Linux系统调用
 * 在查阅了很多文章后得出结论: 在现代内核上,系统调用采用寄存器来保存参数
 * 需要注意的是最多6个参数，每个参数对应 struct pt_regs *regs 中的 6 个寄存器，依次为：di、si、dx、r10、r8、r9
 * 你可能会问如果大于6个参数的系统调用呢？对于这个问题，内核维护人员给出的答案是：
 * 如果大于6个参数，那么多出的参数地址会在%ebx中保存，但他也说了，你基本上不会遇到大于6个参数的系统调用
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/types.h>

#include "khook/engine.c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jerry Wang <freebufer.wang@gmail.com>");
MODULE_DESCRIPTION("Hook openat demo");
MODULE_VERSION("0.1");

/* hook openat reject create testfile */
/* openat系统调用原型: int openat(int dirfd, const char *pathname, int flags, mode_t mode); */
KHOOK_EXT(long, __x64_sys_openat, const struct pt_regs*);
static long khook___x64_sys_openat(const struct pt_regs* regs)
{
        char kernel_filename[2048] = { 0 };
        /* copy str from user space */
        if (strncpy_from_user(kernel_filename, (char*)regs->si, 2048) < 0) {
                return -1;
        }
        if (strncmp(kernel_filename, "/dev/null", 9) != 0) {
                if ((O_CREAT & regs->dx) > 0) {
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
