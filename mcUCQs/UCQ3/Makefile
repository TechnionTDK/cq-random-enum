mcucq3 : mcucq3.o 
	g++ -std=c++14 -O3 -o mcucq3 mcucq3.o -DINVERTED_ACCESS
	rm mcucq3.o

mcucq3.o : mcUCQ3_main.cpp
	g++ -std=c++14 -O3 -o mcucq3.o -c mcUCQ3_main.cpp -DINVERTED_ACCESS

 
mcucq3_maxdelay : mcucq3_maxdelay.o 
	g++ -std=c++14 -O3 -o mcucq3_maxdelay mcucq3_maxdelay.o -DINVERTED_ACCESS
	rm mcucq3_maxdelay.o

mcucq3_maxdelay.o : mcUCQ3_maxdelay.cpp
	g++ -std=c++14 -O3 -o mcucq3_maxdelay.o -c mcUCQ3_maxdelay.cpp -DINVERTED_ACCESS


clean :
	rm mcucq3 2> /dev/null > /dev/null
