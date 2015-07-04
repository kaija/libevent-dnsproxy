
OBJS=dnsproxy.o
EXEC=dnsproxy.exe

CFLAGS= -Wall
LDFLAGS=-levent

.PHONY: all
all: $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o dnsproxy
