#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
	const int SIZE = 4096;
	const char* name = "mySM";
	int shm_fd;
	void* ptr;
	shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	int num = 0;
	int status;
	pid_t pid;
	printf("Please enter a number :\n");
	scanf("%d", &num);

	while(num < 0)
	{
		printf("Error : Please enter a posistive number.\n");
		scanf("%d", &num);
	}

	pid = fork();

	//printf("%d\n", pid);
	if(pid < 0)
	{
		printf("Error in creating a child process.\n");
		exit(-1);
	}
	else if (pid == 0)
	{
		sprintf((char*)ptr, "%d", num);
		ptr += sizeof(num);
		while(num != 1)
		{
			if(num % 2 == 0)
				num /= 2;
			else
				num = 3 * num + 1;
			sprintf((char*)ptr, "%d", num);
			//printf("%d,%d\n", (int*)&ptr, num);
			ptr += sizeof(num);
		}
		exit(0);
	}
	else
	{
		wait(&status);
		printf("%s",(char*)ptr);
		do
		{
			printf(", ");
			ptr += sizeof(int);
			printf("%s", (char*)ptr);
		}while(atoi((char*)ptr) != 1);
	}
	

	return 0;
}