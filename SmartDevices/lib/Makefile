all: libSmartDevices.a

LINK_CPP=g++
LINK_LIB=ar rcs
LINK_FLAGS=

libSmartDevices.a: SmartPlugs/HS105.o
	$(LINK_LIB) $(LINK_FLAGS) $@ $^

SmartPlugs/HS105.o:
	cd SmartPlugs; $(MAKE)

clean:
	-rm -f libSmartDevices.a
	cd SmartPlugs; $(MAKE) clean
