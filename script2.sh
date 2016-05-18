#!/bin/sh
# Задача: переименование нескольких файлов по заданным правилам


#У этой программы есть различные "режимы": добавить посл-ть символов в начало программы, в конец или заменить (подробнее в конце)
# 1. Переименование по суффиксу
# Если первый аргумент ($1) подходит, то мы выполняем эту часть программы и затем выходим.

# Проверка на условие добавления префикса.
if [ $1 = p ]; then
  #Теперь сдвигаемся от переменной режима ($1) и префикса ($2)
  prefix=$2 ; shift ; shift

  # Проверим, задан ли хотя бы один файл.
  # Если нет, то лучше ничего не делать, чем переименовывать несуществующие файлы!

  if [$1 = ]; then
     echo "не задано ни одного файла"
     exit 0
  fi

  # Этот цикл for проделывает итерации над всеми файлами, которые мы задали.
  # Он делает одно переименование на файл.
  for file in $*
    do
    mv ${file} $prefix$file
  done

  #Теперь выходим из программы.
  exit 0
fi

# 2. Переименование по суффиксу
# Проверка на условие добавления суффикса.

if [ $1 = s ]; then
  suffix=$2 ; shift ; shift
  if [$1 = ]; then
   echo "не задано ни одного файла"
   exit 0
  fi

 for file in $*
  do
   mv ${file} $file$suffix
 done

 exit 0
fi

# 3. Переименование с заменой 
# Проверка на условие переименования с заменой.
if [ $1 = r ]; then
  shift

  # Этот кусок позволяет не повредить ни один файл, если пользователь
  # не определил, что сделать:

  if [ $# -lt 3 ] ; then
    echo "Ошибка; правильный ввод: r [выражение] [замена] файлы... "
    exit 0
  fi

  # Сдвигаемся к другой информации
  OLD=$1 ; NEW=$2 ; shift ; shift

  # Данный цикл for последовательно проходит через все файлы, которые мы 
  # задали программе.
  # Он совершает одно переименование на файл, используя программу 'sed'.
  # Это простая программа с командной строки, которая анализирует стандартный 
  # ввод и заменяет регулярное выражение на заданную строку.
  # Здесь мы задаём для sed имя файла (как стандартный ввод) и заменяем
  # нужный текст.

  for file in $*
  do
    new=`echo ${file} | sed s/${OLD}/${NEW}/g`
    mv ${file} $new
  done
  exit 0
fi

# Если дошли до этой строки, это значит, что программе были заданы
# неправильные параметры. Поэтому выводим правила использования
echo " Для корректной работы скрипта используйте:"
echo " p [префикс] файлы.."
echo " s [суффикс] файлы.."
echo " r [выражение] [замена] файлы.."
exit 0

# done!