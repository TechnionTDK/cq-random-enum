//
// Created by shai.zeevi on 06/12/2019.
//

//
// Created by shai.zeevi on 05/12/2019.
//

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
#include "MCIndex.h"
#include "UCQAnswer.h"

///singletons
#include "../../CQs/QA/files/QAIndex.h"
#include "../../CQs/QE/files/QEIndex.h"

///pairs
#include "../../CQs/QAE/files/QAEIndex.h"

typedef long long ll;
using namespace std;

typedef MC_CQWrapper<QARandomAccessIndex, QAAnswer, UCQAnswer> CQA;
typedef MC_CQWrapper<QERandomAccessIndex, QEAnswer, UCQAnswer> CQE;

typedef MC_CQWrapper<QAERandomAccessIndex, QAEAnswer, UCQAnswer> CQAE;

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
    mcCQ cqA = new CQA();
    mcCQ cqE = new CQE();
    mcCQ cqAE = new CQAE();

    ///define the mcUCQ
    mcUCQ ucqAE = new MCIndexOfTwo<UCQAnswer>(cqA, cqE, cqAE);
//    mcUCQ empty = new EmptyMCIndex<UCQAnswer>(); //base of the chain
//
//    mcUCQ ucqA = new MCIndex<UCQAnswer>(cqA, empty, {}, {}); //this c'tor preforms build already
//    mcUCQ ucqAE = new MCIndex<UCQAnswer>(cqE, ucqA, {cqAE}, {1});

    ///preprocessing
    double build_in_millis = ucqAE->preprocessing(filenames, numlines);
    cout << "build_in_millis = " << build_in_millis << endl;

    ///build the ENUM instance
    MCRandomOrderEnum<UCQAnswer> mcEnumAE(ucqAE);
    mcEnumAE.build();

    auto t2 = chrono::steady_clock::now();

    cout << "qA cardinality = " << cqA->cardinality() << endl;
    cout << "qE cardinality = " << cqE->cardinality() << endl;
    cout << "qAE cardinality = " << cqAE->cardinality() << endl;
    cout << "ucqAE cardinality = " << ucqAE->cardinality() << endl;
    cout << endl;

    ofstream out("report.txt", ios::app);
    assert(!out.fail());


    /// perform 3 trials of enumeration and average results
    vector<double> enum_time = {};
    for (int t = 0; t < 3; t++) {
        cout << "trial " << t + 1 << ":" << endl;
        auto t3 = chrono::steady_clock::now();
        mcEnumAE.resetShuffler();
        for (ll i = 0; i < ucqAE->cardinality(); i++) {
//        log << mc_ps->access(i) << endl;
            mcEnumAE.next();
        }
        auto t4 = chrono::steady_clock::now();
        enum_time.push_back(chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() / 1000.0);
    }

    double average = accumulate(enum_time.begin(), enum_time.end(), 0.0)/enum_time.size();
    cout << "build: " << build_in_millis / 1000.0 << " seconds" << endl;
    out << "build: " << build_in_millis / 1000.0 << " seconds" << endl;
    cout << "enumeration: " << average << " seconds" << endl;
    out << "enumeration: " << average << " seconds" << endl;


    delete cqA;
    delete cqE;
    delete cqAE;
//    delete empty;
//    delete ucqA;
    delete ucqAE;

    return 0;
}

#endif //RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H
