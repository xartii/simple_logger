CPP_FLAGS="-ggdb"

log_test: log_main.o logmsg.o
	g++ -o log_test log_main.o logmsg.o -lssl -lcrypto ${CPP_FLAGS}

log_main.o: log_main.cpp logmsg.hpp
	g++ -c -o log_main.o log_main.cpp ${CPP_FLAGS}

logmsg.o: logmsg.cpp logmsg.hpp
	g++ -c -o logmsg.o logmsg.cpp ${CPP_FLAGS}

clean:
	rm *.o log_test
