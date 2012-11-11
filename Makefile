
etapa4: lex.yy.o main.o m_hash.o y.tab.o astree.o
	gcc -o etapa4 lex.yy.o m_hash.o astree.o main.o y.tab.o

astree.o: astree.c
	gcc -c astree.c

y.tab.o: y.tab.c
	gcc -c y.tab.c
	
y.tab.c: parser.y
	yacc -dv parser.y

lex.yy.c: scanner.l y.tab.c
	flex --header-file=lex.yy.h scanner.l
	
main.o: main.c
	gcc -c main.c
	
m_hash.o: m_hash.c
	gcc -c m_hash.c
	
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c	
	
clean:
	rm lex.yy.c etapa* lex.yy.h y.tab* *.o