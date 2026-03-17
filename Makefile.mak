CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O

all:led.o main.o
	
main.o:main.c
	$(CC) $(CFLAGS) $^ -o $@  
led.o:led.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
