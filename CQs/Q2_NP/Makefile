enum_test : Q2_NP_enumeration_test.o 
	g++ -std=c++14 -O3 -o enum_test Q2_NP_enumeration_test.o
	rm Q2_NP_enumeration_test.o

Q2_NP_enumeration_test.o : Q2_NP_enumeration_test.cpp
	g++ -std=c++14 -O3 -c Q2_NP_enumeration_test.cpp


timing_test : Q2_NP_timing_test.o
	g++ -std=c++14 -O3 -o timing_test Q2_NP_timing_test.o
	rm Q2_NP_timing_test.o

Q2_NP_timing_test.o : Q2_NP_timing_test.cpp
	g++ -std=c++14 -O3 -c Q2_NP_timing_test.cpp


log : Q2_NP_log.o 
	g++ -std=c++14 -O3 -o log Q2_NP_log.o
	rm Q2_NP_log.o

Q2_NP_log.o : Q2_NP_enumeration_test.cpp
	g++ -std=c++14 -O3 -c -DPRINT -o Q2_NP_log.o Q2_NP_enumeration_test.cpp



clean :
	rm enum_test 2> /dev/null > /dev/null
	rm timing_test 2> /dev/null > /dev/null
	rm log 2> /dev/null > /dev/null
  
