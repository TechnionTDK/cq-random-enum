//
// Created by shai.zeevi on 04/12/2019.
//

#ifndef RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H
#define RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H

#include <chrono>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <numeric>
#include "../../CQs/Q7_1/files/Q7_1Index.h"
#include "../../CQs/Q7_2/files/Q7_2Index.h"
#include "../../CQs/Q7_1_2/files/Q7_1_2Index.h"
#include "UCQAnswer.h"
#include "MCIndex.h"

typedef long long ll;
using namespace std;

typedef MC_CQWrapper<Q7_1RandomAccessIndex, Q7_1Answer, UCQAnswer> CQ7_1;
typedef MC_CQWrapper<Q7_2RandomAccessIndex, Q7_2Answer, UCQAnswer> CQ7_2;
typedef MC_CQWrapper<Q7_1_2RandomAccessIndex, Q7_1_2Answer, UCQAnswer> CQ7_1_2;


unordered_map<string, string> readFilenames(const string &filename) {
    ifstream f;
    f.open(filename);
    assert(!f.fail()); //assert that opening file succeeded

    string tblName, fileName;

    unordered_map<string, string> mp;
    while (f >> tblName >> fileName) {
        mp[tblName] = fileName;
    }
    return mp;
}

unordered_map<string, int> readNumLines(const string &filename) {
    ifstream f;
    f.open(filename);
    assert(!f.fail()); //assert that opening file succeeded

    string tblName;
    int numlines;

    unordered_map<string, int> mp;
    while (f >> tblName >> numlines) {
        mp[tblName] = numlines;
    }
    return mp;
}

typedef MC_CQBase<UCQAnswer> mcCQ_t;
typedef mcCQ_t *mcCQ;
typedef MCIndexBase<UCQAnswer> mcUCQ_t;
typedef mcUCQ_t *mcUCQ;

int main() {
    auto t1 = chrono::steady_clock::now();

    // read unordered_map for files here
    unordered_map<string, string> filenames = readFilenames("../filenames.txt");

    // read unordered_map for number of lines per table here
    unordered_map<string, int> numlines = readNumLines("../../db/numlines.txt");

    ///define all our CQs (regular + intersection)
    mcCQ cq71 = new CQ7_1();
    mcCQ cq72 = new CQ7_2();
    mcCQ cq712 = new CQ7_1_2();

    ///define the empty MCIndex
    mcUCQ mc_q7_1_and_2 = new MCIndexOfTwo<UCQAnswer>(cq71, cq72, cq712);

    ///preprocessing
    double build_in_millis = mc_q7_1_and_2->preprocessing(filenames, numlines);
    cout << "build_in_millis = " << build_in_millis << endl;

    ///build the ENUM instance
    MCRandomOrderEnum<UCQAnswer> mcEnum(mc_q7_1_and_2);
    mcEnum.build();

    auto t2 = chrono::steady_clock::now();

    cout << "q_7_1 cardinality = " << cq71->cardinality() << endl;
    cout << "q_7_2 cardinality = " << cq72->cardinality() << endl;
    cout << "q_7_1_2 cardinality = " << cq712->cardinality() << endl;
    cout << "mcucq cardinality = " << mc_q7_1_and_2->cardinality() << endl;

    ofstream out("report.txt", ios::app);
    assert(!out.fail());

    vector<double> percent = {0.01, 0.05, 0.1, 0.3, 0.5, 0.7, 0.9, 1};

    cout << endl;
    cout << "build: " << build_in_millis / 1000.0 << " seconds" << endl;
    out << "build: " << build_in_millis / 1000.0 << " seconds" << endl;


    ///enumerate answers (with 3 trials)
    for (double p : percent) {
        vector<double> enum_time = {};
        for(int t = 0; t < 3; t++) {
            cout << "p = " << p << " ,trial " << t + 1 << ":" << endl;
            auto t3 = chrono::steady_clock::now();
            mcEnum.resetShuffler();
            for (ll i = 0; i < mc_q7_1_and_2->cardinality() * p; i++) {
                mcEnum.next();
            }
            auto t4 = chrono::steady_clock::now();

            enum_time.push_back(chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() / 1000.0);
        }

        //report average of 3 runs
        double average = accumulate(enum_time.begin(), enum_time.end(), 0.0)/enum_time.size();
        cout << p * 100 << "%: " << average << " seconds" << endl;
        out << p * 100 << "%: " << average << " seconds" << endl;
    }
    return 0;


}

#endif //RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H
