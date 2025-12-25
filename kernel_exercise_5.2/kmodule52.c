#include <linux/mm.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

static int pid = 1;

static void print_all_vmas(struct task_struct *pt)
{
    struct mm_struct *mm;
    struct vm_area_struct *vma;
    unsigned long addr = 0;
    int count = 0;

    mm = get_task_mm(pt);
    if (!mm) {
        printk(KERN_INFO "  No memory descriptor.\n");
        return;
    }

    while ((vma = find_vma(mm, addr)) != NULL) {
        count++;
        printk(KERN_INFO
               "  VMA number %4d: 0x%lx - 0x%lx\n",
               count, vma->vm_start, vma->vm_end);
        addr = vma->vm_end;
    }

    mmput(mm);
}

static void run_exercise(void)
{
    struct task_struct *pt;

    printk(KERN_INFO " Looking for PID=%d\n", pid);

    for_each_process(pt) {
        if (pt->pid == pid) {
            printk(KERN_INFO
                   " Found process '%s' PID=%d, PPID=%d\n",
                   pt->comm, pt->pid, pt->real_parent->pid);
            print_all_vmas(pt);
            break;
        }
    }
}

static int __init start_module(void)
{
    printk(KERN_INFO "kmodule52: == STARTING ==\n");
    run_exercise();
    return 0;
}

static void __exit exit_module(void)
{
    printk(KERN_INFO "kmodule52: == EXITING ==\n");
}

module_init(start_module);
module_exit(exit_module);

module_param(pid, int, 0);

MODULE_LICENSE("GPL");

