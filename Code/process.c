#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched/signal.h>  // for_each_process

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ChatGPT");
MODULE_DESCRIPTION("Iterate over all processes in the Linux kernel");

static int __init process_iter_init(void)
{
    struct task_struct *task;

    printk(KERN_INFO "Starting to iterate over processes...\n");

    // Iterate over all processes
    for_each_process(task) {
        printk(KERN_INFO "PID: %d | Process name: %s\n", task->pid, task->comm);
    }

    return 0;
}

static void __exit process_iter_exit(void)
{
    printk(KERN_INFO "Process iteration module exiting.\n");
}

module_init(process_iter_init);
module_exit(process_iter_exit);
