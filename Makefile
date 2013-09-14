makeandclean: a.out

a.out: main.cpp *.h
	g++ $<

clean:
	-rm -f *.o
