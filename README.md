# debug.h
Библиотека для красивого отладочного вывода. Используется для спортивного программирования на языке **_C++_**.

# Как установить?
1. Cкачайте файл и поставьте в той же папке, где и ваш **_source.cpp_** (то есть в той папке, где вы пишете код).
2. В самом коде **_source.cpp_** добавьте следующие строки:
```cpp
#ifdef LOCAL
#   include "debug.h"
#else
#   define debug(...)
#endif
```
Где ```LOCAL``` - это макрос который определяет, что программа запускается у вас на компьютере, а не на тестирующей системе.

# Как использовать?
Пусть у вас есть переменная (например ```pair<int, int> x```). Тогда её значение можете узнать написав:
```cpp
pair<int, int> x = {1, 2};
debug(x);
```
Либо если у вас есть два числа ```a = 1``` и ```b = 2```, то значение выражения ```a + b + 1``` можете узнать так:
```cpp
int a = 1;
int b = 2;
debug(a + b + 1);
```
Если вы хотите увидеть все элементы ```vector```, то можете сделать так:
```cpp
vector A = {1, 2, 3};
debug(A);
```
Такде можно передавать макросу ```debug``` несколько аргументов:
```cpp
char y = 'c';
map<int, string> c = {{1, "a"}, {2, "b"}};
debug(y, c, 1 + 2);
```

В итоге получается следующее:
```cpp
/// @author Camillus
#include <bits/stdc++.h>
#ifdef LOCAL
#   include "debug.h"
#else
#   define debug(...)
#endif
using namespace std;

signed main() {
    pair<int, int> x = {1, 2};
    debug(x);

    int a = 1;
    int b = 2;
    debug(a + b + 1);

    vector A = {1, 2, 3};
    debug(A);

    char y = 'c';
    set<string> c = {"a", "b", "v"};
    debug(y, c, 1 + 2);
    return 0;
}
```
Если запустить, то вывод программы будет следующее:
$$\textcolor{purple}{$ x}$$ = (1, 2)
