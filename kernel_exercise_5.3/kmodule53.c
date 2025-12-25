#include <linux/mm.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

static int pid = 1;

static void print_file_vmas(struct task_struct *pt)
{
    struct mm_struct *mm;
    struct vm_area_struct *vma;
    unsigned long addr = 0;
    int cntr = 0;

    mm = get_task_mm(pt);
    if (!mm) {
        printk(KERN_INFO "  No memory descriptor.\n");
        return;
    }

    while ((vma = find_vma(mm, addr)) != NULL) {
        addr = vma->vm_end;
        if (!vma->vm_file)
            continue;

        char *path;
        char buf[256];
        path = d_path(&vma->vm_file->f_path, buf,
                      sizeof(buf));
        if (!IS_ERR(path)) {
            cntr++;
            printk(KERN_INFO
                  " File-backed VMA %2d: 0x%lx - 0x%lx --> %s\n",
                   cntr, vma->vm_start, vma->vm_end, path);
        }
    }
    mmput(mm);
}

static void run_exercise(void)
{
    struct task_struct *pt;

    printk(KERN_INFO "kmodule53: Looking for PID=%d\n", pid);

    for_each_process(pt) {
        if (pt->pid == pid) {
            printk(KERN_INFO
                   "kmodule53: Found process '%s' PID=%d, PPID=%d\n",
                   pt->comm, pt->pid, pt->real_parent->pid);
            print_file_vmas(pt);
            break;
        }
    }
}

static int __init start_module(void)
{
    printk(KERN_INFO "kmodule53: == STARTING ==\n");
    run_exercise();
    return 0;
}

static void __exit exit_module(void)
{
    printk(KERN_INFO "kmodule53: == EXITING ==\n");
}

module_init(start_module);
module_exit(exit_module);

module_param(pid, int, 0);

MODULE_LICENSE("GPL");
