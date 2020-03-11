enum_test : Q10_enumeration_test.o 
	g++ -std=c++14 -O3 -o enum_test Q10_enumeration_test.o
	rm Q10_enumeration_test.o

Q10_enumeration_test.o : Q10_enumeration_test.cpp
	g++ -std=c++14 -O3 -c Q10_enumeration_test.cpp


timing_test : Q10_timing_test.o
	g++ -std=c++14 -O3 -o timing_test Q10_timing_test.o
	rm Q10_timing_test.o

Q10_timing_test.o : Q10_timing_test.cpp
	g++ -std=c++14 -O3 -c Q10_timing_test.cpp


log : Q10_log.o 
	g++ -std=c++14 -O3 -o log Q10_log.o
	rm Q10_log.o

Q10_log.o : Q10_enumeration_test.cpp
	g++ -std=c++14 -O3 -c -DPRINT -o Q10_log.o Q10_enumeration_test.cpp



clean :
	rm enum_test 2> /dev/null > /dev/null
	rm timing_test 2> /dev/null > /dev/null
	rm log 2> /dev/null > /dev/null
  
