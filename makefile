GCC=gcc
FLAGS=-g -Wall -Wextra -std=c99
LIBS=-lpthread
# Add -lrt when using linux

all: jackpot

jackpot: jackpot.o handler.o display.o wheel.o
	$(GCC) $^ -o $@ $(LIBS)

jackpot.o: jackpot.c
	$(GCC) $(FLAGS) $< -c

handler.o: handler.c handler.h
	$(GCC) $(FLAGS) $< -c

display.o: display.c display.h
	$(GCC) $(FLAGS) $< -c

wheel.o: wheel.c wheel.h
	$(GCC) $(FLAGS) $< -c

clean:
	rm *.o jackpot
