compileall: 
	make process
	make compile

compileallW: 
	make process
	make compileW

process: tiny.l tiny.y
	bison -d tiny.y
	bison tiny.y
	flex tiny.l

compileDebug:
	make debug
	make compile

debug: tiny.l tiny.y
	bison -d tiny.y
	bison --verbose --debug tiny.y
	flex tiny.l

compile:
	gcc -o minic lex.yy.c tiny.tab.c -ll

compileW: 
	gcc -o minic lex.yy.c tiny.tab.c -ll -w

clean: 
	rm *.c *.h *.output
