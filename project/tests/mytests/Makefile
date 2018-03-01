CC = g++
FLAG = -g 
PROTOBUF = ../../../protobuf-2.5.0/
PB = ../../../pb/gmserver/
INCLUDE = -I./ -I$(PB) -I$(PROTOBUF)src -I../
LIBDIR = 
LIB = $(PROTOBUF)src/.libs/libprotobuf.a -lz
BIN = 
TARGET = pb_test
SRCS =  pb_test.cc \
		$(PB)GmServer.pb.cc

$(TARGET):$(SRCS:.cc=.o)
	$(CC) $(FLAG) -o $@ $^ $(LIBDIR) $(LIB)

%.o:%.cpp
	$(CC) $(FLAG) $(INCLUDE) -c -o $@ $<

%.o:%.cc
	$(CC) $(FLAG) $(INCLUDE) -c -o $@ $<

clean:
	-rm -f $(PB)*.o
	-rm -f *.o
	-rm -f $(TARGET)

