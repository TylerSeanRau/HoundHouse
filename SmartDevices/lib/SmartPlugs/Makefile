all: libSmartPlugs.a

CC=gcc
CFLAGS=
CPP=g++
CPP_FLAGS=
LINK_CPP=g++
LINK_LIB=ar rcs
LINK_FLAGS=

libSmartPlugs.a: HS105.o
	$(LINK_LIB) $(LINK_FLAGS) $@ $^

%.o: %.cpp
	$(CPP) $(CPP_FLAGS) -g -c -o $@ -I../../include -I../../include/SmartPlugs $^

%.o: %.c
	$(CC) $(CFLAGS) -g -c -o $@ -I../../include -I../../include/SmartPlugs $^

clean:
	-rm -f libSmartPlugs.a HS105.o
