enum_test : Q9_enumeration_test.o 
	g++ -std=c++14 -O3 -o enum_test Q9_enumeration_test.o
	rm Q9_enumeration_test.o

Q9_enumeration_test.o : Q9_enumeration_test.cpp
	g++ -std=c++14 -O3 -c Q9_enumeration_test.cpp


timing_test : Q9_timing_test.o
	g++ -std=c++14 -O3 -o timing_test Q9_timing_test.o
	rm Q9_timing_test.o

Q9_timing_test.o : Q9_timing_test.cpp
	g++ -std=c++14 -O3 -c Q9_timing_test.cpp


log : Q9_log.o 
	g++ -std=c++14 -O3 -o log Q9_log.o
	rm Q9_log.o

Q9_log.o : Q9_enumeration_test.cpp
	g++ -std=c++14 -O3 -c -DPRINT -o Q9_log.o Q9_enumeration_test.cpp



clean :
	rm enum_test 2> /dev/null > /dev/null
	rm timing_test 2> /dev/null > /dev/null
	rm log 2> /dev/null > /dev/null
  
