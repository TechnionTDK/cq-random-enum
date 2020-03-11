#ifndef RANDOMORDERENUMERATION_QAEINDEX_H
#define RANDOMORDERENUMERATION_QAEINDEX_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "../../TemplatedRandomAccess/YannakakisReducer.h"
#include "../../TemplatedRandomAccess/AbstractWeightCalculator.h"
#include "QAE__O_Parcel.h"
#include "QAE__L_Parcel.h"
#include "QAE__S_Parcel.h"
#include "QAE__N_Parcel.h"
#include "QAE__R_Parcel.h"
#include "QAEAnswer.h"
#include "../../RandomAccessAuxCode/IndexUtils.h"

typedef long long ll;

using namespace std;

//------------------------------------ Yannakakis Reducer ------------------------------------------
//specifies reduction order
struct QAEYannakakisReducer : YannakakisReducer<QAE__O_Table, QAE__L_Table, QAE__S_Table, QAE__N_Table, QAE__R_Table> {
    //you just need to arrange the calls to oneBottomUp according to the tree structure
    void reduceBottomUp(QAE__O_Table& _o__tbl, QAE__L_Table& _l__tbl, QAE__S_Table& _s__tbl, QAE__N_Table& _n__tbl, QAE__R_Table& _r__tbl) override {
        oneBottomUp<QAE__N_Parcel, QAE__R_Parcel, QAE__R_Key>(_n__tbl, _r__tbl);
        oneBottomUp<QAE__S_Parcel, QAE__N_Parcel, QAE__N_Key>(_s__tbl, _n__tbl);
        oneBottomUp<QAE__L_Parcel, QAE__S_Parcel, QAE__S_Key>(_l__tbl, _s__tbl);
        oneBottomUp<QAE__O_Parcel, QAE__L_Parcel, QAE__L_Key>(_o__tbl, _l__tbl);
    }

    //you just need to arrange the calls to oneTopDown according to the tree structure
    void reduceTopDown(QAE__O_Table& _o__tbl, QAE__L_Table& _l__tbl, QAE__S_Table& _s__tbl, QAE__N_Table& _n__tbl, QAE__R_Table& _r__tbl) override {
        oneTopDown<QAE__L_Parcel, QAE__O_Parcel, QAE__L_Key>(_l__tbl, _o__tbl);
        oneTopDown<QAE__S_Parcel, QAE__L_Parcel, QAE__S_Key>(_s__tbl, _l__tbl);
        oneTopDown<QAE__N_Parcel, QAE__S_Parcel, QAE__N_Key>(_n__tbl, _s__tbl);
        oneTopDown<QAE__R_Parcel, QAE__N_Parcel, QAE__R_Key>(_r__tbl, _n__tbl);
    }
};
//------------------------------------------------------------------------------

//------------------------------------ Table Weighter ------------------------------------------
#ifdef PROJECTION_QAE
struct QAE__R_Weighter : AbstractSingleTableWeighter<QAE__R_Key, QAE__R_Parcel> {//leaf
    inline void weightTable(QAE__R_SplitTable& split__r_tbl) override {}
};
#else
struct QAE__R_Weighter : AbstractSingleTableWeighter<QAE__R_Key, QAE__R_Parcel> {//leaf
    inline void weightTable(QAE__R_SplitTable& split__r_tbl) override {}
};
#endif


#ifdef PROJECTION_QAE
struct QAE__N_Weighter : AbstractSingleTableWeighter<QAE__N_Key, QAE__N_Parcel, QAE__R_SplitTable> {//internal node
    inline void weightTable(QAE__N_SplitTable& split__n_tbl, const QAE__R_SplitTable& split__r_tbl) override {
        weightingStep(split__n_tbl, split__r_tbl);
    }
};
#else
struct QAE__N_Weighter : AbstractSingleTableWeighter<QAE__N_Key, QAE__N_Parcel, QAE__R_SplitTable> {//internal node
    inline void weightTable(QAE__N_SplitTable& split__n_tbl, const QAE__R_SplitTable& split__r_tbl) override {
        weightingStep(split__n_tbl, split__r_tbl);
    }
};
#endif


#ifdef PROJECTION_QAE
struct QAE__S_Weighter : AbstractSingleTableWeighter<QAE__S_Key, QAE__S_Parcel, QAE__N_SplitTable> {//internal node
    inline void weightTable(QAE__S_SplitTable& split__s_tbl, const QAE__N_SplitTable& split__n_tbl) override {
        weightingStep(split__s_tbl, split__n_tbl);
    }
};
#else
struct QAE__S_Weighter : AbstractSingleTableWeighter<QAE__S_Key, QAE__S_Parcel, QAE__N_SplitTable> {//internal node
    inline void weightTable(QAE__S_SplitTable& split__s_tbl, const QAE__N_SplitTable& split__n_tbl) override {
        weightingStep(split__s_tbl, split__n_tbl);
    }
};
#endif


#ifdef PROJECTION_QAE
struct QAE__L_Weighter : AbstractSingleTableWeighter<QAE__L_Key, QAE__L_Parcel, QAE__S_SplitTable> {//internal node
    inline void weightTable(QAE__L_SplitTable& split__l_tbl, const QAE__S_SplitTable& split__s_tbl) override {
        weightingStep(split__l_tbl, split__s_tbl);
    }
};
#else
struct QAE__L_Weighter : AbstractSingleTableWeighter<QAE__L_Key, QAE__L_Parcel, QAE__S_SplitTable> {//internal node
    inline void weightTable(QAE__L_SplitTable& split__l_tbl, const QAE__S_SplitTable& split__s_tbl) override {
        weightingStep(split__l_tbl, split__s_tbl);
    }
};
#endif


#ifdef PROJECTION_QAE
struct QAE__O_Weighter : AbstractSingleTableWeighter<QAE__O_Key, QAE__O_Parcel, QAE__L_SplitTable> {//internal node
    inline void weightTable(QAE__O_SplitTable& split__o_tbl, const QAE__L_SplitTable& split__l_tbl) override {
        weightingStep(split__o_tbl, split__l_tbl);
    }
};
#else
struct QAE__O_Weighter : AbstractSingleTableWeighter<QAE__O_Key, QAE__O_Parcel, QAE__L_SplitTable> {//internal node
    inline void weightTable(QAE__O_SplitTable& split__o_tbl, const QAE__L_SplitTable& split__l_tbl) override {
        weightingStep(split__o_tbl, split__l_tbl);
    }
};
#endif


#ifndef PROJECTION_QAE
struct QAEWeighter : QueryWeighter<QAE__O_SplitTable, QAE__L_SplitTable, QAE__S_SplitTable, QAE__N_SplitTable, QAE__R_SplitTable> {
    inline void weight(QAE__O_SplitTable& split__o_tbl, QAE__L_SplitTable& split__l_tbl, QAE__S_SplitTable& split__s_tbl, QAE__N_SplitTable& split__n_tbl, QAE__R_SplitTable& split__r_tbl) override {
        QAE__R_Weighter().weight(split__r_tbl);

        QAE__N_Weighter().weight(split__n_tbl, split__r_tbl);

        QAE__S_Weighter().weight(split__s_tbl, split__n_tbl);

        QAE__L_Weighter().weight(split__l_tbl, split__s_tbl);

        QAE__O_Weighter().weight(split__o_tbl, split__l_tbl);
    }
};
#else
struct QAEWeighter : QueryWeighter<QAE__O_SplitTable, QAE__L_SplitTable, QAE__S_SplitTable, QAE__N_SplitTable, QAE__R_SplitTable> {
    inline void weight(QAE__O_SplitTable& split__o_tbl, QAE__L_SplitTable& split__l_tbl, QAE__S_SplitTable& split__s_tbl, QAE__N_SplitTable& split__n_tbl, QAE__R_SplitTable& split__r_tbl) override {
        QAE__R_Weighter().weight(split__r_tbl);

        QAE__N_Weighter().weight(split__n_tbl, split__r_tbl);

        QAE__S_Weighter().weight(split__s_tbl, split__n_tbl);

        QAE__L_Weighter().weight(split__l_tbl, split__s_tbl);

        QAE__O_Weighter().weight(split__o_tbl, split__l_tbl);
    }
};
#endif
//------------------------------------------------------------------------------

bool QAE_A_NationSelect(void* arg, void* parcel) {
  return ((QAE__N_Parcel*)parcel)->nationKey == 24; //UNITED STATES
}

bool QAE_E_NationSelect(void* arg, void* parcel) {
  return ((QAE__N_Parcel*)parcel)->nationKey == 23; //UNITED KINGDOM
}

//------------------------------------ RandomAccessIndex ------------------------------------------
struct QAERandomAccessIndex {

    //Fields tables;
    #ifdef PROJECTION_QAE
    QAE__O_SplitTable split__o_tbl;
    QAE__L_SplitTable split__l_tbl;
    QAE__S_SplitTable split__s_tbl;
    QAE__N_SplitTable split__n_tbl;
    QAE__R_SplitTable split__r_tbl;
    #else
    QAE__O_SplitTable split__o_tbl;
    QAE__L_SplitTable split__l_tbl;
    QAE__S_SplitTable split__s_tbl;
    QAE__N_SplitTable split__n_tbl;
    QAE__R_SplitTable split__r_tbl;

    #endif
    ll numAnswers;
    
    
    //preprocessing
    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numLines) {
        cout << "\t[QAE PREPROCESSING]" << endl;
        //------------------------------------------------------- PREPROCESSING START!
        auto t1 = chrono::steady_clock::now();
        
        QAE__O_Table _o_tbl;
        QAE__L_Table _l_tbl;
        QAE__S_Table _s_tbl;
        QAE__N_Table _n_tbl;
        QAE__R_Table _r_tbl;

        _o_tbl.loadFromFile(filenames.at("_O_"), numLines.at("_O_"));
        _l_tbl.loadFromFile(filenames.at("_L_"), numLines.at("_L_"));
        _s_tbl.loadFromFile(filenames.at("_S_"), numLines.at("_S_"));
        _n_tbl.loadFromFile(filenames.at("_N_"), numLines.at("_N_"));
        _r_tbl.loadFromFile(filenames.at("_R_"), numLines.at("_R_"));
        
        auto t2 = chrono::steady_clock::now();
        
        _n_tbl = _n_tbl.select(QAE_A_NationSelect);
        _n_tbl = _n_tbl.select(QAE_E_NationSelect);
        
        QAEYannakakisReducer().reduce(_o_tbl, _l_tbl, _s_tbl, _n_tbl, _r_tbl);

        #ifdef PROJECTION_QAE
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

        QAEWeighter().weight(split__o_tbl, split__l_tbl, split__s_tbl, split__n_tbl, split__r_tbl);
        
        numAnswers = split__o_tbl.getCummulativeWeight();
        
        auto t3 = chrono::steady_clock::now();
        //cout << "reading time is " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1000.0 << " milliseconds" << endl;
        //cout << "building time is " << chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0 << " milliseconds" << endl;
        //------------------------------------------------------- PREPROCESSING DONE!

        return chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0;
    }
    
    QAEAnswer access(ll j) {
        //if(j < 0 || j > numAnswers) {
        //    cout << "tried to access answer no." << j << ", n = " << numAnswers << endl;
        //    throw runtime_error("index beyond range " + to_string(j));
        //}
        
        ll j__l_, j__s_, j__n_, j__r_;
        QAEAnswer ans;
        find_answer__O_(ans, j, j__l_);
        find_answer__L_(ans, j__l_, j__s_);
        find_answer__S_(ans, j__s_, j__n_);
        find_answer__N_(ans, j__n_, j__r_);
        find_answer__R_(ans, j__r_);
        return move(ans);
    }
    
    #if defined(INVERSE_MAPPING) || defined(INVERTED_ACCESS)
    ll index(const QAEAnswer& ans) {
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
    inline void find_answer__O_(QAEAnswer& answer, ll j/*, int& position*/, ll& j__l_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_QAE
        const auto& bucket = split__o_tbl.buckets[answer.to<QAE__O_Key>()];
        #else
        const auto& bucket = split__o_tbl.buckets[answer.to<QAE__O_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<QAE__O_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION_QAE
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__l_tbl.buckets[answer.to<QAE__L_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__l_tbl.buckets[answer.to<QAE__L_Key>()].totalWeight});
        #endif
        j__l_ = new_indices[0];
    }

    inline void find_answer__L_(QAEAnswer& answer, ll j/*, int& position*/, ll& j__s_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_QAE
        const auto& bucket = split__l_tbl.buckets[answer.to<QAE__L_Key>()];
        #else
        const auto& bucket = split__l_tbl.buckets[answer.to<QAE__L_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<QAE__L_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION_QAE
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<QAE__S_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<QAE__S_Key>()].totalWeight});
        #endif
        j__s_ = new_indices[0];
    }

    inline void find_answer__S_(QAEAnswer& answer, ll j/*, int& position*/, ll& j__n_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_QAE
        const auto& bucket = split__s_tbl.buckets[answer.to<QAE__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<QAE__S_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<QAE__S_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION_QAE
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n_tbl.buckets[answer.to<QAE__N_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n_tbl.buckets[answer.to<QAE__N_Key>()].totalWeight});
        #endif
        j__n_ = new_indices[0];
    }

    inline void find_answer__N_(QAEAnswer& answer, ll j/*, int& position*/, ll& j__r_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_QAE
        const auto& bucket = split__n_tbl.buckets[answer.to<QAE__N_Key>()];
        #else
        const auto& bucket = split__n_tbl.buckets[answer.to<QAE__N_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<QAE__N_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION_QAE
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__r_tbl.buckets[answer.to<QAE__R_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__r_tbl.buckets[answer.to<QAE__R_Key>()].totalWeight});
        #endif
        j__r_ = new_indices[0];
    }

    inline void find_answer__R_(QAEAnswer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_QAE
        const auto& bucket = split__r_tbl.buckets[answer.to<QAE__R_Key>()];
        #else
        const auto& bucket = split__r_tbl.buckets[answer.to<QAE__R_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<QAE__R_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION_QAE
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #else
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #endif
        
    }
    
    #if defined(INVERSE_MAPPING) || defined(INVERTED_ACCESS)
    inline bool find_index__O_(const QAEAnswer& answer, ll j__l_, ll& j) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_QAE
        const auto& bucket = split__o_tbl.buckets[answer.to<QAE__O_Key>()];
        #else
        const auto& bucket = split__o_tbl.buckets[answer.to<QAE__O_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION_QAE
        auto it = bucket.weightOffsetMap.find(answer.to<QAE__O_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<QAE__O_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION_QAE
        j = it->second /*offset*/ + IndexUtils::combine({j__l_}, {split__l_tbl.buckets[answer.to<QAE__L_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__l_}, {split__l_tbl.buckets[answer.to<QAE__L_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__L_(const QAEAnswer& answer, ll j__s_, ll& j) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_QAE
        const auto& bucket = split__l_tbl.buckets[answer.to<QAE__L_Key>()];
        #else
        const auto& bucket = split__l_tbl.buckets[answer.to<QAE__L_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION_QAE
        auto it = bucket.weightOffsetMap.find(answer.to<QAE__L_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<QAE__L_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION_QAE
        j = it->second /*offset*/ + IndexUtils::combine({j__s_}, {split__s_tbl.buckets[answer.to<QAE__S_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__s_}, {split__s_tbl.buckets[answer.to<QAE__S_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__S_(const QAEAnswer& answer, ll j__n_, ll& j) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_QAE
        const auto& bucket = split__s_tbl.buckets[answer.to<QAE__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<QAE__S_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION_QAE
        auto it = bucket.weightOffsetMap.find(answer.to<QAE__S_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<QAE__S_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION_QAE
        j = it->second /*offset*/ + IndexUtils::combine({j__n_}, {split__n_tbl.buckets[answer.to<QAE__N_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__n_}, {split__n_tbl.buckets[answer.to<QAE__N_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__N_(const QAEAnswer& answer, ll j__r_, ll& j) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_QAE
        const auto& bucket = split__n_tbl.buckets[answer.to<QAE__N_Key>()];
        #else
        const auto& bucket = split__n_tbl.buckets[answer.to<QAE__N_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION_QAE
        auto it = bucket.weightOffsetMap.find(answer.to<QAE__N_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<QAE__N_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION_QAE
        j = it->second /*offset*/ + IndexUtils::combine({j__r_}, {split__r_tbl.buckets[answer.to<QAE__R_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__r_}, {split__r_tbl.buckets[answer.to<QAE__R_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__R_(const QAEAnswer& answer, ll& j) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_QAE
        const auto& bucket = split__r_tbl.buckets[answer.to<QAE__R_Key>()];
        #else
        const auto& bucket = split__r_tbl.buckets[answer.to<QAE__R_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION_QAE
        auto it = bucket.weightOffsetMap.find(answer.to<QAE__R_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<QAE__R_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION_QAE
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

typedef QAERandomAccessIndex QAEIndex;

//------------------------------------------------------------------------------

#endif //RANDOMORDERENUMERATION_QAEINDEX_H