etapa6: lex.yy.o main.o m_hash.o y.tab.o astree.o tac.o machine_code_gen.o
	gcc -o etapa6 tac.o lex.yy.o m_hash.o astree.o main.o y.tab.o machine_code_gen.o

teste: tac.o teste.o m_hash.o machine_code_gen.o 
	gcc -o teste.out teste.o tac.o m_hash.o machine_code_gen.o

teste.o: teste.c 
	gcc -c teste.c

astree.o: astree.c
	gcc -c astree.c

machine_code_gen.o: machine_code_gen.c
	gcc -c machine_code_gen.c

y.tab.o: y.tab.c
	gcc -c y.tab.c
	
y.tab.c: parser.y
	yacc -dv --verbose parser.y

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
	rm lex.yy.c etapa* lex.yy.h y.tab* *.o *.s