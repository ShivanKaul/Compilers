CFLAGS = -ll 
CFLAGSw = $(CFLAGS) -w

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
	gcc -o minic lex.yy.c tiny.tab.c $(CFLAGS)

compilew: 
	gcc -o minic lex.yy.c tiny.tab.c $(CFLAGSw)

clean: 
	rm *.c *.h *.output
