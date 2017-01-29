GCC=gcc
FLAGS=-g -Wall -Wextra -std=gnu99
LIBS=-lpthread -lrt
# Add -lrt when using linux

all: jackpot

jackpot: jackpot.o handler.o display.o wheel.o
	$(GCC) $^ -o $@ $(LIBS)

%.o: %.c const.h
	$(GCC) $(FLAGS) $< -c

clean:
	rm *.o jackpot
