UCQ1_Main : UCQ1_Main.o 
	g++ -std=c++14 -O3 -o ProbabillisticCounting_UCQ1 UCQ1_Main.o -DINVERSE_MAPPING -DNDEBUG
	rm UCQ1_Main.o

UCQ1_Main.o : UCQ1_Main.cpp
	g++ -std=c++14 -O3 -c UCQ1_Main.cpp -DINVERSE_MAPPING -DNDEBUG
	

UCQ1_Main_Debug : UCQ1_Main_Debug.o 
	g++ -std=c++14 -g -o ProbabillisticCounting_UCQ1 UCQ1_Main.o -DINVERSE_MAPPING
	rm UCQ1_Main.o

UCQ1_Main_Debug.o : UCQ1_Main.cpp
	g++ -std=c++14 -g -c UCQ1_Main.cpp -DINVERSE_MAPPING


UCQ1_Incremental : UCQ1_MainIncremental.o 
	g++ -std=c++14 -O3 -o ProbabillisticCountingIncremental_UCQ1 UCQ1_MainIncremental.o -DINVERSE_MAPPING -DNDEBUG
	rm UCQ1_MainIncremental.o

UCQ1_MainIncremental.o : UCQ1_MainIncremental.cpp
	g++ -std=c++14 -O3 -c UCQ1_MainIncremental.cpp -DINVERSE_MAPPING -DNDEBUG


UCQ1_Timer : UCQ1_MainTimer.o 
	g++ -std=c++14 -O3 -o ProbabillisticCountingTimer_UCQ1 UCQ1_MainTimer.o -DINVERSE_MAPPING -DNDEBUG -DTIMER
	rm UCQ1_MainTimer.o

UCQ1_MainTimer.o : UCQ1_MainTimer.cpp
	g++ -std=c++14 -O3 -c UCQ1_MainTimer.cpp -DINVERSE_MAPPING -DNDEBUG -DTIMER