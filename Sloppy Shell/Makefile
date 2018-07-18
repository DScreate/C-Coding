CC=gcc

ush:	cscd340Lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./utils/fileUtil.o ./process/process.o ./pipes/pipes.o ./linkedlist/linkedList.o ./linkedlist/listUtils.o ./alias/alias.o ./history/history.o
	gcc -g cscd340Lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./utils/fileUtil.o ./process/process.o ./pipes/pipes.o ./linkedlist/linkedList.o ./linkedlist/listUtils.o ./alias/alias.o ./history/history.o -o ush

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

fileUtil.o:	./utils/fileUtil.o ./utils/fileUtil.h
	gcc -g -c ./utils/fileUtil.c

process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

alias.o:	./alias/alias.c ./alias/alias.h
	gcc -g -c

history.o:	./history/history.c ./history/history.h
	gcc -g -c

linkedList.o: 	./linkedlist/linkedList.c ./linkedlist/linkedList.h
	gcc -g -c

listUtils.o:	./linkedlist/listUtils.c ./linkedlist/listUtils.h
	gcc -g -c

clean:
	rm ./pipes/pipes.o	
	rm ./utils/myUtils.o
	rm ./utils/fileUtil.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./alias/alias.o
	rm ./history/history.o
	rm ./linkedlist/linkedList.o
	rm ./linkedlist/listUtils.o
	rm ush

