CPP_FLAGS="-ggdb"

log_test: log_main.o logmsg.o functions.o
	g++ -o log_test log_main.o logmsg.o functions.o -lssl -lcrypto ${CPP_FLAGS}

log_main.o: log_main.cpp logmsg.hpp
	g++ -c -o log_main.o log_main.cpp ${CPP_FLAGS}

logmsg.o: logmsg.cpp logmsg.hpp
	g++ -c -o logmsg.o logmsg.cpp ${CPP_FLAGS}

functions.o: functions.cpp functions.hpp
	g++ -c -o functions.o functions.cpp ${CPP_FLAGS}
clean:
	rm *.o log_test
