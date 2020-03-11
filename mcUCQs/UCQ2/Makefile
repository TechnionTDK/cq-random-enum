mcucq2 : mcucq2.o 
	g++ -std=c++14 -O3 -o mcucq2 mcucq2.o -DINVERTED_ACCESS
	rm mcucq2.o

mcucq2.o : mcUCQ2_main.cpp
	g++ -std=c++14 -O3 -o mcucq2.o -c mcUCQ2_main.cpp -DINVERTED_ACCESS
 
 
mcucq2_maxdelay : mcucq2_maxdelay.o 
	g++ -std=c++14 -O3 -o mcucq2_maxdelay mcucq2_maxdelay.o -DINVERTED_ACCESS
	rm mcucq2_maxdelay.o

mcucq2_maxdelay.o : mcUCQ2_maxdelay.cpp
	g++ -std=c++14 -O3 -o mcucq2_maxdelay.o -c mcUCQ2_maxdelay.cpp -DINVERTED_ACCESS


clean :
	rm mcucq2 2> /dev/null > /dev/null
