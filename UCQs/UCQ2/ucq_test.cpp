#ifndef RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H
#define RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H

#include <chrono>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include "../../CQs/RandomOrderAuxCode/RandomOrderEnumeration.h"
#include "../../CQs/Q2_N/files/Q2_NIndex.h"
#include "../../CQs/Q2_S/files/Q2_SIndex.h"
#include "../../CQs/Q2_P/files/Q2_PIndex.h"
#include "../UCQFisherYatesShuffler.h"
#include "../UCQRandomOrderEnumeration.h"
#include "UCQAnswer.h"
#include "../EnumWrapper.h"

void print(const vector<ll>& v) {
  cout << "[";
  for(int i = 0; i < v.size(); i++){
    cout << (i > 0 ? ", " : "") << v[i];
  }
  cout << "]" << endl;
}

using namespace std;

typedef RandomOrderEnumeration<Q2_NRandomAccessIndex, ComplexFisherYatesShuffler, Q2_NAnswer> Q2_NRandomOrderEnumeration;
typedef EnumWrapper<Q2_NRandomOrderEnumeration, Q2_NAnswer, UCQAnswer> Q2_NEnum;

typedef RandomOrderEnumeration<Q2_PRandomAccessIndex, ComplexFisherYatesShuffler, Q2_PAnswer> Q2_PRandomOrderEnumeration;
typedef EnumWrapper<Q2_PRandomOrderEnumeration, Q2_PAnswer, UCQAnswer> Q2_PEnum;

typedef RandomOrderEnumeration<Q2_SRandomAccessIndex, ComplexFisherYatesShuffler, Q2_SAnswer> Q2_SRandomOrderEnumeration;
typedef EnumWrapper<Q2_SRandomOrderEnumeration, Q2_SAnswer, UCQAnswer> Q2_SEnum;


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


int main() {
    // read unordered_map for files here
    unordered_map<string, string> filenames = readFilenames("../filenames.txt");
    
    // read unordered_map for number of lines per table here
    unordered_map<string, int> numlines = readNumLines("../../db/numlines.txt");
	
    ofstream out("report.txt", ios::app);

    auto t1 = chrono::steady_clock::now();
    Q2_NEnum q2_n;
    Q2_PEnum q2_p;
    Q2_SEnum q2_s;
    auto ucq = UCQEnumerator<UCQAnswer>({&q2_n, &q2_p, &q2_s});
    double build_in_millis = ucq.preprocessing(filenames, numlines);
    auto t2 = chrono::steady_clock::now();
    
    cout << "build took " << build_in_millis / 1000.0 << " seconds." << endl;
    cout << "each query cardinality is: ";
    print(ucq.cardHist());

    auto t3 = chrono::steady_clock::now();
    ll numAns = 0;
    try{
      while(1) {
        auto a = ucq.nextAnswer();
        numAns++;
      }
    } catch(runtime_error& e){
        cout << e.what() << endl;
    }
    auto t4 = chrono::steady_clock::now();
    
    cout << "number of answers found: " << numAns << endl;
    cout << "finished with cardinalities: ";
    print(ucq.cardHist());
        
    cout << "AVG. query answer time: " <<  chrono::duration_cast<chrono::microseconds>(t4 - t3).count() / (double)numAns << endl;
    cout << "sampling took " << chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() / 1000.0 << " seconds" << endl;
    
    out << "build: "  << build_in_millis / 1000.0 << " seconds, sampling: "
        << chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() / 1000.0 << " seconds" << endl;
        
        
    return 0;
}

#endif //RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H
