UCQ2_Main : UCQ2_Main.o 
	g++ -std=c++14 -O3 -o DualSampling_UCQ2 UCQ2_Main.o -DINVERSE_MAPPING -DUSING_DUAL_SAMPLING
	rm UCQ2_Main.o

UCQ2_Main.o : UCQ2_Main.cpp
	g++ -std=c++14 -O3 -c UCQ2_Main.cpp -DINVERSE_MAPPING -DUSING_DUAL_SAMPLING
	

UCQ2_Main_Debug : UCQ2_Main_Debug.o 
	g++ -std=c++14 -g -o DualSampling_UCQ2 UCQ2_Main.o -DINVERSE_MAPPING -DUSING_DUAL_SAMPLING
	rm UCQ2_Main.o

UCQ2_Main_Debug.o : UCQ2_Main.cpp
	g++ -std=c++14 -g -c UCQ2_Main.cpp -DINVERSE_MAPPING -DUSING_DUAL_SAMPLING
