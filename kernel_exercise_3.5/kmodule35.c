#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

static void run_exercise(void)
{
    struct task_struct *pt;

    for_each_process(pt) {
        if (strcmp(pt->comm, "top") == 0) {
            printk(KERN_INFO "Found: Name='%s' | PID=%d \
| PPID=%d\n", pt->comm, pt->pid, pt->real_parent->pid);
        }
    }
}

static int __init start_module(void)
{
    printk(KERN_INFO "kmodule35: == STARTING ==\n");
    run_exercise();
    return 0;
}

static void __exit exit_module(void)
{
    printk(KERN_INFO "kmodule35: == EXITING ==\n");
}

module_init(start_module);
module_exit(exit_module);

MODULE_LICENSE("GPL");
