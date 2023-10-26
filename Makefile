.Phony: start
start: processor.o stack_func.o
	clang++ processor.o stack_func.o -o processor
processor.o: processor.cpp processor.h commands.h stack_func.h
	clang++ -c processor.cpp
stack_func.o: stack_func.cpp processor.h commands.h stack_func.h
	clang++ -c stack_func.cpp


