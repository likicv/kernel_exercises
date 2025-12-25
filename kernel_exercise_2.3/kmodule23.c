#include <linux/kernel.h>
#include <linux/module.h>

static void run_exercise(void)
{
    // Exercise-specific logic goes here
}

static int __init start_module(void) {
    printk(KERN_INFO "kmodule23: == STARTING ==\n");
    run_exercise();
    return 0;
}

static void __exit exit_module(void) {
    printk(KERN_INFO "kmodule23: == EXITING ==\n");
}

module_init(start_module);
module_exit(exit_module);

MODULE_LICENSE("GPL");
