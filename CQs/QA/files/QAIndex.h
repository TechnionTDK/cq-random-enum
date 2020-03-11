#ifndef RANDOMORDERENUMERATION_QAINDEX_H
#define RANDOMORDERENUMERATION_QAINDEX_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "../../TemplatedRandomAccess/YannakakisReducer.h"
#include "../../TemplatedRandomAccess/AbstractWeightCalculator.h"
#include "QA__O_Parcel.h"
#include "QA__L_Parcel.h"
#include "QA__S_Parcel.h"
#include "QA__N_Parcel.h"
#include "QA__R_Parcel.h"
#include "QAAnswer.h"
#include "../../RandomAccessAuxCode/IndexUtils.h"

typedef long long ll;

using namespace std;

//------------------------------------ Yannakakis Reducer ------------------------------------------
//specifies reduction order
struct QAYannakakisReducer : YannakakisReducer<QA__O_Table, QA__L_Table, QA__S_Table, QA__N_Table, QA__R_Table> {
    //you just need to arrange the calls to oneBottomUp according to the tree structure
    void reduceBottomUp(QA__O_Table& _o__tbl, QA__L_Table& _l__tbl, QA__S_Table& _s__tbl, QA__N_Table& _n__tbl, QA__R_Table& _r__tbl) override {
        oneBottomUp<QA__N_Parcel, QA__R_Parcel, QA__R_Key>(_n__tbl, _r__tbl);
        oneBottomUp<QA__S_Parcel, QA__N_Parcel, QA__N_Key>(_s__tbl, _n__tbl);
        oneBottomUp<QA__L_Parcel, QA__S_Parcel, QA__S_Key>(_l__tbl, _s__tbl);
        oneBottomUp<QA__O_Parcel, QA__L_Parcel, QA__L_Key>(_o__tbl, _l__tbl);
    }

    //you just need to arrange the calls to oneTopDown according to the tree structure
    void reduceTopDown(QA__O_Table& _o__tbl, QA__L_Table& _l__tbl, QA__S_Table& _s__tbl, QA__N_Table& _n__tbl, QA__R_Table& _r__tbl) override {
        oneTopDown<QA__L_Parcel, QA__O_Parcel, QA__L_Key>(_l__tbl, _o__tbl);
        oneTopDown<QA__S_Parcel, QA__L_Parcel, QA__S_Key>(_s__tbl, _l__tbl);
        oneTopDown<QA__N_Parcel, QA__S_Parcel, QA__N_Key>(_n__tbl, _s__tbl);
        oneTopDown<QA__R_Parcel, QA__N_Parcel, QA__R_Key>(_r__tbl, _n__tbl);
    }
};
//------------------------------------------------------------------------------

//------------------------------------ Table Weighter ------------------------------------------
#ifdef PROJECTION
struct QA__R_Weighter : AbstractSingleTableWeighter<QA__R_Key, QA__R_Parcel> {//leaf
    inline void weightTable(QA__R_SplitTable& split__r_tbl) override {}
};
#else
struct QA__R_Weighter : AbstractSingleTableWeighter<QA__R_Key, QA__R_Parcel> {//leaf
    inline void weightTable(QA__R_SplitTable& split__r_tbl) override {}
};
#endif


#ifdef PROJECTION
struct QA__N_Weighter : AbstractSingleTableWeighter<QA__N_Key, QA__N_Parcel, QA__R_SplitTable> {//internal node
    inline void weightTable(QA__N_SplitTable& split__n_tbl, const QA__R_SplitTable& split__r_tbl) override {
        weightingStep(split__n_tbl, split__r_tbl);
    }
};
#else
struct QA__N_Weighter : AbstractSingleTableWeighter<QA__N_Key, QA__N_Parcel, QA__R_SplitTable> {//internal node
    inline void weightTable(QA__N_SplitTable& split__n_tbl, const QA__R_SplitTable& split__r_tbl) override {
        weightingStep(split__n_tbl, split__r_tbl);
    }
};
#endif


#ifdef PROJECTION
struct QA__S_Weighter : AbstractSingleTableWeighter<QA__S_Key, QA__S_Parcel, QA__N_SplitTable> {//internal node
    inline void weightTable(QA__S_SplitTable& split__s_tbl, const QA__N_SplitTable& split__n_tbl) override {
        weightingStep(split__s_tbl, split__n_tbl);
    }
};
#else
struct QA__S_Weighter : AbstractSingleTableWeighter<QA__S_Key, QA__S_Parcel, QA__N_SplitTable> {//internal node
    inline void weightTable(QA__S_SplitTable& split__s_tbl, const QA__N_SplitTable& split__n_tbl) override {
        weightingStep(split__s_tbl, split__n_tbl);
    }
};
#endif


#ifdef PROJECTION
struct QA__L_Weighter : AbstractSingleTableWeighter<QA__L_Key, QA__L_Parcel, QA__S_SplitTable> {//internal node
    inline void weightTable(QA__L_SplitTable& split__l_tbl, const QA__S_SplitTable& split__s_tbl) override {
        weightingStep(split__l_tbl, split__s_tbl);
    }
};
#else
struct QA__L_Weighter : AbstractSingleTableWeighter<QA__L_Key, QA__L_Parcel, QA__S_SplitTable> {//internal node
    inline void weightTable(QA__L_SplitTable& split__l_tbl, const QA__S_SplitTable& split__s_tbl) override {
        weightingStep(split__l_tbl, split__s_tbl);
    }
};
#endif


#ifdef PROJECTION
struct QA__O_Weighter : AbstractSingleTableWeighter<QA__O_Key, QA__O_Parcel, QA__L_SplitTable> {//internal node
    inline void weightTable(QA__O_SplitTable& split__o_tbl, const QA__L_SplitTable& split__l_tbl) override {
        weightingStep(split__o_tbl, split__l_tbl);
    }
};
#else
struct QA__O_Weighter : AbstractSingleTableWeighter<QA__O_Key, QA__O_Parcel, QA__L_SplitTable> {//internal node
    inline void weightTable(QA__O_SplitTable& split__o_tbl, const QA__L_SplitTable& split__l_tbl) override {
        weightingStep(split__o_tbl, split__l_tbl);
    }
};
#endif


#ifndef PROJECTION
struct QAWeighter : QueryWeighter<QA__O_SplitTable, QA__L_SplitTable, QA__S_SplitTable, QA__N_SplitTable, QA__R_SplitTable> {
    inline void weight(QA__O_SplitTable& split__o_tbl, QA__L_SplitTable& split__l_tbl, QA__S_SplitTable& split__s_tbl, QA__N_SplitTable& split__n_tbl, QA__R_SplitTable& split__r_tbl) override {
        QA__R_Weighter().weight(split__r_tbl);

        QA__N_Weighter().weight(split__n_tbl, split__r_tbl);

        QA__S_Weighter().weight(split__s_tbl, split__n_tbl);

        QA__L_Weighter().weight(split__l_tbl, split__s_tbl);

        QA__O_Weighter().weight(split__o_tbl, split__l_tbl);
    }
};
#else
struct QAWeighter : QueryWeighter<QA__O_SplitTable, QA__L_SplitTable, QA__S_SplitTable, QA__N_SplitTable, QA__R_SplitTable> {
    inline void weight(QA__O_SplitTable& split__o_tbl, QA__L_SplitTable& split__l_tbl, QA__S_SplitTable& split__s_tbl, QA__N_SplitTable& split__n_tbl, QA__R_SplitTable& split__r_tbl) override {
        QA__R_Weighter().weight(split__r_tbl);

        QA__N_Weighter().weight(split__n_tbl, split__r_tbl);

        QA__S_Weighter().weight(split__s_tbl, split__n_tbl);

        QA__L_Weighter().weight(split__l_tbl, split__s_tbl);

        QA__O_Weighter().weight(split__o_tbl, split__l_tbl);
    }
};
#endif
//------------------------------------------------------------------------------

bool QA_R_NameSelect(void* arg, void* parcel) {
  return ((QA__R_Parcel*)parcel)->rname == "AMERICA";
}

bool QA_NationSelect(void* arg, void* parcel) {
  return ((QA__N_Parcel*)parcel)->nationKey == 24; //UNITED STATES
}

//------------------------------------ RandomAccessIndex ------------------------------------------
struct QARandomAccessIndex {

    //Fields tables;
    #ifdef PROJECTION
    QA__O_SplitTable split__o_tbl;
    QA__L_SplitTable split__l_tbl;
    QA__S_SplitTable split__s_tbl;
    QA__N_SplitTable split__n_tbl;
    QA__R_SplitTable split__r_tbl;
    #else
    QA__O_SplitTable split__o_tbl;
    QA__L_SplitTable split__l_tbl;
    QA__S_SplitTable split__s_tbl;
    QA__N_SplitTable split__n_tbl;
    QA__R_SplitTable split__r_tbl;

    #endif
    ll numAnswers;
    
    
    //preprocessing
    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numLines) {
        cout << "\t[QA PREPROCESSING]" << endl;
        //------------------------------------------------------- PREPROCESSING START!
        auto t1 = chrono::steady_clock::now();
        
        QA__O_Table _o_tbl;
        QA__L_Table _l_tbl;
        QA__S_Table _s_tbl;
        QA__N_Table _n_tbl;
        QA__R_Table _r_tbl;

        _o_tbl.loadFromFile(filenames.at("_O_"), numLines.at("_O_"));
        _l_tbl.loadFromFile(filenames.at("_L_"), numLines.at("_L_"));
        _s_tbl.loadFromFile(filenames.at("_S_"), numLines.at("_S_"));
        _n_tbl.loadFromFile(filenames.at("_N_"), numLines.at("_N_")/*, QA_NationSelect*/);
        _r_tbl.loadFromFile(filenames.at("_R_"), numLines.at("_R_")/*, QA_R_NameSelect*/);
        
        auto t2 = chrono::steady_clock::now();
        
        //_r_tbl = _r_tbl.select(QA_R_NameSelect);
        _n_tbl = _n_tbl.select(QA_NationSelect);
        
        QAYannakakisReducer().reduce(_o_tbl, _l_tbl, _s_tbl, _n_tbl, _r_tbl);

        #ifdef PROJECTION
        split__o_tbl.loadFromTable(_o_tbl);
        split__l_tbl.loadFromTable(_l_tbl);
        split__s_tbl.loadFromTable(_s_tbl);
        split__n_tbl.loadFromTable(_n_tbl);
        split__r_tbl.loadFromTable(_r_tbl);
        #else
        split__o_tbl.loadFromTable(_o_tbl);
        split__l_tbl.loadFromTable(_l_tbl);
        split__s_tbl.loadFromTable(_s_tbl);
        split__n_tbl.loadFromTable(_n_tbl);
        split__r_tbl.loadFromTable(_r_tbl);
        #endif

        QAWeighter().weight(split__o_tbl, split__l_tbl, split__s_tbl, split__n_tbl, split__r_tbl);
        
        numAnswers = split__o_tbl.getCummulativeWeight();
        
        auto t3 = chrono::steady_clock::now();
        //cout << "reading time is " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1000.0 << " milliseconds" << endl;
        //cout << "building time is " << chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0 << " milliseconds" << endl;
        //------------------------------------------------------- PREPROCESSING DONE!

        return chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0;
    }
    
    QAAnswer access(ll j) {
        //if(j < 0 || j > numAnswers) {
        //    cout << "tried to access answer no." << j << ", n = " << numAnswers << endl;
        //    throw runtime_error("index beyond range " + to_string(j));
        //}
        
        ll j__l_, j__s_, j__n_, j__r_;
        QAAnswer ans;
        find_answer__O_(ans, j, j__l_);
        find_answer__L_(ans, j__l_, j__s_);
        find_answer__S_(ans, j__s_, j__n_);
        find_answer__N_(ans, j__n_, j__r_);
        find_answer__R_(ans, j__r_);
        return move(ans);
    }
    
    #if defined(INVERSE_MAPPING) || defined(INVERTED_ACCESS)
    ll index(const QAAnswer& ans) {
        ll j__o_, j__l_, j__s_, j__n_, j__r_;
        if(!find_index__R_(ans, j__r_)) {
            return -1;
        }

        if(!find_index__N_(ans, j__r_, j__n_)) {
            return -1;
        }

        if(!find_index__S_(ans, j__n_, j__s_)) {
            return -1;
        }

        if(!find_index__L_(ans, j__s_, j__l_)) {
            return -1;
        }

        if(!find_index__O_(ans, j__l_, j__o_)) {
            return -1;
        }

        return j__o_;
    }
    #endif
    
    
private:
    inline void find_answer__O_(QAAnswer& answer, ll j/*, int& position*/, ll& j__l_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__o_tbl.buckets[answer.to<QA__O_Key>()];
        #else
        const auto& bucket = split__o_tbl.buckets[answer.to<QA__O_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<QA__O_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__l_tbl.buckets[answer.to<QA__L_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__l_tbl.buckets[answer.to<QA__L_Key>()].totalWeight});
        #endif
        j__l_ = new_indices[0];
    }

    inline void find_answer__L_(QAAnswer& answer, ll j/*, int& position*/, ll& j__s_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__l_tbl.buckets[answer.to<QA__L_Key>()];
        #else
        const auto& bucket = split__l_tbl.buckets[answer.to<QA__L_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<QA__L_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<QA__S_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<QA__S_Key>()].totalWeight});
        #endif
        j__s_ = new_indices[0];
    }

    inline void find_answer__S_(QAAnswer& answer, ll j/*, int& position*/, ll& j__n_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__s_tbl.buckets[answer.to<QA__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<QA__S_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<QA__S_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n_tbl.buckets[answer.to<QA__N_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n_tbl.buckets[answer.to<QA__N_Key>()].totalWeight});
        #endif
        j__n_ = new_indices[0];
    }

    inline void find_answer__N_(QAAnswer& answer, ll j/*, int& position*/, ll& j__r_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__n_tbl.buckets[answer.to<QA__N_Key>()];
        #else
        const auto& bucket = split__n_tbl.buckets[answer.to<QA__N_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<QA__N_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__r_tbl.buckets[answer.to<QA__R_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__r_tbl.buckets[answer.to<QA__R_Key>()].totalWeight});
        #endif
        j__r_ = new_indices[0];
    }

    inline void find_answer__R_(QAAnswer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__r_tbl.buckets[answer.to<QA__R_Key>()];
        #else
        const auto& bucket = split__r_tbl.buckets[answer.to<QA__R_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<QA__R_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #else
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #endif
        
    }
    
    #if defined(INVERSE_MAPPING) || defined(INVERTED_ACCESS)
    inline bool find_index__O_(const QAAnswer& answer, ll j__l_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__o_tbl.buckets[answer.to<QA__O_Key>()];
        #else
        const auto& bucket = split__o_tbl.buckets[answer.to<QA__O_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<QA__O_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<QA__O_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__l_}, {split__l_tbl.buckets[answer.to<QA__L_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__l_}, {split__l_tbl.buckets[answer.to<QA__L_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__L_(const QAAnswer& answer, ll j__s_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__l_tbl.buckets[answer.to<QA__L_Key>()];
        #else
        const auto& bucket = split__l_tbl.buckets[answer.to<QA__L_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<QA__L_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<QA__L_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__s_}, {split__s_tbl.buckets[answer.to<QA__S_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__s_}, {split__s_tbl.buckets[answer.to<QA__S_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__S_(const QAAnswer& answer, ll j__n_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__s_tbl.buckets[answer.to<QA__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<QA__S_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<QA__S_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<QA__S_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__n_}, {split__n_tbl.buckets[answer.to<QA__N_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__n_}, {split__n_tbl.buckets[answer.to<QA__N_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__N_(const QAAnswer& answer, ll j__r_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__n_tbl.buckets[answer.to<QA__N_Key>()];
        #else
        const auto& bucket = split__n_tbl.buckets[answer.to<QA__N_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<QA__N_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<QA__N_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__r_}, {split__r_tbl.buckets[answer.to<QA__R_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__r_}, {split__r_tbl.buckets[answer.to<QA__R_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__R_(const QAAnswer& answer, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__r_tbl.buckets[answer.to<QA__R_Key>()];
        #else
        const auto& bucket = split__r_tbl.buckets[answer.to<QA__R_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<QA__R_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<QA__R_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ /*+ IndexUtils::combine({}, {})*/;
        #else
        j = it->second /*offset*/ /*+ IndexUtils::combine({}, {})*/;
        #endif
        return true;
    }
    #endif
    
    static inline int getTupleIndex(const vector<ll>& prefixSum, ll j) {
        return (upper_bound(prefixSum.begin(), prefixSum.end(), j) - prefixSum.begin() - 1);
    }
};

typedef QARandomAccessIndex QAIndex;

//------------------------------------------------------------------------------

#endif //RANDOMORDERENUMERATION_QAINDEX_H