ucq_test : ucq_test.o 
	g++ -std=c++14 -O3 -o ucq_test ucq_test.o -DINVERSE_MAPPING
	rm ucq_test.o

ucq_test.o : ucq_test.cpp
	g++ -std=c++14 -O3 -c ucq_test.cpp -DINVERSE_MAPPING
 
 
ucq_total_time_test : ucq_total_time_test.o 
	g++ -std=c++14 -O3 -o ucq_total_time_test ucq_total_time_test.o -DINVERSE_MAPPING
	rm ucq_total_time_test.o

ucq_total_time_test.o : ucq_total_time_test.cpp
	g++ -std=c++14 -O3 -c ucq_total_time_test.cpp -DINVERSE_MAPPING
 
 
ucq_split_time_test : ucq_split_time_test.o 
	g++ -std=c++14 -O3 -o ucq_split_time_test ucq_split_time_test.o -DINVERSE_MAPPING -DTIME_COUNT
	rm ucq_split_time_test.o

ucq_split_time_test.o : ucq_split_time_test.cpp
	g++ -std=c++14 -O3 -c ucq_split_time_test.cpp -DINVERSE_MAPPING -DTIME_COUNT
 
 
 

max_delay : ucq_test_maxdelay.o 
	g++ -std=c++14 -O3 -o max_delay ucq_test_maxdelay.o -DINVERSE_MAPPING
	rm ucq_test_maxdelay.o

ucq_test_maxdelay.o : ucq_test_maxdelay.cpp
	g++ -std=c++14 -O3 -c ucq_test_maxdelay.cpp -DINVERSE_MAPPING
 

clean :
	rm ucq_test 2> /dev/null > /dev/null
	rm ucq_total_time_test 2> /dev/null > /dev/null
	rm ucq_split_time_test 2> /dev/null > /dev/null
	rm max_delay 2> /dev/null > /dev/null
