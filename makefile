OBJ = screen.o testscreen.o comm.o
APPNAME = screentest

$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lcurl

%.o : %.c
	gcc -c -o $@ $<

clean:
	rm $(APPNAME) $(OBJ)

zip:
	tar cf appdev.tar *.c *.h makefile
