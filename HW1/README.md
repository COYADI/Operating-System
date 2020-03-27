1. gcc –o os-hw1-1 os-hw1-1.C
	./os-hw1-1

	When entered number < 0
	Print : Error : Please enter a posistive number.
	When pid < 0
	Print : Error in creating a child process.
	When pid = 0
	Do child process
	When pid > 0
	Do parent process

2. gcc –o os-hw1-2 os-hw1-2.C -lrt
	./os-hw1-2
	
	When entered number < 0
	Print : Error : Please enter a posistive number.
	When pid < 0
	Print : Error in creating a child process.
	When pid = 0
	Do child process
	When pid > 0
	Do parent process

3. gcc –o filecopy filecopy.C
	./filecopy input.txt copy.txt

	When pipe(fd) = -1
	Print : pipe failed
	When pid < 0
	Print : fork failed
	Child process read and write in pipe 
	Parent process read and write in copy.txt
