#include <linux/linkage.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/sched/signal.h>

struct proc_segs{
	unsigned long mssv;
	unsigned long start_code;
	unsigned long end_code;
	unsigned long start_data;
	unsigned long end_data;
	unsigned long start_heap;
	unsigned long end_heap;
	unsigned long start_stack;
};

void read_mem(struct task_struct *task, struct proc_segs* info)
{
	struct mm_struct *mm;
	mm = task->mm;

	info->start_code = mm->start_code;
	info->end_code = mm->end_code;
	info->start_data = mm->start_data;
	info->end_data = mm->end_data;
	info->start_heap = mm->start_brk;
	info->end_heap = mm->brk;
	info->start_stack = mm->start_stack;
}

asmlinkage long sys_procmem(int pid, struct proc_segs* info) {
	// TODO: Implement the system call
	info->mssv = 1810118;

	struct task_struct *task;
	for_each_process(task) {
		if (task->pid == pid) {
			read_mem(task, info);
			break;
		}
	}
	return 0;
}
