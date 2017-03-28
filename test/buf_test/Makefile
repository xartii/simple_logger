CC=g++
CPPFLAGS=-ggdb
LDFLAGS=-lssl -lcrypto

buf_test: logmsg.o buf_test.o functions.o
	$(CC) -o $@ $^ $(CPPFLAGS) $(LDFLAGS)

logmsg.o: logmsg.cpp logmsg.hpp
	$(CC) -o $@ -c logmsg.cpp $(CPPFLAGS)

buf_test.o: buf_test.cpp
	$(CC) -o $@ -c $^ $(CPPFLAGS)

functions.o: functions.cpp functions.hpp
	$(CC) -o $@ -c functions.cpp $(CPPFLAGS)

clean:
	rm *.o
	rm buf_test
