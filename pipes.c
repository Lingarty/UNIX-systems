/*
		Задача: программа создаёт два процесса, взаимодействующих
	через  программный   канал.  Первый  процесс  выдает  в  канал  текст,
	состоящий из  символов верхнего  и нижнего  регистров.  Второй процесс
	переводит все символы в верхний регистр, и выводит полученный текст на
	терминал. { fork(2), pipe(2) } 
*/

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
 
 int main(int argc, char **argv)
 {
 	int pid;
 	int fd[2];

	static char lines[3][50] = {"Here are 3 lines of text.\n", "You will see all lower case\n", "made to upper!!\n"};
	char input[1000];
	int rtn;

	if (pipe(fd) == -1) 
	{
		perror(argv[0]);
		exit(1);
	}
	if ((pid = fork()) > 0) /* parent */
	{
		close(fd[0]);
		for(int i = 0; i < 3; i++)
			write(fd[1], lines[i], strlen(lines[i]));
		close(fd[1]);
	}
	else if (pid == 0) /* child */ 
		/*
			Все процессы в Unix имеют своих родителей — процессы, не имеющие или потерявшие родителей 
			являются дочерними для init (процесс с PID = 1), который в свою очередь является дочерним 
			для ядра (процесса с PID = 0). init всегда обрабатывает SIGCHLD, поэтому от таких процессов 
			никогда не остаётся зомби (пустых процессов, хранящих только код завершения для родительского процесса).
		*/
	{
		close(fd[1]);
		while ((rtn=read(fd[0], input, 1000)) > 0)
		{
			for(int i = 0; i < rtn; i++)
				if(islower(input[i]))
					input[i] = toupper(input[i]);
			write(1, input, rtn);
		}
		close(fd[0]);
	}
	else /* cannot fork */
	{
		perror(argv[0]);
		exit(2);
	}
	exit(0);
}
