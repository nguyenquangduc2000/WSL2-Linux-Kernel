#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <procmem.h>

int main() {
	long sysvalue;
	struct proc_segs info;
	int input;
	scanf("%d", &input);
	sysvalue = syscall(335, input, &info);

	printf("My MSSV: %lu\n", info.mssv);
	printf("Code segment: %lx-%lx\n", info.start_code, info.end_code);
	printf("Data segment: %lx-%lx\n", info.start_data, info.end_data);
	printf("Heap segment: %lx-%lx\n", info.start_heap, info.end_heap);
	printf("Start stack: %lx\n", info.start_stack);

	if (sysvalue == 0)
		printf("System call executed correctly. Use dmesg to check.\n");
	else
		printf("System call did not execute as expected\n");
}