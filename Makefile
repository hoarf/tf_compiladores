
etapa5: lex.yy.o main.o m_hash.o y.tab.o astree.o tac.o
	gcc -o etapa5 tac.o lex.yy.o m_hash.o astree.o main.o y.tab.o

teste: tac.o teste.o m_hash.o
	gcc -o teste.out teste.o tac.o m_hash.o

teste.o: teste.c
	gcc -c teste.c

astree.o: astree.c
	gcc -c astree.c

y.tab.o: y.tab.c
	gcc -c y.tab.c
	
y.tab.c: parser.y
	yacc -dv parser.y

lex.yy.c: scanner.l y.tab.c
	flex --header-file=lex.yy.h scanner.l
	
tac.o: tac.c
	gcc -c tac.c

main.o: main.c
	gcc -c main.c
	
m_hash.o: m_hash.c
	gcc -c m_hash.c
	
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c	
	
clean:
	rm lex.yy.c etapa* lex.yy.h y.tab* *.o