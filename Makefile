makeandclean: a.out

a.out: main.cpp *.h
	g++ $<

debug: main.cpp *.h
	g++ -g $< -o a.debug.out

clean:
	-rm -f *.o

cleanall:
	-rm -f a.out a.debug.out
