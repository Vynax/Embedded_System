// kernel_world/fileIO.c

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_DESCRIPTION("fileIO");
MODULE_LICENSE("GPL");

static int fileIO_init(void)
{
    struct file *f;
    char buf[256] = {0};
    mm_segment_t fs;
    //int i;
    printk(KERN_INFO "fileIO start\n");

    printk(KERN_INFO "fileIO is initialized");
    f = filp_open("input.txt", O_RDONLY, 0);
    if (f == NULL)
        printk(KERN_ALERT "filp_open error!!.\n");
    else
    {
        // Get current segment descriptor
        fs = get_fs();
        // Set segment descriptor associated to kernel space
        set_fs(KERNEL_DS);
        // Read the file
        f->f_op->read(f, buf, 128, &f->f_pos);
        // Restore segment descriptor
        set_fs(fs);
        // See what we read from file
        printk(KERN_INFO "buf:%s\n", buf);
    }
    filp_close(f, NULL);
    return 0;
}

static void fileIO_exit(void)
{
    printk(KERN_INFO "fileIO Bye !\n");
}

module_init(fileIO_init);
module_exit(fileIO_exit);
