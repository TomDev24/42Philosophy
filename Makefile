all:
	gcc -fsanitize=thread -g -Wall -Wextra *.c -pthread
