enum_test : Q3_enumeration_test.o 
	g++ -std=c++14 -O3 -o enum_test Q3_enumeration_test.o
	rm Q3_enumeration_test.o

Q3_enumeration_test.o : Q3_enumeration_test.cpp
	g++ -std=c++14 -O3 -c Q3_enumeration_test.cpp


timing_test : Q3_timing_test.o
	g++ -std=c++14 -O3 -o timing_test Q3_timing_test.o
	rm Q3_timing_test.o

Q3_timing_test.o : Q3_timing_test.cpp
	g++ -std=c++14 -O3 -c Q3_timing_test.cpp


log : Q3_log.o 
	g++ -std=c++14 -O3 -o log Q3_log.o
	rm Q3_log.o

Q3_log.o : Q3_enumeration_test.cpp
	g++ -std=c++14 -O3 -c -DPRINT -o Q3_log.o Q3_enumeration_test.cpp



clean :
	rm enum_test 2> /dev/null > /dev/null
	rm timing_test 2> /dev/null > /dev/null
	rm log 2> /dev/null > /dev/null
  
