/*
  Какая-то контроха

	Задача: 
	argv[0] - имя
	argv[1] - последовательность (abc), считаем, сколько раз она встретилась
	argv[2] - если есть флаг -k, считает все а, после которых нет r
*/

#include <stdio.h>	
#include <string.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	char c;
	int i = 0; // индекс по входному слову
	int ended = 0;
	int count = 0; //считает сумму символов
	int a_count = 0; //количество а, после которых нет r


	if (argc == 3 && argv[2][0] == '-' && argv[2][1] == 'k') //проверяет наличие флага и считает кол-во а, после которых нет r
	{	
		ended = (c = getchar()) == EOF;
		while (!ended)
		{
			if (c == 'a')
			{
				ended = (c = getchar()) == EOF;	
				if (c != 'r')
				{
					a_count++;
				}
			}
			ended = (c = getchar()) == EOF;
		}
		printf("\nСумма a, после которых нет r, в файле: %d\n",  a_count);		
	}
	else
	{	
		while (!ended)
		{
			ended = (c = getchar()) == EOF;
			if (c == argv[1][0])
			{
				for (i = 1; i < strlen(argv[1]) && !ended; i++)
				{
					ended = (c = getchar()) == EOF;
					if (c != argv[1][i])
					{
						break;
					}	
				}
				if (i == strlen(argv[1]))
				{
					count++;
				}
			}
		}
		printf("\nСумма %s в файле: %d\n", argv[1], count);
	}
	return 0;
}
