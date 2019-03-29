all:	lab7

lab7:	testMain.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./history/history.o ./linkedlist/linkedlist.o ./linkedlist/listUtils.o ./types/word.o ./types/alias.o ./types/string.o ./utils/fileUtils.o
	gcc -g testMain.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./history/history.o ./linkedlist/linkedlist.o ./linkedlist/listUtils.o ./types/word.o ./types/alias.o ./types/string.o ./utils/fileUtils.o -o ussh

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

linkedlist.o: ./linkedlist/linkedlist.c ./linkedlist/linkedlist.h ./linkedlist/requiredIncludes.h
	gcc -g -c ./linkedlist/linkedlist.c

istUtils.o: ./linkedlist/listUtils.c ./linkedlist/listUtils.h
	gcc -g -c ./linkedlist/listUtils.c

word.o: ./types/word.c ./types/word.h
	gcc -g -c ./types/word.c

alias.o: ./types/alias.c ./types/alias.h
	gcc -g -c ./types/alias.c

string.o: ./types/string.c ./types/string.h
	gcc -g -c ./types/string.c

fileUtils.o: ./utils/fileUtils.c ./utils/fileUtils.h
	gcc -g -c ./utils/fileUtils.c

clean:
	rm ./pipes/pipes.o
	rm ./types/word.o
	rm ./types/alias.o	
	rm ./types/string.o
	rm ./utils/myUtils.o
	rm ./utils/fileUtils.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./history/history.o
	rm ./linkedlist/listUtils.o
	rm ./linkedlist/linkedlist.o
	rm ussh

