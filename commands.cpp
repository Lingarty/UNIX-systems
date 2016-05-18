/*
	Задача: написать программу, реализующую несколько команд

	Реализация:
	-s -- подсчёт количества слов в файле
	-ml -- вывод самого длинного слова
	-b -- создание резервной копии файла в текущую папку
*/
	// сделать так, чтоб можно было вводить несколько флагов одновременно

#include <stdio.h>

int is_letter(char c)
{
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

int sum_words()
{	
	int sum = 0;
	char c;
	int ended = 0;
	while (!ended)
	{
		ended = ((c = getchar()) == EOF);
		if (!is_letter(c))
		{
			sum++;
		}
	}
	return sum - 1;
}

void max_word(char word[50], int &max_length) //ищет макс длинное слово в потоке
{
	char cur_word[50];
	int length = 0;
	int i = 0; //индекс для массива
	char c; // сюда считываем символы из потока
	int ended = 0;

	while (!ended)
	{
		ended = ((c = getchar()) == EOF);
		if (is_letter(c)) 
		{
			cur_word[i] = c;
			length++;
			i++;
		}
		else if (length > max_length)
		{
			max_length = length;
			for (int j = 0; j < max_length; j++)
			{
				word[j] = cur_word[j];
			}
			length = 0;
			i = 0;
		}
		else
		{
			length = 0;
			i = 0;
		}
	}
}

void print(char word[50], int l) // печатает массив как слово
{
	for (int i = 0; i < l; i++)
	{
		printf("%c", word[i]);
	}
}

void read(char word[50], int &l) // читает слово как массив
{
	char c;
	int ended = 0;
	int i = 0;

	while (!ended)
	{
		ended = (c = getchar()) == '\n';
		if (c != '\n')
		{
			word[i] = c;
			i++;
		}
	}
	l = i;
}


int main(int argc, char* argv[])
{
	int not_flag = 3; // вычисляет количество неиспользованных команд
	for (int i = 0; i < argc; i++) //проверяем наличие каждого флага
	{
		if (argv[i][0] == '-' && argv[i][1] == 's')
			// подсчёт количества слов в файле
		{
			not_flag--;
			int sum = sum_words();
			printf("На вход поступило %d слов\n", sum);
		}
		else if (argv[i][0] == '-' && argv[i][1] == 'm' && argv[i][2] == 'l')
			// самое длинное слово в тексте
		{	
			not_flag--;
			char word[50];
			int max_length = 0;
			max_word(word, max_length);
			printf("Самое длинное слово в тексте: ");
			print(word, max_length);
			printf("\n");
		}
		else if (argv[i][0] == '-' && argv[i][1] == 'b')
			// резервная копия файла в каталоге
		{
			not_flag--;
			FILE *file = fopen("input-3-backup.txt", "w");
			
			if (file != NULL)
			{
				int ended = 0;
				char c;

				while (!ended)
				{
					ended = (c = getchar()) == EOF;
					if (c != EOF)
					{
						fprintf(file, "%c", c);
					}
				}
				printf("Cоздана резервная копия input-3-backup.txt в текущем каталоге\n");
			}
			else
			{
				printf("Файл не найден\n");
			}
		}
	}
	if (not_flag == 3)
		printf("Доступные команды не найдены\n");

	return 0;
}
