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
#include "../../CQs/QA/files/QAIndex.h"
#include "../../CQs/QE/files/QEIndex.h"

typedef long long ll;

using namespace std;

typedef RandomOrderEnumeration<QARandomAccessIndex, ComplexFisherYatesShuffler, QAAnswer> QARandomOrderEnumeration;
typedef EnumWrapper<QARandomOrderEnumeration, QAAnswer, UCQAnswer> QAEnum;

typedef RandomOrderEnumeration<QERandomAccessIndex, ComplexFisherYatesShuffler, QEAnswer> QERandomOrderEnumeration;
typedef EnumWrapper<QERandomOrderEnumeration, QEAnswer, UCQAnswer> QEEnum;

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

int main(int argc, char* argv[]) {

    unordered_map<string, string> filenames = readFilenames("../../db/filenames.txt");
    unordered_map<string, int> numlines = readNumLines("../../db/numlines.txt");
	vector<ll> intersectionSizes = readIntersectionSizes("../../db/IntersectionSizes.txt", "QA,QE");

    ofstream out("report.txt", ios::app);

    auto t1 = chrono::steady_clock::now();
    QAEnum QA;
    QEEnum QE;
    auto ucq = DualSampling<UCQAnswer>({&QA, &QE}, intersectionSizes);
    double build_in_millis = ucq.preprocessing(filenames, numlines);
    auto t2 = chrono::steady_clock::now();
    
    cout << "build took " << build_in_millis / 1000.0 << " seconds." << endl;
	cout << endl << "number of answers found: " << ucq.count() << endl;
	
	cout << "Ns: [";
	ucq.PrintCardinalityHistogram();
	cout << "]" << endl;

    auto t3 = chrono::steady_clock::now();
	ll numAns = ucq.count();
	for(ll i = 0; i < numAns; i++)
	{
		const UCQAnswer& a = ucq.peek();
        ucq.commit(a);
	}
    auto t4 = chrono::steady_clock::now();
    
    cout << "Ns: [";
	ucq.PrintCardinalityHistogram();
	cout << "]" << endl;
        
    cout << "AVG. query answer time: " <<  chrono::duration_cast<chrono::microseconds>(t4 - t3).count() / (double)numAns << endl;
    cout << "sampling took " << chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() / 1000.0 << " seconds" << endl;
    
    out << "build: "  << build_in_millis / 1000.0 << " seconds, sampling: "
        << chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() / 1000.0 << " seconds" << endl;
        
    return 0;
}

#endif //RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H
