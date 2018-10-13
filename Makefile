all:	lab7

lab7:	cscd340lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./history/history.o
	gcc -g cscd340lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./history/history.o -o ussh

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

history.o: ./history/history.c ./history/history.h
	gcc -g -c ./history/history.c

clean:
	rm ./pipes/pipes.o	
	rm ./utils/myUtils.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./history/history.o
	rm ussh

