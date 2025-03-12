CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = Double.c Integer.c Interface.c LinearForm.c main.c Tests.c
HEADERS = Double.h Integer.h Interface.h LinearForm.h LinearFormErrors.h Tests.h TypeInfo.h
OBJS = $(SRCS:.c=.o)

TARGET = result

.PHONY: all clean cleanall rebuild run rerun

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q /F $(OBJS)

cleanall:
	del /Q /F $(OBJS) $(TARGET).exe

rebuild:
	make cleanall
	make

run:
	.\$(TARGET)

rerun:
	make rebuild
	make run