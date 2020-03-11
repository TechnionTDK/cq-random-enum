#ifndef RANDOMORDERENUMERATION_Q2_NRANDOMENUMERATIONTEST_H_H
#define RANDOMORDERENUMERATION_Q2_NRANDOMENUMERATIONTEST_H_H

#include <chrono>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "../RandomOrderAuxCode/RandomOrderEnumeration.h"
#include "files/Q2_NIndex.h"

typedef long long ll;

void print(const vector<int>& v) {
  cout << "[";
  for(int i = 0; i < v.size(); i++){
    cout << (i > 0 ? ", " : "") << v[i];
  }
  cout << "]" << endl;
}

using namespace std;

typedef RandomOrderEnumeration<Q2_NRandomAccessIndex, FisherYatesShuffler, Q2_NAnswer> Q2_NRandomOrderEnumeration;
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

vector<double> readSampleRatios(const string& filename) {
    ifstream f;
    f.open(filename);
    assert(!f.fail()); //assert that opening file succeeded
    
    double ratio;
    
    vector<double> ratios;
    while(f >> ratio) {
        ratios.push_back(ratio);
    }
    return ratios;
}


int main() {
    
    // read unordered_map for files here
    unordered_map<string, string> filenames = readFilenames("../filenames.txt");
    
    // read unordered_map for number of lines per table here
    unordered_map<string, int> numlines = readNumLines("../../db/numlines.txt");
    
    // read sample_sizes [in percentages]
    vector<double> sample_ratios = readSampleRatios("sampleratios.txt");

    // open output file
    ofstream out;
    out.open("TestsOutput/Q2_N_report.txt", ios::app);
    //out << endl;
    //out << "sample ratio [%], build time [sec], sample time [sec]" << endl;

    #ifdef PRINT
    ofstream log;
    log.open("TestsOutput/Q2_N_answers.csv", ios::out);
    sample_ratios = {1.0};
    #endif

    auto t1 = chrono::steady_clock::now();
    Q2_NRandomOrderEnumeration enume;
    double build_in_millis = enume.preprocessing(filenames, numlines);
    auto t2 = chrono::steady_clock::now();
    cout << "building took " << build_in_millis / 1000.0 << " seconds." << endl;
    cout << "query cardinality, |Q(I)|, is: " << enume.getNumAnswers() << endl;
    cout << endl;
    out << "building: " << build_in_millis / 1000.0 << " seconds." << endl;

    for(double sample_ratio : sample_ratios) {

        enume.resetShuffler(); //the shuffler is reset, the random-access is still valid

        ll sample_size = (ll)(enume.getNumAnswers()*sample_ratio);
        cout << "sample_size = " << sample_size << endl;

        auto t3 = chrono::steady_clock::now();
        for(ll j = 0; j < sample_size; j++){
          #ifdef PRINT
            log << enume.nextAnswer().to_string() << endl;
          #else
            enume.nextAnswer();
          #endif
        }
        auto t4 = chrono::steady_clock::now();
        
        cout << "AVG. query answer time: " <<  
        chrono::duration_cast<chrono::microseconds>(t4 - t3).count() / (double)sample_size <<
        " microseconds {sample_size = " << sample_size << ", sample_ratio = " << (sample_ratio*100) << "%} " << endl;
        cout << "sampling took " << chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() / 1000.0 << " seconds." << endl;
        cout << endl;

        out << "ratio = " << sample_ratio << ", " << "duration = " << chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() / 1000.0 << endl;
    }

    out << endl;
    return 0;
}

#endif //RANDOMORDERENUMERATION_Q2_NRANDOMENUMERATIONTEST_H_H