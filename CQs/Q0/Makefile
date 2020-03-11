enum_test : Q0_enumeration_test.o 
	g++ -std=c++14 -O3 -o enum_test Q0_enumeration_test.o
	rm Q0_enumeration_test.o

Q0_enumeration_test.o : Q0_enumeration_test.cpp
	g++ -std=c++14 -O3 -c Q0_enumeration_test.cpp


timing_test : Q0_timing_test.o
	g++ -std=c++14 -O3 -o timing_test Q0_timing_test.o
	rm Q0_timing_test.o

Q0_timing_test.o : Q0_timing_test.cpp
	g++ -std=c++14 -O3 -c Q0_timing_test.cpp


log : Q0_log.o 
	g++ -std=c++14 -O3 -o log Q0_log.o
	rm Q0_log.o

Q0_log.o : Q0_enumeration_test.cpp
	g++ -std=c++14 -O3 -c -DPRINT -o Q0_log.o Q0_enumeration_test.cpp

clean :
	rm enum_test 2> /dev/null > /dev/null
	rm timing_test 2> /dev/null > /dev/null
	rm log 2> /dev/null > /dev/null
  
