
etapa3: lex.yy.o main_etapa2.o m_hash.o y.tab.o astree.o
	gcc -o etapa3 lex.yy.o m_hash.o astree.o main_etapa2.o y.tab.o

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

main_estapa2.o: main_etapa2.c
	gcc -c main_etapa2.c
	
m_hash.o: m_hash.c
	gcc -c m_hash.c
	
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c


test: astree_test.o astree.o m_hash.o
	gcc -o astree_test astree_test.o astree.o m_hash.o	

astree_test.o: astree_test.c
	gcc -c astree_test.c 
	
	
	
clean:
	rm lex.yy.c etapa2 lex.yy.h y.tab* *.o