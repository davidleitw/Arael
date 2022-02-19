
MAKE	= make
SUBDIRS = lib
all:
	-for i in $(SUBDIRS); do $(MAKE) -C $$i || exit 1; done

clean:
	-for i in $(SUBDIRS); do $(MAKE) -C $$i clean || exit 1; done
