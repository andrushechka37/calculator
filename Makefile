.Phony: start
start: processor.o stack_func.o
	clang++ processor.o stack_func.o -o main
processor.o: processor.cpp processor.h
	clang++ -c processor.cpp
stack_func.o: stack_func.cpp processor.h
	clang++ -c stack_func.cpp

