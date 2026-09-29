## Compilar

Requer MSYS2/MinGW-w64 instalado (g++ e mingw32-make no PATH).

```
mingw32-make
```

Caso de erro, compile manualmente:
```
g++ -O2 -std=c++17 -Wall -Wextra -Iinclude -static -static-libgcc -static-libstdc++ main.cpp src/*.cpp -o programa.exe
```

