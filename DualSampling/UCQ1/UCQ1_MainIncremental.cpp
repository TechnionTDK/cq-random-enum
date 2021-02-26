#ifndef RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H
#define RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H

#include <chrono>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>

#include "UCQAnswer.h"

#include "../DualSampling.h"

#include "../../UCQs/UCQFisherYatesShuffler.h"
#include "../../UCQs/EnumWrapper.h"

#include "../../CQs/RandomOrderAuxCode/RandomOrderEnumeration.h"
#include "../../CQs/Q7_1/files/Q7_1Index.h"
#include "../../CQs/Q7_2/files/Q7_2Index.h"

using namespace std;

typedef RandomOrderEnumeration<Q7_1RandomAccessIndex, ComplexFisherYatesShuffler, Q7_1Answer> Q7_1RandomOrderEnumeration;
typedef EnumWrapper<Q7_1RandomOrderEnumeration, Q7_1Answer, UCQAnswer> Q7_1Enum;

typedef RandomOrderEnumeration<Q7_2RandomAccessIndex, ComplexFisherYatesShuffler, Q7_2Answer> Q7_2RandomOrderEnumeration;
typedef EnumWrapper<Q7_2RandomOrderEnumeration, Q7_2Answer, UCQAnswer> Q7_2Enum;

typedef long long ll;

unordered_map<string, string> readFilenames(const string& filename){
    ifstream f;
    f.open(filename);
    assert(!f.fail()); //assert that opening file succeeded
    
    string tblName, fileName;
    
    unordered_map<string, string> mp;
    while(f >> tblName >> fileName) {
        mp[tblName] = fileName;
    }
    return mp;
}

unordered_map<string, int> readNumLines(const string& filename){
    ifstream f;
    f.open(filename);
    assert(!f.fail()); //assert that opening file succeeded
    
    string tblName;
    int numlines;
    
    unordered_map<string, int> mp;
    while(f >> tblName >> numlines) {
        mp[tblName] = numlines;
    }
    return mp;
}

vector<ll> readIntersectionSizes(const string& filename, const string& queryTag)
{
	ifstream f;
    f.open(filename);
    assert(!f.fail()); //assert that opening file succeeded
    
	string line, tag;
	while(getline(f, line))
	{
		istringstream iss(line);
		iss >> tag;
		if(tag == queryTag)
		{
			ll sz;
			vector<ll> vll;
			while(iss >> sz)
			{
				vll.push_back(sz);
			}
			return vll;
		}
	}
	
	throw runtime_error("could not find query tag in file\n");
}

void readParams(unordered_map<string, string>& filenames, unordered_map<string, int>& numlines, vector<ll>& intersectionSizes)
{
	filenames = readFilenames("../../db/filenames.txt");
	numlines = readNumLines("../../db/numlines.txt");
	intersectionSizes = readIntersectionSizes("../../db/IntersectionSizes.txt", "Q7_1,Q7_2");
}

double enumUntil(DualSampling<UCQAnswer>& ucq, ll answersGoal)
{
    auto t3 = chrono::steady_clock::now();
    ll numAns = 0;
    try {
        for (; numAns < answersGoal; numAns++) {
            // auto a = ucq.sample();
            const UCQAnswer& a = ucq.peek();
            ucq.commit(a);
        }
    }
    catch (runtime_error& e) {
        cout << e.what() << endl;
    }
    auto t4 = chrono::steady_clock::now();

    cout << endl << "number of answers found: " << numAns << endl;
    ucq.PrintCardinalityHistogram();

    return (double)chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() / (double)1000.0;
}

int main() {
    unordered_map<string, string> filenames;
    unordered_map<string, int> numlines;
	vector<ll> intersectionSizes;
	
	readParams(filenames, numlines, intersectionSizes);
	
    ofstream out("report.txt", ios::app);

    auto t1 = chrono::steady_clock::now();
    Q7_1Enum q7_1;
    Q7_2Enum q7_2;
    auto ucq = DualSampling<UCQAnswer>({&q7_1, &q7_2}, intersectionSizes);
    double build_in_millis = ucq.preprocessing(filenames, numlines);
    auto t2 = chrono::steady_clock::now();
    
    cout << "build took " << build_in_millis / 1000.0 << " seconds." << endl;
	cout << endl << "number of answers found: " << ucq.count() << endl;
	
	cout << "Ns: [";
	ucq.PrintCardinalityHistogram();
	cout << "]" << endl;
    
    out << "Incremental Enumeration: " << endl
        << "build = " << build_in_millis / 1000.0 << endl
        << "sampling: " << endl;

    vector<double> ratios = { 0.01, 0.05, 0.1, 0.3, 0.5, 0.7, 0.9, 1 }; 
    ll n = ucq.count();
    for (double ratio : ratios)
    {
        ucq.reset();
        double sampling_time = enumUntil(ucq, ratio * n);

        cout << "AVG. query answer time: " << sampling_time / (double)(ratio * n) << endl;
        cout << "sampling took " << sampling_time << " seconds" << endl;

        out << sampling_time << endl;
    }

    out << endl;
        
    return 0;
}

#endif //RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H
