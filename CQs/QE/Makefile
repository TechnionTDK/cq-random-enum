enum_test : QE_enumeration_test.o 
	g++ -std=c++14 -O3 -o enum_test QE_enumeration_test.o
	rm QE_enumeration_test.o

QE_enumeration_test.o : QE_enumeration_test.cpp
	g++ -std=c++14 -O3 -c QE_enumeration_test.cpp


timing_test : QE_timing_test.o
	g++ -std=c++14 -O3 -o timing_test QE_timing_test.o
	rm QE_timing_test.o

QE_timing_test.o : QE_timing_test.cpp
	g++ -std=c++14 -O3 -c QE_timing_test.cpp


log : QE_log.o 
	g++ -std=c++14 -O3 -o log QE_log.o
	rm QE_log.o

QE_log.o : QE_enumeration_test.cpp
	g++ -std=c++14 -O3 -c -DPRINT -o QE_log.o QE_enumeration_test.cpp



clean :
	rm enum_test 2> /dev/null > /dev/null
	rm timing_test 2> /dev/null > /dev/null
	rm log 2> /dev/null > /dev/null
  
