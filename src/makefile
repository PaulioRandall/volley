
IDIR=../include
ODIR=../obj
LDIR=../lib

CC=cc
CFLAGS=-I$(IDIR)
LIBS=-llua -ldl -lm

DEPS=$(wildcard $(IDIR)/*.h)

SRC=$(wildcard *.c)
_OBJ=$(patsubst %.c, %.o, $(SRC))
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bigben: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
	rm -f bigben
