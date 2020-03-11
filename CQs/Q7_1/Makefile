enum_test : Q7_1_enumeration_test.o 
	g++ -std=c++14 -O3 -o enum_test Q7_1_enumeration_test.o
	rm Q7_1_enumeration_test.o

Q7_1_enumeration_test.o : Q7_1_enumeration_test.cpp
	g++ -std=c++14 -O3 -c Q7_1_enumeration_test.cpp


timing_test : Q7_1_timing_test.o
	g++ -std=c++14 -O3 -o timing_test Q7_1_timing_test.o
	rm Q7_1_timing_test.o

Q7_1_timing_test.o : Q7_1_timing_test.cpp
	g++ -std=c++14 -O3 -c Q7_1_timing_test.cpp


log : Q7_1_log.o 
	g++ -std=c++14 -O3 -o log Q7_1_log.o
	rm Q7_1_log.o

Q7_1_log.o : Q7_1_enumeration_test.cpp
	g++ -std=c++14 -O3 -c -DPRINT -o Q7_1_log.o Q7_1_enumeration_test.cpp



clean :
	rm enum_test 2> /dev/null > /dev/null
	rm timing_test 2> /dev/null > /dev/null
	rm log 2> /dev/null > /dev/null
  
