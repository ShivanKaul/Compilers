CFLAGS = -ll  
CFLAGSw = $(CFLAGS) -w
FILES = lex.yy.c tiny.tab.c tree.c pretty.c main.c symbol.c typecheck.c code.c memory.c
OUTPUT =  minic
CC = gcc 

compileall: 
	make process
	make compile

nowarning: 
	make process
	make compilew

process: tiny.l tiny.y
	bison -d tiny.y
	bison --verbose --debug tiny.y
	flex tiny.l

compile:
	$(CC) -o $(OUTPUT) $(FILES) $(CFLAGS)

compilew: 
	 $(CC) -o $(OUTPUT) $(FILES) $(CFLAGSw)

clean: 
	rm *.c *.h *.output
