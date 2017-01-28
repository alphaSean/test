TARGET:=pipetest pipetest2 pipetest3
CFLAGS:=-Wall -fPIC -g 
all:$(TARGET)

.PHONY:all clean

pipetest:pipetest.o
	gcc $(CFLAGS) -o $@ $^
pipetest2:pipetest2.o
	gcc $(CFLAGS) -o $@ $^
pipetest3:pipetest3.o
	gcc $(CFLAGS) -o $@ $^

piptest.o:pipetest.c
	gcc $(CFLAGS) -c $^

piptest2.o:pipetest2.c
	gcc $(CFLAGS) -c $^
piptest3.o:pipetest3.c
	gcc $(CFLAGS) -c $^

clean:
	rm -f *.o
	rm -f $(TARGET)
