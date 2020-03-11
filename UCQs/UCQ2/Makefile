ucq_test : ucq_test.o 
	g++ -std=c++14 -O3 -o ucq_test ucq_test.o -DINVERSE_MAPPING
	rm ucq_test.o

ucq_test.o : ucq_test.cpp
	g++ -std=c++14 -O3 -c ucq_test.cpp -DINVERSE_MAPPING



maxdelay : ucq_test_maxdelay.o
	g++ -std=c++14 -O3 -o maxdelay ucq_test_maxdelay.o -DINVERSE_MAPPING
	rm ucq_test_maxdelay.o

ucq_test_maxdelay.o : ucq_test_maxdelay.cpp
	g++ -std=c++14 -O3 -c ucq_test_maxdelay.cpp -DINVERSE_MAPPING



clean :
	rm ucq_test 2> /dev/null > /dev/null
	rm ucq_test_maxdelay 2> /dev/null > /dev/null
