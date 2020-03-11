enum_test : QA_enumeration_test.o 
	g++ -std=c++14 -O3 -o enum_test QA_enumeration_test.o
	rm QA_enumeration_test.o

QA_enumeration_test.o : QA_enumeration_test.cpp
	g++ -std=c++14 -O3 -c QA_enumeration_test.cpp


timing_test : QA_timing_test.o
	g++ -std=c++14 -O3 -o timing_test QA_timing_test.o
	rm QA_timing_test.o

QA_timing_test.o : QA_timing_test.cpp
	g++ -std=c++14 -O3 -c QA_timing_test.cpp


log : QA_log.o 
	g++ -std=c++14 -O3 -o log QA_log.o
	rm QA_log.o

QA_log.o : QA_enumeration_test.cpp
	g++ -std=c++14 -O3 -c -DPRINT -o QA_log.o QA_enumeration_test.cpp



clean :
	rm enum_test 2> /dev/null > /dev/null
	rm timing_test 2> /dev/null > /dev/null
	rm log 2> /dev/null > /dev/null
  
