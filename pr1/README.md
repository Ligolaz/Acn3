# Завдання 1.3. Компіляція з використанням бібліотек

## Тезисно що було зроблено

- Демонстрація процесу компіляції та лінкування проєкту, що складається з кількох файлів - main.c, input.c, output.c, process.c, process1.c
- Створення статичних (.a) та динамічних (.so) бібліотек
- Лінкування бібліотек, що знаходяться у системних (/usr/lib) та користувацьких (~/mylibs) каталогах
- Автоматизація процесу компіляції за допомогою Makefile та CMake

## Програмні вимоги

- Середовище запуску - термінал Linux (btw у цій практичній використовувався Ubuntu через VirtualBox)
- Компілятор - GCC
- + Утиліта - Make

## Збірка та запуск

Процес збірки складається зі створення бібліотек та компіляції головної програми
## 1. Створення статичних бібліотек (.a)

Спочатку створюємо бібліотеки, які будуть використовуватися програмою:
```
gcc -c process1.c -o process1.o
ar rcs libprocess1.a process1.o
sudo cp libprocess1.a /usr/lib/

mkdir -p ~/mylibs
gcc -c process.c -o process.o
ar rcs ~/mylibs/libprocess.a process.o
```
## 2. Компіляція головної програми

Збираємо програму, вказуючи компілятору, де шукати новостворені бібліотеки:
```
gcc main.c input.c output.c -L/usr/lib -lprocess1 -L~/mylibs -lprocess -o my_program
```
## 3. Запуск

Після успішної компіляції програма запускається наступною командою:
```
./my_program
```
## 4. Робота з динамічними бібліотеками (.so)

Створюємо динамічні бібліотеки та вказати шлях до них перед запуском:
```
gcc -c -fPIC process.c -o process.o
gcc -shared -o ~/mylibs/libprocess.so process.o

export LD_LIBRARY_PATH=$HOME/mylibs:$LD_LIBRARY_PATH - команда перед запуском, виконується в кожній новій сесії термінала

./my_program
```

## Автоматизація за допомоги Makefile

Для спрощення процесу створюємо та використовуємо Makefile:
```
CC = gcc
CFLAGS = -g -O2 -Wall
LIBS = -L/usr/lib -lprocess1 -L$(HOME)/mylibs -lprocess

all: my_program

my_program: main.o input.o output.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o my_program
```
Команди для роботи з Makefile:
```
make - зібрати проєкт
make clean - очистити папку від файлів збірки
```

## Автоматизація за допомоги CMake

Створюємо файл CMakeLists.txt:
```
cmake_minimum_required(VERSION 3.10)

project(Lab1_3)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2")

#Finding all libs
#System process1
find_library(LIB_PROCESS1 process1 PATHS /usr/lib)
#Home process
find_library(LIB_PROCESS process PATHS $ENV{HOME}/mylibs)

add_executable(my_program main.c input.c output.c)
#Connecting libs to prog
target_link_libraries(my_program ${LIB_PROCESS1} ${LIB_PROCESS})
```
Команди для роботи з CMake:
```
cmake .(саме пробіл - крапка, щоб вказати поточну папку) - створити файли для збірки
make - скомпілювати програму
```

## Результат

При успішному запуску, програма виведе послідовність виклику функцій:
```
Starting program...
Input is here!!!
System lib AKA Process1 was called.
User lib Process was called.
Output is here.!.
Ending Program.
```
