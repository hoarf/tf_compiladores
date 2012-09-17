
etapa1: lex.yy.o main.o m_hash.o
	gcc -o etapa1 lex.yy.o m_hash.o main.o

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l
main.o: main.c
	gcc -c main.c
m_hash.o: m_hash.c
	gcc -c m_hash.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
clean:
	rm *.o lex.yy.c etapa1