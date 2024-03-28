CC = gcc
CFLAGS = -Wall -Werror -Wextra 

all: s21_cat

rebuild: clean all

s21_cat: clean main.o parsing.o execution.o
	$(CC) $(CFLAGS) main.o parsing.o execution.o -o s21_cat

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

parsing.o: parsing.c
	$(CC) -c $(CFLAGS) parsing.c

execution.o: execution.c
	$(CC) -c $(CFLAGS) execution.c

clang:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	rm -rf .clang-format

clang_review:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	rm -rf .clang-format

clean:
	-rm *.o
	-rm s21_cat