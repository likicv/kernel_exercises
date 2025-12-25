#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_NAME "simple_counter"

static ssize_t proc_read(struct file *file, char __user *buf, size_t count, loff_t *pos) {
    char output[] = "42\n";
    size_t len = sizeof(output);

    if (*pos > 0)  // EOF after first read
        return 0;

    if (copy_to_user(buf, output, len))
        return -EFAULT;

    *pos = len;
    return len;
}

static const struct proc_ops proc_fops = {
    .proc_read = proc_read,
};

static void run_exercise(void)
{
    if (!proc_create(PROC_NAME, 0444, NULL, &proc_fops)) {
        printk(KERN_ERR "  Failed to create /proc/%s\n", PROC_NAME);
    } else {
        printk(KERN_INFO "  /proc/%s created\n", PROC_NAME);
    }
}

static int __init start_module(void) {
    printk(KERN_INFO "kmodule62: == STARTING ==\n");
    run_exercise();
    return 0;
}

static void __exit exit_module(void) {
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
    printk(KERN_INFO "kmodule62: == EXITING ==\n");
}

module_init(start_module);
module_exit(exit_module);

MODULE_LICENSE("GPL");
