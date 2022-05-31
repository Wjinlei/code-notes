#include <linux/kernel.h>
#include <linux/module.h>

#include "khook/engine.c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jerry Wang <freebufer.wang@gmail.com>");
MODULE_DESCRIPTION("LSM Hook demo");
MODULE_VERSION("0.1");

#include <linux/security.h>
KHOOK(security_inode_create);
static int khook_security_inode_create(struct inode *dir, struct dentry *dentry, umode_t mode)
{
        /* int ret = 0; */
        pr_err("Hook create: %s\n", dentry->d_name.name);
        return -1;
        /* ret = KHOOK_ORIGIN(security_inode_create, dir, dentry, mode); */
        /* return ret; */
}

int init_module(void)
{
        return khook_init();
}

void cleanup_module(void)
{
        khook_cleanup();
}
