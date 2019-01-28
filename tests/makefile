
IDIR=../include
SDIR=../src
ODIR=../obj
LDIR=../lib

CC=cc
CFLAGS=-I$(IDIR)
LIBS=-llua -ldl -lm

DEPS=$(wildcard $(IDIR)/*.h)

TSRC=$(wildcard *.c)
TOBJ=$(patsubst %.c, $(ODIR)/%.o, $(TSRC))
_SRC=$(wildcard $(SDIR)/*.c)
SRC=$(filter-out $(SDIR)/bigben.c, $(_SRC))
_OBJ=$(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRC))
OBJ=$(_OBJ) $(TOBJ)

tests: $(TOBJ)
	cd $(SDIR) && $(MAKE)
	rm -f $(ODIR)/bigben.o
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LIBS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
	rm -f test
	cd $(SDIR) && $(MAKE) clean
