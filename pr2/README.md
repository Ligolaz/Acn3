# Практична робота №2

## Тезисно що було зроблено

- Дослідження типу **time_t**, його розміру та поведінки при переповненні на 64-бітній системі
- Аналіз сегментів виконуваного файлу - **text, data, bss**. Їх зміни в залежності від оголошення глобальних та локальних змінних
- Дослідження стека викликів завислого процесу за допомогою дебагера **GDB**
- Дослідження розподілу пам'яті у багатопотоковій програмі

## Програмні вимоги

- Середовище запуску - термінал Linux
- Компілятор - GCC
- Утиліти - GDB, size

## Збірка та запуск

### 1. Дослідження time_t (Завдання 1)

Програма визначає розмір time_t (64 біти) та демонструє переповнення при спробі перевищити максимальне значення (2^63 - 1), що призводить до переходу у мінімальне від'ємне

**Компіляція та запуск:**
```
user@user:~/lab2$ gcc 1.c -o 1
1.c: In function ‘main’:
1.c:8:24: warning: overflow in conversion from ‘double’ to ‘time_t’ ...
user@user:~/lab2$ ./1
time_t bits (1 bit +- sign): 64

Max time_t is 2^63 - 1: 9223372036854775807

++time1 result: -9223372036854775808
Negative value mrans 2^63 is max time, because it OVERFLOWED when ++time1
```

### 2. Аналіз сегментів виконуваного файлу (Завдання 2)

Було створено 4 версії "hello world" для аналізу, як оголошення змінних впливає на розмір сегментів

**2.1. Базова програма:**
```
user@user:~/lab2$ ls -l 2-1
-rwxrwxr-x 1 user user 15960 Feb 15 18:06 2-1
user@user:~/lab2$ size 2-1
   text	   data	    bss	    dec	    hex	filename
   1374	    600	      8	   1982	    7be	2-1
```
**2.2. Додано глобальний неініціалізований масив (int arr[1000]):**

Виріс сегмент BSS, де зберігаються неініціалізовані дані:
```
user@user:~/lab2$ ls -l 2-2
-rwxrwxr-x 1 user user 15984 Feb 15 18:07 2-2
user@user:~/lab2$ size 2-2
   text	   data	    bss	    dec	    hex	filename
   1374	    600	   4032	   6006	   1776	2-2
```
**2.3. Глобальний масив ініціалізовано (int arr[1000] = {1}):**

Масив перемістився з BSS у сегмент DATA, що збільшило розмір файлу на диску:
```
user@user:~/lab2$ ls -l 2-3
-rwxrwxr-x 1 user user 20000 Feb 15 18:09 2-3
user@user:~/lab2$ size 2-3
   text	   data	    bss	    dec	    hex	filename
   1374	   4616	      8	   5998	   176e	2-3
```
**2.4. Додано локальний масив у main():**

Розміри сегментів майже не змінилися, оскільки локальний масив знаходиться на стеку і створюється під час виконання, а не зберігається у файлі:
```
user@user:~/lab2$ ls -l 2-4
-rwxrwxr-x 1 user user 20056 Feb 15 18:10 2-4
user@user:~/lab2$ size 2-4
   text	   data	    bss	    dec	    hex	filename
   1574	   4624	      8	   6206	   183e	2-4
```

### 3. Визначення адрес пам'яті (Завдання 3)

Програма виводить адреси ключових областей пам'яті:
```
user@user:~/lab2$ gcc 3.c -o 3
user@user:~/lab2$ ./3
Text segment, aka main(), is at: 0x55ebba9601e3
Global int (data segment) is at: 0x55ebba963010
Heap is at: 0x55ebd2a662a0
The stack top is near: 0x7fffe03a0bd0
Func called
Now stack top is near: 0x7fffe03a0bd4
```

### 4. Дослідження стека процесу за допомогою GDB (Завдання 4)

Було використано два термінали: в одному програма була "заморожена" викликом pause(), в іншому - проаналізована через gdb:

**Термінал 1 (Запуск програми):**
```
user@user:~/lab2$ gcc -g 4.c -o 4
user@user:~/lab2$ ./4
In function                 main; &localvar = 0x7fff07ba6904
In function                  foo; &localvar = 0x7fff07ba68d4
In function                  bar; &localvar = 0x7fff07ba68b4
In function    bar_is_now_closed; &localvar = 0x7fff07ba6894

 Now blocking on pause()...
Terminated
```
**Термінал 2 (Аналіз через GDB):**
```
user@user:~$ ps aux | grep ./4
user        2762  0.0  0.0   2680  1528 pts/0    S+   19:08   0:00 ./4
...
user@user:~$ sudo gdb -q
(gdb) attach 2762
Attaching to process 2762
Reading symbols from /home/user/lab2/4...
...
(gdb) bt
#0  0x000076d10c2fa3d4 in __libc_pause () at ../sysdeps/unix/sysv/linux/pause.c:29
#1  0x00005b3af9280224 in bar_is_now_closed ()
#2  0x00005b3af9280287 in bar ()
#3  0x00005b3af92802ea in foo ()
#4  0x00005b3af9280354 in main ()
(gdb) detach
Detaching from program: /home/user/lab2/4, process 2762
...
(gdb) quit
user@user:~$ kill 2762
```

### 5. IP та Стек (Завдання 5)

Для розгляду гіпотетичної ситуації заміни лічильника команд (IP) на вершину стека було написано демонстраційний код. Проблема полягає в тому, що при виклику функції, процесор зберігає адресу повернення на стеку. Якщо сама верхівка стека використовується як IP, то для адреси повернення просто не залишається місця, не затерши поточну команду. Це призведе до збою програми після завершення функції, бо процесор більше не буде знати, куди повертатися.
Запуск коду:
```
user@user:~/lab2$ gcc 5.c -o 5
user@user:~/lab2$ ./5
Before func
Inside func
After func
```

### 6. Завдання за 4-м варіантом

Програма демонструє, що стандартний алокатор malloc є потокобезпечним, адже кожен з 4 потоків отримує унікальну адресу пам'яті на спільному Heap:
```
user@user:~/lab2$ gcc -pthread 6.c -o 6
user@user:~/lab2$ ./6
Starting 4 threads to test memory allocation...
Thread 2: Allocated memory at address: 0x7b3738000b70
Thread 1: Allocated memory at address: 0x7b373c000b70
Thread 3: Allocated memory at address: 0x7b3734000b70
Thread 0: Allocated memory at address: 0x7b3740000b70
Thread 2: Data verified successfully. Freeing memory.
Thread 0: Data verified successfully. Freeing memory.
Thread 1: Data verified successfully. Freeing memory.
Thread 3: Data verified successfully. Freeing memory.
All threads finished execution.
```

## Висновки

У цій роботі було продемонстровано принципи системного програмування, зокрема аналіз фундаментального ресурсу ОС - пам'яті. Ефективність цього аналізу було підтверджено у терміналі за допомогою утиліт size та gdb, які дозволили побачити, як саме операційна система структурує програму у віртуальному адресному просторі.

Роботу було зроблено на Linux, оскільки ця система дозволяє легко побачити, як все влаштовано всередині. Скомпільована програма ділиться на чіткі частини, сегменти - text, data, bss. Тобто це наче інструкція для ОС, куди саме розкласти код та змінні у пам'яті, коли програма запускається. Таким чином, ми на практиці побачили, як працює система керування пам'яттю.

Окрему увагу було приділено роботі з різними областями пам'яті. Було продемонстровано, як неініціалізовані глобальні дані потрапляють у сегмент BSS, а ініціалізовані - в DATA. Робота з динамічною пам'яттю (malloc) та аналіз стека через gdb наочно показали, як ОС керує спільними та індивідуальними ресурсами процесу під час його виконання.
