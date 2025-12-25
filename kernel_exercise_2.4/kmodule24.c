#include <linux/kernel.h>
#include <linux/module.h>

static int pid = 1;

static void run_exercise(void)
{
    printk(KERN_INFO " -> got pid=%d\n", pid);
}

static int __init start_module(void)
{
    printk(KERN_INFO "kmodule24: == STARTING ==\n");
    run_exercise();
    return 0;
}

static void __exit exit_module(void)
{
    printk(KERN_INFO "kmodule24: == EXITING ==\n");
}

module_init(start_module);
module_exit(exit_module);

module_param(pid, int, 0);

MODULE_LICENSE("GPL");
