# C++ Programming Language - Compiler

C++ References

-   [https://www.learncpp.com/](learncpp)
-   [https://en.cppreference.com/w/](cppreference)
-   [http://www.cplusplus.com/doc/tutorial](cplusplus)

## C++ Compilation Process

1. Source & Header files are run through pre-processor
2. Pre-processor output is run through the C++ compiler
3. Object files are created
4. Object files are linked together
5. Executable files are created.

View the results of pre-processing with -E

```sh
g++ -E myprog.c > myprog.s
```

Compile to an object file with -c

```sh
g++ -c myprog.c
```

Objects then linked to single executable

```sh
g++ -o myprog myprog1.o myprog2.o
```
