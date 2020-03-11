mcucq1 : mcucq1.o 
	g++ -std=c++14 -O3 -o mcucq1 mcucq1.o -DINVERTED_ACCESS
	rm mcucq1.o

mcucq1.o : mcUCQ1_main.cpp
	g++ -std=c++14 -O3 -o mcucq1.o -c mcUCQ1_main.cpp -DINVERTED_ACCESS
 
 
mcucq1_maxdelay : mcucq1_maxdelay.o 
	g++ -std=c++14 -O3 -o mcucq1_maxdelay mcucq1_maxdelay.o -DINVERTED_ACCESS
	rm mcucq1_maxdelay.o

mcucq1_maxdelay.o : mcUCQ1_maxdelay.cpp
	g++ -std=c++14 -O3 -o mcucq1_maxdelay.o -c mcUCQ1_maxdelay.cpp -DINVERTED_ACCESS
 

clean :
	rm mcucq1 2> /dev/null > /dev/null
