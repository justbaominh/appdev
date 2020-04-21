OBJ = screen.o main.o comm.o sound.o
APPNAME = sound

$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lcurl -lm

%.o : %.c
	gcc -c -o $@ $<

clean:
	rm $(APPNAME) $(OBJ)

zip:
	tar cf appdev.tar *.c *.h makefile
