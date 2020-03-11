#ifndef RANDOMORDERENUMERATION_Q0INDEX_H
#define RANDOMORDERENUMERATION_Q0INDEX_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "../../TemplatedRandomAccess/YannakakisReducer.h"
#include "../../TemplatedRandomAccess/AbstractWeightCalculator.h"
#include "Q0__R_Parcel.h"
#include "Q0__N_Parcel.h"
#include "Q0__S_Parcel.h"
#include "Q0__PS_Parcel.h"
#include "Q0Answer.h"
#include "../../RandomAccessAuxCode/IndexUtils.h"

typedef long long ll;

using namespace std;

//------------------------------------ Yannakakis Reducer ------------------------------------------
//specifies reduction order
struct Q0YannakakisReducer : YannakakisReducer<Q0__R_Table, Q0__N_Table, Q0__S_Table, Q0__PS_Table> {
    //you just need to arrange the calls to oneBottomUp according to the tree structure
    void reduceBottomUp(Q0__R_Table& _r__tbl, Q0__N_Table& _n__tbl, Q0__S_Table& _s__tbl, Q0__PS_Table& _ps__tbl) override {
        oneBottomUp<Q0__N_Parcel, Q0__R_Parcel, Q0__R_Key>(_n__tbl, _r__tbl);
        oneBottomUp<Q0__S_Parcel, Q0__N_Parcel, Q0__N_Key>(_s__tbl, _n__tbl);
        oneBottomUp<Q0__PS_Parcel, Q0__S_Parcel, Q0__S_Key>(_ps__tbl, _s__tbl);
    }

    //you just need to arrange the calls to oneTopDown according to the tree structure
    void reduceTopDown(Q0__R_Table& _r__tbl, Q0__N_Table& _n__tbl, Q0__S_Table& _s__tbl, Q0__PS_Table& _ps__tbl) override {
        oneTopDown<Q0__S_Parcel, Q0__PS_Parcel, Q0__S_Key>(_s__tbl, _ps__tbl);
        oneTopDown<Q0__N_Parcel, Q0__S_Parcel, Q0__N_Key>(_n__tbl, _s__tbl);
        oneTopDown<Q0__R_Parcel, Q0__N_Parcel, Q0__R_Key>(_r__tbl, _n__tbl);
    }
};
//------------------------------------------------------------------------------

//------------------------------------ Table Weighter ------------------------------------------
#ifdef PROJECTION
struct Q0__R_Weighter : AbstractSingleTableWeighter<Q0__R_Key, Q0__R_Parcel> {//leaf
    inline void weightTable(Q0__R_SplitTable& split__r_tbl) override {}
};
#else
struct Q0__R_Weighter : AbstractSingleTableWeighter<Q0__R_Key, Q0__R_Parcel> {//leaf
    inline void weightTable(Q0__R_SplitTable& split__r_tbl) override {}
};
#endif


#ifdef PROJECTION
struct Q0__N_Weighter : AbstractSingleTableWeighter<Q0__N_Key, Q0__N_Parcel, Q0__R_SplitTable> {//internal node
    inline void weightTable(Q0__N_SplitTable& split__n_tbl, const Q0__R_SplitTable& split__r_tbl) override {
        weightingStep(split__n_tbl, split__r_tbl);
    }
};
#else
struct Q0__N_Weighter : AbstractSingleTableWeighter<Q0__N_Key, Q0__N_Parcel, Q0__R_SplitTable> {//internal node
    inline void weightTable(Q0__N_SplitTable& split__n_tbl, const Q0__R_SplitTable& split__r_tbl) override {
        weightingStep(split__n_tbl, split__r_tbl);
    }
};
#endif


#ifdef PROJECTION
struct Q0__S_Weighter : AbstractSingleTableWeighter<Q0__S_Key, Q0__S_Parcel, Q0__N_SplitTable> {//internal node
    inline void weightTable(Q0__S_SplitTable& split__s_tbl, const Q0__N_SplitTable& split__n_tbl) override {
        weightingStep(split__s_tbl, split__n_tbl);
    }
};
#else
struct Q0__S_Weighter : AbstractSingleTableWeighter<Q0__S_Key, Q0__S_Parcel, Q0__N_SplitTable> {//internal node
    inline void weightTable(Q0__S_SplitTable& split__s_tbl, const Q0__N_SplitTable& split__n_tbl) override {
        weightingStep(split__s_tbl, split__n_tbl);
    }
};
#endif


#ifdef PROJECTION
struct Q0__PS_Weighter : AbstractSingleTableWeighter<Q0__PS_Key, Q0__PS_Parcel, Q0__S_SplitTable> {//internal node
    inline void weightTable(Q0__PS_SplitTable& split__ps_tbl, const Q0__S_SplitTable& split__s_tbl) override {
        weightingStep(split__ps_tbl, split__s_tbl);
    }
};
#else
struct Q0__PS_Weighter : AbstractSingleTableWeighter<Q0__PS_Key, Q0__PS_Parcel, Q0__S_SplitTable> {//internal node
    inline void weightTable(Q0__PS_SplitTable& split__ps_tbl, const Q0__S_SplitTable& split__s_tbl) override {
        weightingStep(split__ps_tbl, split__s_tbl);
    }
};
#endif


#ifndef PROJECTION
struct Q0Weighter : QueryWeighter<Q0__R_SplitTable, Q0__N_SplitTable, Q0__S_SplitTable, Q0__PS_SplitTable> {
    inline void weight(Q0__R_SplitTable& split__r_tbl, Q0__N_SplitTable& split__n_tbl, Q0__S_SplitTable& split__s_tbl, Q0__PS_SplitTable& split__ps_tbl) override {
        Q0__R_Weighter().weight(split__r_tbl);

        Q0__N_Weighter().weight(split__n_tbl, split__r_tbl);

        Q0__S_Weighter().weight(split__s_tbl, split__n_tbl);

        Q0__PS_Weighter().weight(split__ps_tbl, split__s_tbl);
    }
};
#else
struct Q0Weighter : QueryWeighter<Q0__R_SplitTable, Q0__N_SplitTable, Q0__S_SplitTable, Q0__PS_SplitTable> {
    inline void weight(Q0__R_SplitTable& split__r_tbl, Q0__N_SplitTable& split__n_tbl, Q0__S_SplitTable& split__s_tbl, Q0__PS_SplitTable& split__ps_tbl) override {
        Q0__R_Weighter().weight(split__r_tbl);

        Q0__N_Weighter().weight(split__n_tbl, split__r_tbl);

        Q0__S_Weighter().weight(split__s_tbl, split__n_tbl);

        Q0__PS_Weighter().weight(split__ps_tbl, split__s_tbl);
    }
};
#endif
//------------------------------------------------------------------------------

//------------------------------------ RandomAccessIndex ------------------------------------------
struct Q0RandomAccessIndex {

    //Fields tables;
    #ifdef PROJECTION
    Q0__R_SplitTable split__r_tbl;
    Q0__N_SplitTable split__n_tbl;
    Q0__S_SplitTable split__s_tbl;
    Q0__PS_SplitTable split__ps_tbl;
    #else
    Q0__R_SplitTable split__r_tbl;
    Q0__N_SplitTable split__n_tbl;
    Q0__S_SplitTable split__s_tbl;
    Q0__PS_SplitTable split__ps_tbl;

    #endif
    ll numAnswers;
    
    
    //preprocessing
    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numLines) {
        //------------------------------------------------------- PREPROCESSING START!
        auto t1 = chrono::steady_clock::now();
        
        Q0__R_Table _r_tbl;
        Q0__N_Table _n_tbl;
        Q0__S_Table _s_tbl;
        Q0__PS_Table _ps_tbl;

        _r_tbl.loadFromFile(filenames.at("_R_"), numLines.at("_R_"));
        _n_tbl.loadFromFile(filenames.at("_N_"), numLines.at("_N_"));
        _s_tbl.loadFromFile(filenames.at("_S_"), numLines.at("_S_"));
        _ps_tbl.loadFromFile(filenames.at("_PS_"), numLines.at("_PS_"));
        
        auto t2 = chrono::steady_clock::now();
        
        Q0YannakakisReducer().reduce(_r_tbl, _n_tbl, _s_tbl, _ps_tbl);

        #ifdef PROJECTION
        split__r_tbl.loadFromTable(_r_tbl);
        split__n_tbl.loadFromTable(_n_tbl);
        split__s_tbl.loadFromTable(_s_tbl);
        split__ps_tbl.loadFromTable(_ps_tbl);
        #else
        split__r_tbl.loadFromTable(_r_tbl);
        split__n_tbl.loadFromTable(_n_tbl);
        split__s_tbl.loadFromTable(_s_tbl);
        split__ps_tbl.loadFromTable(_ps_tbl);
        #endif

        Q0Weighter().weight(split__r_tbl, split__n_tbl, split__s_tbl, split__ps_tbl);
        
        numAnswers = split__ps_tbl.getCummulativeWeight();
        
        auto t3 = chrono::steady_clock::now();
        //cout << "reading time is " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1000.0 << " milliseconds" << endl;
        //cout << "building time is " << chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0 << " milliseconds" << endl;
        //------------------------------------------------------- PREPROCESSING DONE!

        return chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0;
    }
    
    Q0Answer access(ll j) {
        //if(j < 0 || j > numAnswers) {
        //    cout << "tried to access answer no." << j << ", n = " << numAnswers << endl;
        //    throw runtime_error("index beyond range " + to_string(j));
        //}
        
        ll j__r_, j__n_, j__s_;
        Q0Answer ans;
        find_answer__PS_(ans, j, j__s_);
        find_answer__S_(ans, j__s_, j__n_);
        find_answer__N_(ans, j__n_, j__r_);
        find_answer__R_(ans, j__r_);
        return move(ans);
    }
    
    #ifdef INVERSE_MAPPING
    ll index(const Q0Answer& ans) {
        ll j__r_, j__n_, j__s_, j__ps_;
        if(!find_index__R_(ans, j__r_)) {
            return -1;
        }

        if(!find_index__N_(ans, j__r_, j__n_)) {
            return -1;
        }

        if(!find_index__S_(ans, j__n_, j__s_)) {
            return -1;
        }

        if(!find_index__PS_(ans, j__s_, j__ps_)) {
            return -1;
        }

        return j__ps_;
    }
    #endif
    
    
private:
    inline void find_answer__R_(Q0Answer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__r_tbl.buckets[answer.to<Q0__R_Key>()];
        #else
        const auto& bucket = split__r_tbl.buckets[answer.to<Q0__R_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q0__R_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #else
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #endif
        
    }

    inline void find_answer__N_(Q0Answer& answer, ll j/*, int& position*/, ll& j__r_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__n_tbl.buckets[answer.to<Q0__N_Key>()];
        #else
        const auto& bucket = split__n_tbl.buckets[answer.to<Q0__N_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q0__N_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__r_tbl.buckets[answer.to<Q0__R_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__r_tbl.buckets[answer.to<Q0__R_Key>()].totalWeight});
        #endif
        j__r_ = new_indices[0];
    }

    inline void find_answer__S_(Q0Answer& answer, ll j/*, int& position*/, ll& j__n_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__s_tbl.buckets[answer.to<Q0__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<Q0__S_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q0__S_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n_tbl.buckets[answer.to<Q0__N_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n_tbl.buckets[answer.to<Q0__N_Key>()].totalWeight});
        #endif
        j__n_ = new_indices[0];
    }

    inline void find_answer__PS_(Q0Answer& answer, ll j/*, int& position*/, ll& j__s_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q0__PS_Key>()];
        #else
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q0__PS_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q0__PS_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<Q0__S_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<Q0__S_Key>()].totalWeight});
        #endif
        j__s_ = new_indices[0];
    }
    
    #ifdef INVERSE_MAPPING
    inline bool find_index__R_(const Q0Answer& answer, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__r_tbl.buckets[answer.to<Q0__R_Key>()];
        #else
        const auto& bucket = split__r_tbl.buckets[answer.to<Q0__R_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q0__R_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q0__R_Parcel>());
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

    inline bool find_index__N_(const Q0Answer& answer, ll j__r_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__n_tbl.buckets[answer.to<Q0__N_Key>()];
        #else
        const auto& bucket = split__n_tbl.buckets[answer.to<Q0__N_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q0__N_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q0__N_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__r_}, {split__r_tbl.buckets[answer.to<Q0__R_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__r_}, {split__r_tbl.buckets[answer.to<Q0__R_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__S_(const Q0Answer& answer, ll j__n_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__s_tbl.buckets[answer.to<Q0__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<Q0__S_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q0__S_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q0__S_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__n_}, {split__n_tbl.buckets[answer.to<Q0__N_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__n_}, {split__n_tbl.buckets[answer.to<Q0__N_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__PS_(const Q0Answer& answer, ll j__s_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q0__PS_Key>()];
        #else
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q0__PS_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q0__PS_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q0__PS_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__s_}, {split__s_tbl.buckets[answer.to<Q0__S_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__s_}, {split__s_tbl.buckets[answer.to<Q0__S_Key>()].totalWeight});
        #endif
        return true;
    }
    #endif
    
    static inline int getTupleIndex(const vector<ll>& prefixSum, ll j) {
        return (upper_bound(prefixSum.begin(), prefixSum.end(), j) - prefixSum.begin() - 1);
    }
};

typedef Q0RandomAccessIndex Q0Index;

//------------------------------------------------------------------------------

#endif //RANDOMORDERENUMERATION_Q0INDEX_H