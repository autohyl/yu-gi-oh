BASE = ../../
BASELIB = ../../muduo/lib
INC = -I./ -I$(BASE)
x86_64 = 0
SYSBIT = $(shell getconf LONG_BIT)
ifeq ($(SYSBIT),64)
	x86_64 = 1
endif

ifeq ($(x86_64),0)
	CFLAGS = -g -Wall -fno-strict-aliasing -D_GNU_SOURCE -DSNACC_DEEP_COPY -DHAVE_VARIABLE_SIZED_AUTOMATIC_ARRAYS
else
	CFLAGS = -g -Wall -fno-strict-aliasing -D_GNU_SOURCE -fPIC -DSNACC_DEEP_COPY -DHAVE_VARIABLE_SIZED_AUTOMATIC_ARRAYS
endif
CFLAGS += -DJSON_USE_SIMPLE_INTERNAL_ALLOCATOR

LIB += $(BASELIB)/libmuduo_net.a $(BASELIB)/libmuduo_base.a -lpthread
TARGET = $(shell pwd | xargs basename -a)

#SRCS = $(wildcard ./*.cpp)
SRCS += $(wildcard ./*.cc)
#OBJ = $(patsubst %.cpp, %.o, $(SRCS))
OBJ += $(patsubst %.cc, %.o, $(SRCS))


$(TARGET):$(OBJ)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB)

%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<

%.o:%.cc
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -f *.o
	rm -f $(TARGET)

all:
	@echo $(OBJ)
	@echo $(SRCS)
