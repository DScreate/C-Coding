#include "pipes.h"

int containsPipe(char *s)
{
  int count = 0;
  char * saveptr;
  int i;

  //printf("Starting containsPipe\n");
  for(i = 0; i < strlen(s); i++) {
    if(s[i] == '|') {
      count++;
    }
  }
  
  //printf("number of pipes  is %d\n", count);
  if(count>0)
    return count;
  else
    return -1;

}

char ** parsePrePipe(char *s, int * preCount)
{
  //printf("Starting pPrePipe\n");
  char copy[strlen(s)+1];
  strcpy(copy, s);
  char * temp = strtok(copy, "|");
  char ** res = NULL;
  int i;

  int tokens = makeargs(temp, &res);
  printargs(tokens,res);
  /*
  for(i = 0; i < tokens; i++) {
    printf("%s\n", res[i]);
  }*/
    

  *preCount = tokens;
  //printf("Ending pPrePipe, res is %s %s\n", *res, *(res + 1));
  return res;
 
}

char ** parsePostPipe(char *s, int * postCount)
{
  //printf("Starting pPostPipe\n");
  char copy[strlen(s)+1];
  strcpy(copy, s);
  char * saveptr;
  char * temp = strtok_r(copy, "|",&saveptr);
  char ** res = NULL;
  int i;

  temp = strtok_r(NULL, "\0", &saveptr);
  int tokens = makeargs(temp, &res);
  printargs(tokens,res);
  /*
  for(i = 0; i < tokens; i++) {
    printf("%s\n", res[i]);
  }*/
    

  *postCount = tokens;
  // printf("Ending pPostPipe, res is %s %s\n", *res, *(res + 1));
  return res;

}


void pipeIt(char ** prePipe, char ** postPipe)
{
  pid_t pid;
  int fd[2];
  int status;

  pid = fork();




  if(pid != 0)
    {
      waitpid(pid, &status, 0);
    }// end parent
  else
    {
      //
      int res = pipe(fd);
      if(res < 0)
	{
	  printf("Pipe Failure\n");
	  exit(-1);
	}

      pid_t pid2 = fork();
      
      if(pid2 != 0)
	{
	  close(fd[1]);
	  close(0);
	  dup(fd[0]);
	  close(fd[0]);
	  execvp(postPipe[0], postPipe);
	  exit(-1);
	}// end parent
      else
	{
	  close(fd[0]);
	  close(1);
	  dup(fd[1]);
	  close(fd[1]);
	  execvp(prePipe[0], prePipe);
	  exit(-1);
	}
      //

    }

  

/*  
  void pipeIt(char ** prePipe, char ** postPipe)
{
  pid_t pid;
  int fd[2];

  int res = pipe(fd);

  if(res < 0)
    {
      printf("Pipe Failure\n");
      exit(-1);
    }

  pid = fork();

  if(pid != 0)
    {
      close(fd[1]);
      close(0);
      dup(fd[0]);
      close(fd[0]);
      execvp(postPipe[0], postPipe);
    }// end parent
  else
    {
      close(fd[0]);
      close(1);
      dup(fd[1]);
      close(fd[1]);
      execvp(prePipe[0], prePipe);
    }
*/ 
}
