# Практична №1
## Завдання 1.4. Багатопоток

## Тезисно що було зроблено

- Реалізація багатопоточності на мові C з використанням бібліотеки **pthread**
- Виконання коду за допомогою **OpenMP**
- Версія програми на **C++** з використанням **std::thread**
- Аналіз продуктивності за допомогою утиліти **time** та перевірки витоку пам'яті через **valgrind**

## Програмні вимоги

- Середовище запуску - термінал Linux (btw у цій практичній використовувався Ubuntu через VirtualBox)
- Компілятори - GCC та G++
- Утиліта - Valgrind

## Збірка та запуск

### 1. -pthread

Компіляція програми з явною підтримкою багатопоточності **-pthread**. Програма запускає два модулі, кожен з яких імітує роботу тривалістю 2 секунди

**Компіляція:**
```
gcc -Wall -Wextra -pthread main.c module1.c module2.c -o threaded_program
```

**Запуск:**
```
./threaded_program
```

### 2. OpenMP

**Компіляція:**
```
gcc -Wall -Wextra -fopenmp main_omp.c module1.c module2.c -o threaded_program_omp
```

**Запуск:**
```
./threaded_program_omp
```

### 3. C++ із std::thread

**Компіляція:**
```
g++ -Wall -Wextra -pthread main_cpp.cpp module1.c module2.c -o threaded_program_cpp
```
**Запуск:**
```
./threaded_program_cpp
```
### Аналізи
**Перевірка продуктивності через time**

Для підтвердження паралельного виконання використовувалася команда time. Оскільки кожен з двох модулів виконується 2 секунди, послідовне виконання повинно було зайняти 4 секунди

**Результат виконання:**
```
user@user:~/lab1_4$ time ./threaded_program
Main - starting threads...
Module 1 - 2 sec work...
Module 2 - another 2sec work...
Module 1 - work finished.
Module 2 - work finished.
Main - all threads have finished.

real	0m2.003s
user	0m0.000s
sys	0m0.002s
user@user:~/lab1_4$ time ./threaded_program_omp
Main(OMP) - starting parallel sections...
Module 1 - 2 sec work...
Module 2 - another 2sec work...
Module 1 - work finished.
Module 2 - work finished.
Main(OMP) - all sections finished.

real	0m2.011s
user	0m0.000s
sys	0m0.002s
```
Час ```real 2.003s``` підтверджує, що потоки виконувалися одночасно

**Перевірка пам'яті через Valgrind**

**Аналіз на наявність витоків пам'яті та помилок потоків:**
```
user@user:~/lab1_4$ valgrind ./threaded_program_omp
==2364== Memcheck, a memory error detector
==2364== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==2364== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==2364== Command: ./threaded_program_omp
==2364== 
Main(OMP) - starting parallel sections...
Module 1 - 2 sec work...
Module 2 - another 2sec work...
Module 1 - work finished.
Module 2 - work finished.
Main(OMP) - all sections finished.
==2364== 
==2364== HEAP SUMMARY:
==2364==     in use at exit: 2,416 bytes in 6 blocks
==2364==   total heap usage: 7 allocs, 1 frees, 3,440 bytes allocated
==2364== 
==2364== LEAK SUMMARY:
==2364==    definitely lost: 0 bytes in 0 blocks
==2364==    indirectly lost: 0 bytes in 0 blocks
==2364==      possibly lost: 288 bytes in 1 blocks
==2364==    still reachable: 2,128 bytes in 5 blocks
==2364==         suppressed: 0 bytes in 0 blocks
==2364== Rerun with --leak-check=full to see details of leaked memory
==2364== 
==2364== For lists of detected and suppressed errors, rerun with: -s
==2364== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
Результат показав відсутність критичних помилок - ```ERROR SUMMARY: 0 errors```

### Результат

При успішному запуску будь-якої з версій програми, виводиться повідомлення про старт та завершення потоків, буде лише змінюватися ця частина виводу - ```Main; Main(OMP); Main(C++)...```:
```
Main - starting threads...
Module 1 - 2 sec work...
Module 2 - another 2sec work...
Module 1 - work finished.
Module 2 - work finished.
Main - all threads have finished.
```

## Висновки

У цій роботі було продемонстровано принципи системного програмування, зокрема безпосереднє керування ресурсами процесора.
Ефективність підходу було підтверджено у терміналі за допомогою команди **time** - скорочення часу виконання вдвічі засвідчило, що планувальник ОС успішно розподілив навантаження між ядрами.

Реалізацію виконано на Linux, оскільки в цій системі потоки працюють дуже ефективно і майже не навантажують систему при запуску.
Це робить Linux ідеальною платформою для серверного програмного забезпечення, де потрібно обробляти тисячі запитів одночасно.

Окрему увагу було приділено роботі з пам'яттю. Оскільки потоки використовують спільний буфер у віртуальному адресному просторі, для перевірки безпеки даних та відсутності витоків пам'яті було застосовано утиліту **valgrind**.


