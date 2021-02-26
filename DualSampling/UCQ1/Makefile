UCQ1_Main : UCQ1_Main.o 
	g++ -std=c++14 -O3 -o DualSampling_UCQ1 UCQ1_Main.o -DINVERSE_MAPPING -DNDEBUG -DUSING_DUAL_SAMPLING
	rm UCQ1_Main.o

UCQ1_Main.o : UCQ1_Main.cpp
	g++ -std=c++14 -O3 -c UCQ1_Main.cpp -DINVERSE_MAPPING -DNDEBUG -DUSING_DUAL_SAMPLING
	

UCQ1_Main_Debug : UCQ1_Main_Debug.o 
	g++ -std=c++14 -g -o DualSampling_UCQ1 UCQ1_Main.o -DINVERSE_MAPPING -DUSING_DUAL_SAMPLING
	rm UCQ1_Main.o

UCQ1_Main_Debug.o : UCQ1_Main.cpp
	g++ -std=c++14 -g -c UCQ1_Main.cpp -DINVERSE_MAPPING -DUSING_DUAL_SAMPLING


UCQ1_Incremental : UCQ1_MainIncremental.o 
	g++ -std=c++14 -O3 -o DualSamplingIncremental_UCQ1 UCQ1_MainIncremental.o -DINVERSE_MAPPING -DNDEBUG -DUSING_DUAL_SAMPLING
	rm UCQ1_MainIncremental.o

UCQ1_MainIncremental.o : UCQ1_MainIncremental.cpp
	g++ -std=c++14 -O3 -c UCQ1_MainIncremental.cpp -DINVERSE_MAPPING -DNDEBUG -DUSING_DUAL_SAMPLING