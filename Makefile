CPPFLAGS += -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -I -D_XOPEN_SOURCE
CFLAGS += -std=c11 -lm
ARFLAGS += -U

DEBUG = -DDEBUG -g

BINS = driver

FILES = driver.o poly.a

all: $(BINS)

poly.a: poly.a(poly.o)

.PHONY: all build poly.a

debug: CPPFLAGS += -DDEBUG -g
debug:  $(FILES)
	gcc -o $(BINS) $(FILES) $(CPPFLAGS) $(CFLAGS)


build: $(FILES)
	gcc -o $(BINS) $(FILES) $(CPPFLAGS) $(CFLAGS)

clean:
	$(RM) $(BINS) *.o *.a