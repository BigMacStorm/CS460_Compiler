# Compiles and links together the whore program
# This can be modifed as needed

CC	= cc
LEX	= flex
YACC	= bison
LIBS	= -L/usr/local/lib -lfl

OBJS	= lex.yy.o comp.tab.o
TESTOBJS	= driver.o lex.yy.o

comp: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

testscan: $(TESTOBJS) comp.tab.h
	$(CC) -o $@ $(TESTOBJS) $(LIBS)

comp.tab.c: comp.y
	$(YACC) -d $<

lex.yy.c: comp.lex comp.tab.c
	$(LEX) $<

clean:
	-rm -f lex.yy.* comp.tab.* *.o comp testscan *~

.SUFFIXES: .c .o

.c.o:
	$(CC) -c $< -o $@
