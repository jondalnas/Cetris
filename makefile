EXEC = ctris.exe
CFLAGS = -Wall
OBJDIR = obj
DEBUG = -DDEBUG -g
OBJS = $(OBJDIR)/main.o

ctris.exe : $(OBJS)
	gcc $(CFLAGS) -o $(EXEC) $(OBJS)

$(OBJDIR)/main.o : 

$(OBJDIR)/%.o : %.c
	gcc -c $(CFLAGS) -o $@ $<