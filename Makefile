CC=clang
CFLAGS=-g

TARGET = saper

SRCS = main.c plansza1.c plansza2.c plansza3.c
OBJS = main.o plansza1.o plansza2.o plansza3.o

all: $(TARGET)

plansza1.o: plansza1.h plansza1.c
	@$(CC) $(CFLAGS) -c plansza1.c -o plansza1.o

plansza2.o: plansza2.h plansza2.c
	@$(CC) $(CFLAGS) -c plansza2.c -o plansza2.o

plansza3.o: plansza3.h plansza3.c
	@$(CC) $(CFLAGS) -c plansza3.c -o plansza3.o

$(TARGET): main.c plansza1.o plansza2.o plansza3.o
	@$(CC) $(CFLAGS) -o $(TARGET) main.c plansza1.o plansza2.o plansza3.o

clean:
	rm -f $(OBJS) $(TARGET)