compile: tiny.l tiny.y
	flex tiny.l
	bison tiny.y
	gcc -o minic lex.yy.c tiny.tab.c -ll

clean: 
	rm *.c *.h
