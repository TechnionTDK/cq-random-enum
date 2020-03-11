enum_test : QAE_enumeration_test.o 
	g++ -std=c++14 -O3 -o enum_test QAE_enumeration_test.o
	rm QAE_enumeration_test.o

QAE_enumeration_test.o : QAE_enumeration_test.cpp
	g++ -std=c++14 -O3 -c QAE_enumeration_test.cpp


timing_test : QAE_timing_test.o
	g++ -std=c++14 -O3 -o timing_test QAE_timing_test.o
	rm QAE_timing_test.o

QAE_timing_test.o : QAE_timing_test.cpp
	g++ -std=c++14 -O3 -c QAE_timing_test.cpp


log : QAE_log.o 
	g++ -std=c++14 -O3 -o log QAE_log.o
	rm QAE_log.o

QAE_log.o : QAE_enumeration_test.cpp
	g++ -std=c++14 -O3 -c -DPRINT -o QAE_log.o QAE_enumeration_test.cpp



clean :
	rm enum_test 2> /dev/null > /dev/null
	rm timing_test 2> /dev/null > /dev/null
	rm log 2> /dev/null > /dev/null
  
