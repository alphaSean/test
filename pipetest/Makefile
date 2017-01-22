TARGET:=piptest

all:$(TARGET)

.PHONY:all clean

$(TARGET):piptest.o
	gcc -g -o $@ $^

piptest.o:piptest.c
	gcc -g -c $^

clean:
	rm -f *.o
	rm -f $(TARGET)
