// kernel_world/fileIO.c

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
// #include <string.h>

MODULE_DESCRIPTION("fileIO");
MODULE_LICENSE("GPL");

static int fileIO_init(void)
{
    struct file *f = NULL;
    struct file *foutput = NULL;
    char buf[384] = {0};
    char reversebuf[384] = {0};
    mm_segment_t fs;
    loff_t pos = 0;
    int i, j;
    printk(KERN_INFO "fileIO start5\n");

    printk(KERN_INFO "fileIO is initialized");
    f = filp_open("/home/user/Github/Embedded_System/HW1/fileIO/input.txt", O_RDONLY, 0);
    foutput = filp_open("output.txt", O_WRONLY | O_CREAT, 0644);
    printk(KERN_INFO "file open OK");
    if (f == NULL)
        printk(KERN_ALERT "filp_open error!!.\n");
    else
    {
        // Get current segment descriptor
        fs = get_fs();
        printk(KERN_INFO "fs = get_fs OK");
        // Set segment descriptor associated to kernel space
        set_fs(KERNEL_DS);
        printk(KERN_INFO "set_fs(KERNEL_DS) OK");
        // Read the file

        // f->f_op->read(f, buf, 128, &f->f_pos);

        while (kernel_read(f, buf, 384, &pos))
        {
            printk(KERN_INFO "buf:%s\n", buf);
            // for (i = 0; i < (sizeof buf) / sizeof buf[0]; i++)
            //     buf[i] = '\0';
        }
        i = strlen(buf);
        reversebuf[i] = '\0';
        printk(KERN_INFO "strlen(buf):%d\n", i);
        for (i = strlen(buf) - 1, j = 0; i >= 0; i--, j++)
        {
            //printk(KERN_INFO "hi%d\n", i);
            reversebuf[j] = buf[i];
        }

        printk(KERN_INFO "strlen reversebuf:%ld\n", strlen(reversebuf));
        printk(KERN_INFO "reversebuf:%s\n", reversebuf);
        kernel_write(foutput, reversebuf, strlen(reversebuf), &foutput->f_pos);
        // for (i = 0; i < strlen(reversebuf); i++)
        // {
        //     printk(KERN_INFO "hi:%d\n", i);
        //     printk(KERN_INFO "reversebuf:%c\n", reversebuf[i]);
        //     printk(KERN_INFO "hi_why:%d\n", i);
        // }

        //printk(KERN_INFO "f->f_op->read OK");

        // Restore segment descriptor
        set_fs(fs);
        printk(KERN_INFO "set_fs(fs) OK");
        // See what we read from file
        //printk(KERN_INFO "buf:%s\n", buf);
    }
    filp_close(f, NULL);
    filp_close(foutput, NULL);
    printk(KERN_INFO "filp_close OK");
    return 0;
}

static void fileIO_exit(void)
{
    printk(KERN_INFO "fileIO Bye !\n");
}

module_init(fileIO_init);
module_exit(fileIO_exit);
