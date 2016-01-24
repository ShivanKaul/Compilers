compile: tiny.l tiny.y
	flex tiny.l
	bison --debug --verbose tiny.y
	gcc -o minic lex.yy.c tiny.tab.c -ll -w

clean: 
	rm *.c *.h
