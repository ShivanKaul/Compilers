compile: tiny.l tiny.y
	bison -d tiny.y
	bison --verbose --debug tiny.y
	flex tiny.l
	gcc -o minic lex.yy.c tiny.tab.c -ll -w 

clean: 
	rm *.c *.h
