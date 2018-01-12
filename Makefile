CPPFLAGS += -Wall -Werror -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -I -D_XOPEN_SOURCE
CFLAGS += -std=c11 -lm

DEBUG = -DDEBUG -g

BINS = driver

FILES = driver.o poly.a

all: build

.PHONY: all

poly.a: poly.a(poly.o)

debug: CFLAGS += $(DEBUG)
debug: $(FILES)
    gcc -o $(BINS) $(FILES) $(CPPFLAGS) $(CFLAGS)
    $(MAKE) clean

build: $(FILES)
    gcc -o $(BINS) $(FILES) $(CPPFLAGS) $(CFLAGS)
    $(MAKE) clean

buildAll: debug

clean:
    $(RM) *.o *.a

cleanAll:
    $(RM) $(BINS) *.o *.a
