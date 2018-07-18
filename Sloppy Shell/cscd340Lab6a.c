#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
int main()
{
	pid_t pid;
	int fd[2], res, status;
	res = pipe(fd);

	if(res < 0)
	{
		printf("Pipe Failure\n");
		exit(-1);
	}// end if

	pid = fork();

	if(pid != 0)
	{
	  // waitpid(pid, &status, 0);
	  close(fd[1]);
	  close(0);
	  dup(fd[0]);
	  close(fd[0]);
	  execlp("wc", "wc", "-w", NULL);
	  exit(1);
	}// end if AKA parent
	else
	{
	  // puts("test point 2\n");
		close(fd[0]);
		close(1);
		dup(fd[1]);
		close(fd[1]);
		execlp("ls", "ls", "-l", NULL);
		perror("Something went wrong");
		exit(1);
	}// end else AKA child

	return 0;

}// end main
*/
