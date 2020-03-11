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
#include "../../CQs/Q2_N/files/Q2_NIndex.h"
#include "../../CQs/Q2_P/files/Q2_PIndex.h"
#include "../../CQs/Q2_S/files/Q2_SIndex.h"

///pairs
#include "../../CQs/Q2_PS/files/Q2_PSIndex.h"
#include "../../CQs/Q2_NP/files/Q2_NPIndex.h"
#include "../../CQs/Q2_NS/files/Q2_NSIndex.h"

///triplets
#include "../../CQs/Q2_PSN/files/Q2_PSNIndex.h"

typedef long long ll;
using namespace std;

typedef MC_CQWrapper<Q2_NRandomAccessIndex, Q2_NAnswer, UCQAnswer> CQ2_N;
typedef MC_CQWrapper<Q2_PRandomAccessIndex, Q2_PAnswer, UCQAnswer> CQ2_P;
typedef MC_CQWrapper<Q2_SRandomAccessIndex, Q2_SAnswer, UCQAnswer> CQ2_S;

typedef MC_CQWrapper<Q2_PSRandomAccessIndex, Q2_PSAnswer, UCQAnswer> CQ2_PS;
typedef MC_CQWrapper<Q2_NPRandomAccessIndex, Q2_NPAnswer, UCQAnswer> CQ2_NP;
typedef MC_CQWrapper<Q2_NSRandomAccessIndex, Q2_NSAnswer, UCQAnswer> CQ2_NS;

typedef MC_CQWrapper<Q2_PSNRandomAccessIndex, Q2_PSNAnswer, UCQAnswer> CQ2_PSN;


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

typedef MC_CQBase<UCQAnswer> mcCQ_t;
typedef mcCQ_t* mcCQ;
typedef MCIndexBase<UCQAnswer> mcUCQ_t;
typedef mcUCQ_t* mcUCQ;

int main() {
    auto t1 = chrono::steady_clock::now();

    // read unordered_map for files here
    unordered_map<string, string> filenames = readFilenames("../filenames.txt");

    // read unordered_map for number of lines per table here
    unordered_map<string, int> numlines = readNumLines("../../db/numlines.txt");

    ///define all our CQs (regular + intersection)
    mcCQ cq_2n = new CQ2_N(); mcCQ cq_2p = new CQ2_P(); mcCQ cq_2s = new CQ2_S(); //singles
    mcCQ cq_2ps = new CQ2_PS(); mcCQ cq_2np = new CQ2_NP(); mcCQ cq_2ns = new CQ2_NS(); //pairs
    mcCQ cq_2psn = new CQ2_PSN(); //triplets

    ///define the mcUCQ chain
    mcUCQ mc_ps = new MCIndexOfTwo<UCQAnswer>(cq_2p, cq_2s, cq_2ps);
    mcUCQ mc_psn = new MCIndex<UCQAnswer>(cq_2n, mc_ps, {cq_2np, cq_2ns, cq_2psn}, {1,1,2});

    ///preprocessing
    double build_in_millis = mc_psn->preprocessing(filenames, numlines);
    cout << "build_in_millis = " << build_in_millis << endl;

    ///build the ENUM instance
    MCRandomOrderEnum<UCQAnswer> mcEnum_psn(mc_psn);
    mcEnum_psn.build();

    auto t2 = chrono::steady_clock::now();

    cout << "q2_n cardinality = " << cq_2n->cardinality() << endl;
    cout << "q2_p cardinality = " << cq_2p->cardinality() << endl;
    cout << "q2_s cardinality = " << cq_2s->cardinality() << endl;
    cout << "q2_np cardinality = " << cq_2np->cardinality() << endl;
    cout << "q2_ns cardinality = " << cq_2ns->cardinality() << endl;
    cout << "q2_ps cardinality = " << cq_2ps->cardinality() << endl;
    cout << "mcucq cardinality = " << mc_psn->cardinality() << endl;
    cout << endl;

    ofstream out("report.txt", ios::app);
    assert(!out.fail());

    /// perform 3 trials of enumeration and average results
    vector<double> enum_time = {};
    for(int t = 0; t < 3; t++) {
        cout << "trial " << t + 1 << ":" << endl;
        auto t3 = chrono::steady_clock::now();
        mcEnum_psn.resetShuffler();
        for (ll i = 0; i < mc_psn->cardinality(); i++) {
//        log << mc_ps->access(i) << endl;
            mcEnum_psn.next();
        }
        auto t4 = chrono::steady_clock::now();
        enum_time.push_back(chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() / 1000.0);
    }

    double average = accumulate(enum_time.begin(), enum_time.end(), 0.0)/enum_time.size();
    cout << "build: " << build_in_millis / 1000.0 << " seconds" << endl;
    out << "build: " << build_in_millis / 1000.0 << " seconds" << endl;
    cout << "enumeration: " << average << " seconds" << endl;
    out << "enumeration: " << average << " seconds" << endl;


    delete cq_2n;
    delete cq_2p;
    delete cq_2s;
    delete cq_2np;
    delete cq_2ns;
    delete cq_2ps;
    delete cq_2psn;

//    delete empty;
//    delete mc_p;
    delete mc_ps;
    delete mc_psn;



    return 0;
}

#endif //RANDOMORDERENUMERATION_UCQRANDOMENUMERATIONTEST_H_H
