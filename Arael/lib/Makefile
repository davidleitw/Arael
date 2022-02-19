obj := .
SUBDIRS := tests bpf
CFLAGS := -std=c++17
INCDIRS = -I $(obj)/bpf/.output

CXX = clang++

OBJS := $(basename $(wildcard *.cc))

.PHONY: all
all: $(OBJS) 
	 
$(OBJS): $(wildcard *.cc)
	@echo "  $(notdir $<)"
	-$(Q)$(CXX) $(CFLAGS)  -c $(INCDIRS) $^
	-for i in $(SUBDIRS); do $(MAKE) -C $$i || exit 1; done

.PHONY: clean
clean: 
	rm $(wildcard *.o)
	-for i in $(SUBDIRS); do $(MAKE) -C $$i clean || exit 1; done
	

# OBJS := $(shell find *.cc | sort)
# TA := $(patsubst %.cc,%.o,$(OBJS))
