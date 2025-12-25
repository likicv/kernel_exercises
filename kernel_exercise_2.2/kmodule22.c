#include <linux/kernel.h>
#include <linux/module.h>

static int __init start_module(void) {
    printk(KERN_INFO "kmodule22: == STARTING ==\n");
    return 0;
}

static void __exit exit_module(void) {
    printk(KERN_INFO "kmodule22: == EXITING ==\n");
}

module_init(start_module);
module_exit(exit_module);

MODULE_LICENSE("GPL");
