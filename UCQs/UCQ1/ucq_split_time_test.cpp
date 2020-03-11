#ifndef RANDOMORDERENUMERATION_QARANDOMENUMERATIONTEST_H_H
#define RANDOMORDERENUMERATION_QARANDOMENUMERATIONTEST_H_H

#include <chrono>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include "../../CQs/RandomOrderAuxCode/RandomOrderEnumeration.h"
#include "../../CQs/Q7_1/files/Q7_1Index.h"
#include "../../CQs/Q7_2/files/Q7_2Index.h"
#include "../UCQFisherYatesShuffler.h"
#include "../UCQRandomOrderEnumeration.h"
#include "UCQAnswer.h"
#include "../EnumWrapper.h"

typedef pair<double, double> pdd;

void print(const vector<ll>& v) {
  cout << "[";
  for(int i = 0; i < v.size(); i++){
    cout << (i > 0 ? ", " : "") << v[i];
  }
  cout << "]" << endl;
}

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

vector<int> readSampleSizes(const string& filename) {
    ifstream f;
    f.open(filename);
    assert(!f.fail()); //assert that opening file succeeded
    
    int size;
    
    vector<int> sizes;
    while(f >> size) {
        sizes.push_back(size);
    }
    return sizes;
}


int main() {
    
    // read unordered_map for files here
    unordered_map<string, string> filenames = readFilenames("../filenames.txt");
    
    // read unordered_map for number of lines per table here
    unordered_map<string, int> numlines = readNumLines("../../db/numlines.txt");
    
    // read sample_sizes [in percentages]
    vector<int> sample_sizes = readSampleSizes("thresholds.txt");

    // open output file
    ofstream out;
    out.open("time_split_time_report.txt", ios::app);
    assert(!out.fail());

    auto t1 = chrono::steady_clock::now();
    Q7_1Enum q7_1;
    Q7_2Enum q7_2;
    auto ucq = UCQEnumerator<UCQAnswer>({&q7_1, &q7_2});
    double build_in_millis = ucq.preprocessing(filenames, numlines);
    auto t2 = chrono::steady_clock::now();
    
    cout << "build took " << build_in_millis / 1000.0 << " seconds." << endl;
    cout << "each query cardinality is: ";
    print(ucq.cardHist());
    out << "building: " << build_in_millis / 1000.0 << " seconds." << endl;
    
    int answers_recvd = 0;
    
    for(int sample_size : sample_sizes) {
        
        ucq.resetTimer();
        
        for(int j = 0; j < sample_size; j++){
            ucq.nextAnswer();
        }
        answers_recvd += sample_size;
        pdd times = ucq.getTime();

        out << "answers_recvd = " << answers_recvd << ", secs_for_answers = " << times.first / 1000 << ", secs_for_rejections = " << times.second / 1000 << endl;
        cout << "answers_recvd = " << answers_recvd << ", secs_for_answers = " << times.first / 1000 << ", secs_for_rejections = " << times.second / 1000 << endl;
    }
    
    assert(ucq.empty());

    out << endl;
    return 0;
}

#endif //RANDOMORDERENUMERATION_QARANDOMENUMERATIONTEST_H_H