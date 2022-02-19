CXX := clang++
CFLAGS := -std=c++17
LIBS := -lgtest -lpthread -lelf -lz

STATIC_LIB := ../bpf/.output/libbpf.a
INCDIRS1 := -I ../bpf/.output
INCDIRS2 :=  -I ../

# same path of THIS Makefile
# SRCDIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
# OBJS := $(shell find $(SRCDIR) -name '*.cc' | sort)
# OBJS := $(patsubst %.cc, %.o, $(OBJS))

CFLAGS += $(STATIC_LIB)
CFLAGS += $(INCDIRS)

obj := $(basename $(wildcard *.cc))


.PHONY: all
all: $(obj)
 
	 
$(obj):   
	-$(CXX) $(CFLAGS) $(addsuffix .cc, $@) ../$(patsubst %_test,%.o, $@) $(STATIC_LIB)  $(INCDIRS1) $(INCDIRS2) $(LIBS) -o $@

.PHONY: clean
clean:
	rm ${obj}

# clang++ -std=c++17 BpfLoader_test.cc -lgtest -lpthread -lelf -lz ../bpf/.output/libbpf.a -I ../bpf/.output ../BpfLoader.o -I ../ -o BpfLoader_test