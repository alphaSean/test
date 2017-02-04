TARGET:=pipetest pipetest2 pipetest3 pipetest4 pipetest5 
CFLAGS:=-Wall -fPIC -g 
all:$(TARGET)

.PHONY:all clean

pipetest:pipetest.o
	gcc $(CFLAGS) -o $@ $^
pipetest2:pipetest2.o
	gcc $(CFLAGS) -o $@ $^
pipetest3:pipetest3.o
	gcc $(CFLAGS) -o $@ $^
pipetest4:pipetest4.o
	gcc $(CFLAGS) -o $@ $^
pipetest5:pipetest5.o my_func.o
	gcc $(CFLAGS) -o $@ $^


clean:
	rm -f *.o
	rm -f $(TARGET)
