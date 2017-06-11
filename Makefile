# Regions Makefile

CC = clang
CFLAGS = -g -Wall -DNDEBUG

OBJDIR = object
OBJS0 = $(OBJDIR)/regions.o $(OBJDIR)/regionsList.o $(OBJDIR)/blocks.o $(OBJDIR)/test0.o
OBJS1 = $(OBJDIR)/regions.o $(OBJDIR)/regionsList.o $(OBJDIR)/blocks.o $(OBJDIR)/test1.o
OBJS2 = $(OBJDIR)/regions.o $(OBJDIR)/regionsList.o $(OBJDIR)/blocks.o $(OBJDIR)/test2.o
OBJS3 = $(OBJDIR)/regions.o $(OBJDIR)/regionsList.o $(OBJDIR)/blocks.o $(OBJDIR)/test3.o
OBJS4 = $(OBJDIR)/regions.o $(OBJDIR)/regionsList.o $(OBJDIR)/blocks.o $(OBJDIR)/test4.o
OBJS5 = $(OBJDIR)/regions.o $(OBJDIR)/regionsList.o $(OBJDIR)/blocks.o $(OBJDIR)/test5.o
OBJS6 = $(OBJDIR)/regions.o $(OBJDIR)/regionsList.o $(OBJDIR)/blocks.o $(OBJDIR)/test6.o
OBJS7 = $(OBJDIR)/regions.o $(OBJDIR)/regionsList.o $(OBJDIR)/blocks.o $(OBJDIR)/test7.o
OBJS8 = $(OBJDIR)/regions.o $(OBJDIR)/regionsList.o $(OBJDIR)/blocks.o $(OBJDIR)/main.o

# compiling rules
regions: $(OBJS8) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS8) -o regions

test0Run: $(OBJS0) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS0) -o test0Run

test1Run: $(OBJS1) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS1) -o test1Run

test2Run: $(OBJS2) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS2) -o test2Run

test3Run: $(OBJS3) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS3) -o test3Run

test4Run: $(OBJS4) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS4) -o test4Run

test5Run: $(OBJS5) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS5) -o test5Run

test6Run: $(OBJS6) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS6) -o test6Run

test7Run: $(OBJS7) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS7) -o test7Run

$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(PROG) $(OBJS0) $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7) $(OBJS8)

