#EXECS = 
LIBS= -lpthread

all:    main.o util.o deque.o fighter.o
	gcc -o all main.o util.o deque.o fighter.o $(LIBS)

main.o: main.c defs.h 
	gcc -c main.c $(LIBS)
      	
util.o: util.c defs.h
	gcc -c util.c

deque.o: deque.c defs.h
	gcc -c deque.c

fighter.o: fighter.c defs.h
	gcc -c fighter.c

clean:  
	 rm -f all

