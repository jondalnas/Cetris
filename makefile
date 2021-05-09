EXEC = cetris.exe
CFLAGS = -Wall
OBJDIR = obj
DEBUG = -DDEBUG -g
OBJS = $(OBJDIR)/main.o $(OBJDIR)/grid.o $(OBJDIR)/piece.o

$(EXEC) : $(OBJS)
	gcc $(CFLAGS) -o $(EXEC) $(OBJS)

$(OBJDIR)/main.o : grid.h piece.h
$(OBJDIR)/grid.o : grid.h
$(OBJDIR)/piece.o : piece.h grid.h

$(OBJDIR)/%.o : %.c
	gcc -c $(CFLAGS) -o $@ $<