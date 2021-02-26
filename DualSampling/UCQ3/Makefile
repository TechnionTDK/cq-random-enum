UCQ3_Main : UCQ3_Main.o 
	g++ -std=c++14 -O3 -o DualSampling_UCQ3 UCQ3_Main.o -DINVERSE_MAPPING -DUSING_DUAL_SAMPLING
	rm UCQ3_Main.o

UCQ3_Main.o : UCQ3_Main.cpp
	g++ -std=c++14 -O3 -c UCQ3_Main.cpp -DINVERSE_MAPPING -DUSING_DUAL_SAMPLING
	

UCQ3_Main_Debug : UCQ3_Main_Debug.o 
	g++ -std=c++14 -g -o DualSampling_UCQ3 UCQ3_Main.o -DINVERSE_MAPPING -DUSING_DUAL_SAMPLING
	rm UCQ3_Main.o

UCQ3_Main_Debug.o : UCQ3_Main.cpp
	g++ -std=c++14 -g -c UCQ3_Main.cpp -DINVERSE_MAPPING -DUSING_DUAL_SAMPLING
