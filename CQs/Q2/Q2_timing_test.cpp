#ifndef RANDOMORDERENUMERATION_Q2RANDOMENUMERATIONTEST_H_H
#define RANDOMORDERENUMERATION_Q2RANDOMENUMERATIONTEST_H_H

#include <chrono>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "../RandomOrderAuxCode/RandomOrderEnumeration.h"
#include "files/Q2Index.h"

typedef long long ll;

void print(const vector<int>& v) {
  cout << "[";
  for(int i = 0; i < v.size(); i++){
    cout << (i > 0 ? ", " : "") << v[i];
  }
  cout << "]" << endl;
}

using namespace std;

typedef RandomOrderEnumeration<Q2RandomAccessIndex, FisherYatesShuffler, Q2Answer> Q2RandomOrderEnumeration;
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

    auto t1 = chrono::steady_clock::now();
    Q2RandomOrderEnumeration enume;
    double build_time_in_millis = enume.preprocessing(filenames, numlines);
    auto t2 = chrono::steady_clock::now();

    cout << "build took " << build_time_in_millis / 1000.0 << " seconds." << endl;
    cout << "query cardinality, |Q(I)|, is: " << enume.getNumAnswers() << endl;
    cout << "sample_size = " << enume.getNumAnswers() << endl;

    ofstream timing("TestsOutput/Q2_delay.csv");
    timing << "T" << endl;

    auto t_start = chrono::steady_clock::now();
    auto t3 = chrono::steady_clock::now();
    for(ll j = 0; j < enume.getNumAnswers(); j++){
      enume.nextAnswer();
      auto t_now = chrono::steady_clock::now();
      timing << chrono::duration_cast<chrono::nanoseconds>(t_now - t3).count() / 1000.0 << endl;
      t3 = t_now;
    }
    auto t4 = chrono::steady_clock::now();

    cout << "total time " << chrono::duration_cast<chrono::milliseconds>(t4 - t_start).count() / 1000.0 << endl;
    return 0;
}

#endif //RANDOMORDERENUMERATION_Q2RANDOMENUMERATIONTEST_H_H