CLANG := clang++
STANDARD := -std=c++17
LIBS := -lgtest -lpthread -lelf -lz

STATIC_LIB := ../bpf/.output/libbpf.a
INCDIRS1 := ../bpf/.output
INCDIRS2 := ../

# same path of THIS Makefile
SRCDIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
OBJS := $(shell find $(SRCDIR) -name '*.cc' | sort)
# OBJS := $(patsubst %.cc, %.o, $(OBJS))

CFLAGS += $(STATIC_LIB)
CFLAGS += $(INCDIRS)

obj := $(basename $(wildcard *.cc))

.PHONY: all
all: $(obj)
	
$(obj): 
	$(CLANG) $(STANDARD) $(addsuffix .cc, $@) $(LIBS) $(STATIC_LIB) -I $(INCDIRS1) -I $(INCDIRS2) $(LIBS) -o $@

.PHONY: clean
clean:
	rm ${obj}