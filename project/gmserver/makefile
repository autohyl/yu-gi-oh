BASE = ../../
BASELIB = ../../muduo/lib
PB = ../../pb/gmserver/
PROTOBUF = ../../protobuf-2.5.0/
HANDLE = ./handle/
INC = -I./ -I$(BASE) -I$(BASE)core -I$(BASE)database -I$(PB) -I$(PROTOBUF)src -I$(HANDLE)
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
CFLAGS += -DMUDUO_STD_STRING -DJSON_USE_SIMPLE_INTERNAL_ALLOCATOR `mysql_config --cflags`

LIB += $(BASELIB)/libmuduo_net.a $(BASELIB)/libmuduo_base.a -lpthread -ldl -llua $(PROTOBUF)src/.libs/libprotobuf.a `mysql_config --libs`
TARGET = $(shell pwd | xargs basename -a)

#SRCS = $(wildcard ./*.cpp)
SRCS += $(wildcard ./*.cc)
#OBJ = $(patsubst %.cpp, %.o, $(SRCS))
OBJ += $(patsubst %.cc, %.o, $(SRCS))

OBJ += $(BASE)core/ConfigFileRead.o\
		$(BASE)core/phelper.o\
		$(BASE)core/RegLua/RegLua.o\
		$(BASE)database/cmysql.o\
		$(BASE)json/json_value.o\
		$(BASE)json/json_reader.o\
		$(BASE)json/json_writer.o\
		$(HANDLE)/handleFactory.o\
		$(HANDLE)/loginHandle.o\
		$(PB)GmServer.pb.o

$(TARGET):$(OBJ)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB)

%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<

%.o:%.cc
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -f *.o
	rm -f $(BASE)core/*.o
	rm -f $(BASE)database/*.o
	rm -f $(HANDLE)*.o
	rm -f $(PB)*.o
	rm -f $(TARGET)
all:
	@echo $(OBJ)
	@echo $(SRCS)
