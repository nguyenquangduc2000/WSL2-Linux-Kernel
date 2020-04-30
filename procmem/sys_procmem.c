#include <linux/linkage.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/syscalls.h>

struct proc_segs {
	unsigned long mssv;
	unsigned long start_code;
	unsigned long end_code;
	unsigned long start_data;
	unsigned long end_data;
	unsigned long start_heap;
	unsigned long end_heap;
	unsigned long start_stack;
};

void read_mem(struct task_struct *task, struct proc_segs* info) {
	struct mm_struct *mm;
	mm = task->mm;

	info->start_code = mm->start_code;
	info->end_code = mm->end_code;
	info->start_data = mm->start_data;
	info->end_data = mm->end_data;
	info->start_heap = mm->start_brk;
	info->end_heap = mm->brk;
	info->start_stack = mm->start_stack;

	printk("\nCode  Segment start = 0x%lx, end = 0x%lx \n"
			"Data  Segment start = 0x%lx, end = 0x%lx\n"
			"Heap  Segment start = 0x%lx, end = 0x%lx\n"
			"Stack Segment start = 0x%lx\n",
			mm->start_code, mm->end_code,
			mm->start_data, mm->end_data,
			mm->start_brk,	mm->brk,
			mm->start_stack);
}

SYSCALL_DEFINE2(procmem, int, pid, struct proc_segs*, info) {
	// TODO: Implement the system call
	struct task_struct* task;
	printk("Syscall is successfully called\n");
	printk("PID: %d\n", pid);
	info->mssv = 1810118;

	task = pid_task(find_vpid(pid), PIDTYPE_PID);
	if (task != NULL)
		read_mem(task, info);

	return 0;
}
