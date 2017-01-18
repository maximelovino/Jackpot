GCC=gcc
FLAGS=-g -Wall -Wextra -std=c99
LIBS=-lpthread
# Add -lrt when using linux

all: jackpot

jackpot: jackpot.o handler.o display.o wheel.o timer.o
	$(GCC) $^ -o $@ $(LIBS)

%.o: %.c
	$(GCC) $(FLAGS) $< -c

clean:
	rm *.o jackpot
