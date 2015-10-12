CC  = g++
CFLAGS = -c -g -Wall
LEX	= flex
YACC	= bison
YFLAG = -d --debug --verbose
LFLAG =
LIBS = -ll -ly
SRCS = driver.cpp lex.yy.c y.tab.c Debugger.cpp Type.cpp SymbolNode.cpp SymbolTable.cpp
OBJS = driver.o lex.yy.o y.tab.o Debugger.o Type.o SymbolNode.o SymbolTable.o

compiler: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

y.tab.c: comp.y
	$(YACC) $(YFLAG) -o y.tab.c $<

lex.yy.c: comp.lex y.tab.c
	$(LEX) $(LFLAG) $<

clean:
	-rm -f compiler lex.yy.* y.tab.* y.output *.o  *~

.SUFFIXES: .cpp .c .o

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
