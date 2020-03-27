#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
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
		printf("%d", num);
		while(num != 1)
		{
			if(num % 2 == 0)
				num /= 2;
			else
				num = 3 * num + 1;
			printf(",%d", num);
		}
		exit(0);
	}
	else
	{
		wait(&status);
		//printf("\n%d", WEXITSTATUS(status));
	}
	

	return 0;
}