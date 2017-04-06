CC=g++
CPPFLAGS=-ggdb -std=c++11
LDFLAGS=-lssl -lcrypto

logger_test: logmsg.o logger_test.o logger.o functions.o
	$(CC) -o $@ $^ $(CPPFLAGS) $(LDFLAGS)

logmsg.o: logmsg.cpp logmsg.hpp
	$(CC) -o $@ -c logmsg.cpp $(CPPFLAGS)

logger_test.o: logger_test.cpp
	$(CC) -o $@ -c $^ $(CPPFLAGS)

logger.o: logger.cpp logger.hpp
	$(CC) -o $@ -c logger.cpp $(CPPFLAGS)

functions.o: functions.cpp functions.hpp
	$(CC) -o $@ -c functions.cpp $(CPPFLAGS)


clean:
	rm *.o
	rm buf_test
