// kernel_world/fileIO.c

#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("fileIO");
MODULE_LICENSE("GPL");

static int fileIO_init(void)
{
    printk(KERN_INFO "Hello world !\n");
    return 0;
}

static void fileIO_exit(void)
{
    printk(KERN_INFO "Bye !\n");
}

module_init(fileIO_init);
module_exit(fileIO_exit);
