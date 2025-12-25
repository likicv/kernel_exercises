#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

static int pid = 1;

static void run_exercise(void)
{
    struct task_struct *pt;

    printk(KERN_INFO "  Searching for PID=%d\n", pid);

    for_each_process(pt) {
        if (pt->pid == pid) {
            printk(KERN_INFO "  Found process '%s' PID=%d, PPID=%d\n",
                   pt->comm, pt->pid, pt->real_parent->pid);
        }
    }
}

static int __init start_module(void)
{
    printk(KERN_INFO "kmodule36: == STARTING ==\n");
    run_exercise();
    return 0;
}

static void __exit exit_module(void)
{
    printk(KERN_INFO "kmodule36: == EXITING ==\n");
}

module_init(start_module);
module_exit(exit_module);

module_param(pid, int, 0);

MODULE_LICENSE("GPL");
