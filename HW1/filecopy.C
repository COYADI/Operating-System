#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 100

int main(int argc, char const *argv[])
{
	int fd[2];
	pid_t pid;
	int input_file = open(argv[1], 0);
	int copy_file = open(argv[2], 0666);
	char buffer[BUFFER_SIZE];
	char* copyBuffer;
	int readCnt = 0;

	if(pipe(fd) == -1)
	{
		fprintf(stderr, "pipe failed.\n");
		return -1;
	}

	pid = fork();

	if(pid < 0)
	{
		fprintf(stderr, "fork failed.\n");
		return -1;
	}
	else if(pid == 0)
	{
		close(fd[READ_END]);
		while(read(input_file, buffer, sizeof(buffer)) > 0)
		{
			write(fd[WRITE_END], buffer, strlen(buffer) + 1);
			readCnt = readCnt + 1;
		}
		//printf("%d\n", readCnt);
		close(fd[WRITE_END]);
		exit(0);
	}
	else
	{
		close(fd[WRITE_END]);
		copyBuffer = (char*)malloc(readCnt * sizeof(char));
		//printf("%d %d %d\n", sizeof(copyBuffer), sizeof(buffer), readCnt);
		read(fd[READ_END], copyBuffer, sizeof(buffer));
		write(copy_file, copyBuffer, strlen(copyBuffer) + 1);
		close(fd[READ_END]);
	}

	return 0;
}
