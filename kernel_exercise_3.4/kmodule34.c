#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

static void run_exercise(void)
{
    struct task_struct *pt;
    int cntr = 0;

    for_each_process(pt) {
        printk(KERN_INFO "[%d] PID: %d | Name: %s\n", cntr++,
               pt->pid, pt->comm);
    }
}

static int __init start_module(void)
{
    printk(KERN_INFO "kmodule34: == STARTING ==\n");
    run_exercise();
    return 0;
}

static void __exit exit_module(void)
{
    printk(KERN_INFO "kmodule34: == EXITING ==\n");
}

module_init(start_module);
module_exit(exit_module);

MODULE_LICENSE("GPL");
