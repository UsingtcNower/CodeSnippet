.PHONY: all clean
CC=gcc
CPP=g++
CFLAGS= -g -Wall -Wno-unused-function -std=gnu++0x
SRCDIR = .
INCLUDEDIR = -I./
PROGRAMS =  factory	\
	    singleton	\
	    singleton_local_static_version	\
	    strategy	\
	    strategy_function_bind_version	\
	    template	\
	    observer	\

all: $(PROGRAMS)

%: $(SRCDIR)/%.cc
	$(CPP) $(CFLAGS) -o $@ $< $(INCLUDEDIR)

clean:
	rm -rf $(PROGRAMS) *.dSYM
