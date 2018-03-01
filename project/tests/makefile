PB=../../pb/gmserver
PROTOBUF=../../protobuf-2.5.0
INC=-I./ -I$(PB)/ -I$(PROTOBUF)/src
CFLAGS=-Wall
TARGET=Client_test

OBJ=Client_test.o\
	$(PB)/GmServer.pb.o
OBJ+=$(PROTOBUF)/src/.libs/libprotobuf.a

$(TARGET):$(OBJ)
	$(CXX) $(CFLAGS) -o $@ $^
%.o:%.cc
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<
%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -f *.o
	rm -f $(PB)/*.o
	rm -f $(TARGET)


