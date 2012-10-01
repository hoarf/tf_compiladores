
etapa2: lex.yy.o main_etapa2.o m_hash.o y.tab.o 
	gcc -o etapa2 lex.yy.o m_hash.o main_etapa2.o y.tab.o

etapa1: lex.yy.o main.o m_hash.o
	gcc -o etapa1 lex.yy.o m_hash.o main.o

y.tab.o: y.tab.c
	gcc -c y.tab.c
	
y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l
	
main.o: main.c
	gcc -c main.c

main_estapa2.o: main_etapa2.c
	gcc -c main_etapa2.c
	
m_hash.o: m_hash.c
	gcc -c m_hash.c
	
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
	
clean:
	rm *.o lex.yy.c etapa2 lex.yy.h y.tab*