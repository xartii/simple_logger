CC=g++
CPPFLAGS=-ggdb -std=c++11
LDFLAGS=-lssl -lcrypto

server_test: logmsg.o server_test.o logserver.o functions.o
	$(CC) -o $@ $^ $(CPPFLAGS) $(LDFLAGS)

logmsg.o: logmsg.cpp logmsg.hpp
	$(CC) -o $@ -c logmsg.cpp $(CPPFLAGS)

server_test.o: server_test.cpp
	$(CC) -o $@ -c $^ $(CPPFLAGS)

logserver.o: logserver.cpp logserver.hpp
	$(CC) -o $@ -c logserver.cpp $(CPPFLAGS)

functions.o: functions.cpp functions.hpp
	$(CC) -o $@ -c functions.cpp $(CPPFLAGS)


clean:
	rm *.o
	rm server_test
