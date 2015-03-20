#***************************************************************************
#             Makefile
# 
#   Tue Mar 10 17:33:22 2009
#   Copyright  2009  Pedro Henrique Neves da Silva
#   Email: ptersnow@gmail.com
#
#***************************************************************************

cc     = gcc
cflags = -g -lm -lrt -lcrypt -O2 -pedantic -Wall -m32

#***************************************************************************

all: clean gen compile
	./bin sample | tee -a bin_out
#	./rec sample | tee -a rec_out
#	./bnb sample | tee -a bnb_out
	./gen sample 50 30 | tee -a gen_out
compile:
#	$(cc) $(cflags) knaprec.c -o rec
	$(cc) $(cflags) knapdyn.c -o bin
#	$(cc) $(cflags) queue.c knapbnb.c -o bnb
	$(cc) $(cflags) knapgen.c -o gen
	
gen:
	$(cc) $(cflags) generator.c -o generator
	./generator

clean:
	rm -f bin rec generator bnb gen

distclean: clean
	rm -f sample sample1 bin_out rec_out bnb_out gen_out

