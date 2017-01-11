GCC=gcc -g -Wall -Wextra -std=gnu99
LIBS=-lpthread -lrt

all: jackpot

jackpot: jackpot.o handler.o display.o wheel.o
	$(GCC) $^ -o $@ $(LIBS)

jackpot.o: jackpot.c
	$(GCC) $< -c

handler.o: handler.c handler.h
	$(GCC) $< -c

display.o: display.h display.c
	$(GCC) $< -c

wheel.o: wheel.c wheel.h
	$(GCC) $< -c

clean:
	rm *.o jackpot
