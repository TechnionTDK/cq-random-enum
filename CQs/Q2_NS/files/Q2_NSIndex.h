#ifndef RANDOMORDERENUMERATION_Q2_NSINDEX_H
#define RANDOMORDERENUMERATION_Q2_NSINDEX_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "../../TemplatedRandomAccess/YannakakisReducer.h"
#include "../../TemplatedRandomAccess/AbstractWeightCalculator.h"
#include "Q2_NS__R_Parcel.h"
#include "Q2_NS__N_Parcel.h"
#include "Q2_NS__S_Parcel.h"
#include "Q2_NS__PS_Parcel.h"
#include "Q2_NS__P_Parcel.h"
#include "Q2_NSAnswer.h"
#include "../../RandomAccessAuxCode/IndexUtils.h"

typedef long long ll;

using namespace std;

//------------------------------------ Yannakakis Reducer ------------------------------------------
//specifies reduction order
struct Q2_NSYannakakisReducer : YannakakisReducer<Q2_NS__R_Table, Q2_NS__N_Table, Q2_NS__S_Table, Q2_NS__PS_Table, Q2_NS__P_Table> {
    //you just need to arrange the calls to oneBottomUp according to the tree structure
    void reduceBottomUp(Q2_NS__R_Table& _r__tbl, Q2_NS__N_Table& _n__tbl, Q2_NS__S_Table& _s__tbl, Q2_NS__PS_Table& _ps__tbl, Q2_NS__P_Table& _p__tbl) override {
        oneBottomUp<Q2_NS__N_Parcel, Q2_NS__R_Parcel, Q2_NS__R_Key>(_n__tbl, _r__tbl);
        oneBottomUp<Q2_NS__S_Parcel, Q2_NS__N_Parcel, Q2_NS__N_Key>(_s__tbl, _n__tbl);
        oneBottomUp<Q2_NS__PS_Parcel, Q2_NS__S_Parcel, Q2_NS__S_Key>(_ps__tbl, _s__tbl);
        oneBottomUp<Q2_NS__PS_Parcel, Q2_NS__P_Parcel, Q2_NS__P_Key>(_ps__tbl, _p__tbl);
    }

    //you just need to arrange the calls to oneTopDown according to the tree structure
    void reduceTopDown(Q2_NS__R_Table& _r__tbl, Q2_NS__N_Table& _n__tbl, Q2_NS__S_Table& _s__tbl, Q2_NS__PS_Table& _ps__tbl, Q2_NS__P_Table& _p__tbl) override {
        oneTopDown<Q2_NS__S_Parcel, Q2_NS__PS_Parcel, Q2_NS__S_Key>(_s__tbl, _ps__tbl);
        oneTopDown<Q2_NS__N_Parcel, Q2_NS__S_Parcel, Q2_NS__N_Key>(_n__tbl, _s__tbl);
        oneTopDown<Q2_NS__R_Parcel, Q2_NS__N_Parcel, Q2_NS__R_Key>(_r__tbl, _n__tbl);
    }
};
//------------------------------------------------------------------------------

//------------------------------------ Table Weighter ------------------------------------------
#ifdef PROJECTION_Q2_NS
struct Q2_NS__R_Weighter : AbstractSingleTableWeighter<Q2_NS__R_Key, Q2_NS__R_Parcel> {//leaf
    inline void weightTable(Q2_NS__R_SplitTable& split__r_tbl) override {}
};
#else
struct Q2_NS__R_Weighter : AbstractSingleTableWeighter<Q2_NS__R_Key, Q2_NS__R_Parcel> {//leaf
    inline void weightTable(Q2_NS__R_SplitTable& split__r_tbl) override {}
};
#endif


#ifdef PROJECTION_Q2_NS
struct Q2_NS__N_Weighter : AbstractSingleTableWeighter<Q2_NS__N_Key, Q2_NS__N_Parcel, Q2_NS__R_SplitTable> {//internal node
    inline void weightTable(Q2_NS__N_SplitTable& split__n_tbl, const Q2_NS__R_SplitTable& split__r_tbl) override {
        weightingStep(split__n_tbl, split__r_tbl);
    }
};
#else
struct Q2_NS__N_Weighter : AbstractSingleTableWeighter<Q2_NS__N_Key, Q2_NS__N_Parcel, Q2_NS__R_SplitTable> {//internal node
    inline void weightTable(Q2_NS__N_SplitTable& split__n_tbl, const Q2_NS__R_SplitTable& split__r_tbl) override {
        weightingStep(split__n_tbl, split__r_tbl);
    }
};
#endif


#ifdef PROJECTION_Q2_NS
struct Q2_NS__S_Weighter : AbstractSingleTableWeighter<Q2_NS__S_Key, Q2_NS__S_Parcel, Q2_NS__N_SplitTable> {//internal node
    inline void weightTable(Q2_NS__S_SplitTable& split__s_tbl, const Q2_NS__N_SplitTable& split__n_tbl) override {
        weightingStep(split__s_tbl, split__n_tbl);
    }
};
#else
struct Q2_NS__S_Weighter : AbstractSingleTableWeighter<Q2_NS__S_Key, Q2_NS__S_Parcel, Q2_NS__N_SplitTable> {//internal node
    inline void weightTable(Q2_NS__S_SplitTable& split__s_tbl, const Q2_NS__N_SplitTable& split__n_tbl) override {
        weightingStep(split__s_tbl, split__n_tbl);
    }
};
#endif


#ifdef PROJECTION_Q2_NS
struct Q2_NS__P_Weighter : AbstractSingleTableWeighter<Q2_NS__P_Key, Q2_NS__P_Parcel> {//leaf
    inline void weightTable(Q2_NS__P_SplitTable& split__p_tbl) override {}
};
#else
struct Q2_NS__P_Weighter : AbstractSingleTableWeighter<Q2_NS__P_Key, Q2_NS__P_Parcel> {//leaf
    inline void weightTable(Q2_NS__P_SplitTable& split__p_tbl) override {}
};
#endif


#ifdef PROJECTION_Q2_NS
struct Q2_NS__PS_Weighter : AbstractSingleTableWeighter<Q2_NS__PS_Key, Q2_NS__PS_Parcel, Q2_NS__S_SplitTable> {//internal node
    inline void weightTable(Q2_NS__PS_SplitTable& split__ps_tbl, const Q2_NS__S_SplitTable& split__s_tbl) override {
        weightingStep(split__ps_tbl, split__s_tbl);
    }
};
#else
struct Q2_NS__PS_Weighter : AbstractSingleTableWeighter<Q2_NS__PS_Key, Q2_NS__PS_Parcel, Q2_NS__S_SplitTable> {//internal node
    inline void weightTable(Q2_NS__PS_SplitTable& split__ps_tbl, const Q2_NS__S_SplitTable& split__s_tbl) override {
        weightingStep(split__ps_tbl, split__s_tbl);
    }
};
#endif


#ifndef PROJECTION_Q2_NS
struct Q2_NSWeighter : QueryWeighter<Q2_NS__R_SplitTable, Q2_NS__N_SplitTable, Q2_NS__S_SplitTable, Q2_NS__PS_SplitTable, Q2_NS__P_SplitTable> {
    inline void weight(Q2_NS__R_SplitTable& split__r_tbl, Q2_NS__N_SplitTable& split__n_tbl, Q2_NS__S_SplitTable& split__s_tbl, Q2_NS__PS_SplitTable& split__ps_tbl, Q2_NS__P_SplitTable& split__p_tbl) override {
        Q2_NS__R_Weighter().weight(split__r_tbl);

        Q2_NS__N_Weighter().weight(split__n_tbl, split__r_tbl);

        Q2_NS__S_Weighter().weight(split__s_tbl, split__n_tbl);

        Q2_NS__P_Weighter().weight(split__p_tbl);

        Q2_NS__PS_Weighter().weight(split__ps_tbl, split__s_tbl);
    }
};
#else
struct Q2_NSWeighter : QueryWeighter<Q2_NS__R_SplitTable, Q2_NS__N_SplitTable, Q2_NS__S_SplitTable, Q2_NS__PS_SplitTable, Q2_NS__P_SplitTable> {
    inline void weight(Q2_NS__R_SplitTable& split__r_tbl, Q2_NS__N_SplitTable& split__n_tbl, Q2_NS__S_SplitTable& split__s_tbl, Q2_NS__PS_SplitTable& split__ps_tbl, Q2_NS__P_SplitTable& split__p_tbl) override {
        Q2_NS__R_Weighter().weight(split__r_tbl);

        Q2_NS__N_Weighter().weight(split__n_tbl, split__r_tbl);

        Q2_NS__S_Weighter().weight(split__s_tbl, split__n_tbl);

        Q2_NS__P_Weighter().weight(split__p_tbl);

        Q2_NS__PS_Weighter().weight(split__ps_tbl, split__s_tbl);
    }
};
#endif
//------------------------------------------------------------------------------

bool Q2_NS_N_Select(void* arg, void* parcel) {
    return ((Q2_NS__R_Parcel*)parcel)->regionKey != 0;
}

bool Q2_NS_S_Select(void* arg, void* parcel) {
  return ((Q2_NS__S_Parcel*)parcel)->suppKey % 2 == 0;
}

//------------------------------------ RandomAccessIndex ------------------------------------------
struct Q2_NSRandomAccessIndex {

    //Fields tables;
    #ifdef PROJECTION_Q2_NS
    Q2_NS__R_SplitTable split__r_tbl;
    Q2_NS__N_SplitTable split__n_tbl;
    Q2_NS__S_SplitTable split__s_tbl;
    Q2_NS__PS_SplitTable split__ps_tbl;
    Q2_NS__P_SplitTable split__p_tbl;
    #else
    Q2_NS__R_SplitTable split__r_tbl;
    Q2_NS__N_SplitTable split__n_tbl;
    Q2_NS__S_SplitTable split__s_tbl;
    Q2_NS__PS_SplitTable split__ps_tbl;
    Q2_NS__P_SplitTable split__p_tbl;

    #endif
    ll numAnswers;
    
    
    //preprocessing
    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numLines) {
        cout << "\t[Q2_NS PREPROCESSING]" << endl;
        //------------------------------------------------------- PREPROCESSING START!
        auto t1 = chrono::steady_clock::now();
        
        Q2_NS__R_Table _r_tbl;
        Q2_NS__N_Table _n_tbl;
        Q2_NS__S_Table _s_tbl;
        Q2_NS__PS_Table _ps_tbl;
        Q2_NS__P_Table _p_tbl;

        _r_tbl.loadFromFile(filenames.at("_R_"), numLines.at("_R_"));
        _n_tbl.loadFromFile(filenames.at("_N_"), numLines.at("_N_"));
        _s_tbl.loadFromFile(filenames.at("_S_"), numLines.at("_S_"));
        _ps_tbl.loadFromFile(filenames.at("_PS_"), numLines.at("_PS_"));
        _p_tbl.loadFromFile(filenames.at("_P_"), numLines.at("_P_"));
        
        auto t2 = chrono::steady_clock::now();
        
        _n_tbl = _n_tbl.select(Q2_NS_N_Select);
        _s_tbl = _s_tbl.select(Q2_NS_S_Select);
        
        Q2_NSYannakakisReducer().reduce(_r_tbl, _n_tbl, _s_tbl, _ps_tbl, _p_tbl);

        #ifdef PROJECTION_Q2_NS
        split__r_tbl.loadFromTable(_r_tbl);
        split__n_tbl.loadFromTable(_n_tbl);
        split__s_tbl.loadFromTable(_s_tbl);
        split__ps_tbl.loadFromTable(_ps_tbl);
        split__p_tbl.loadFromTable(_p_tbl);
        #else
        split__r_tbl.loadFromTable(_r_tbl);
        split__n_tbl.loadFromTable(_n_tbl);
        split__s_tbl.loadFromTable(_s_tbl);
        split__ps_tbl.loadFromTable(_ps_tbl);
        split__p_tbl.loadFromTable(_p_tbl);
        #endif

        Q2_NSWeighter().weight(split__r_tbl, split__n_tbl, split__s_tbl, split__ps_tbl, split__p_tbl);
        
        numAnswers = split__ps_tbl.getCummulativeWeight();
        
        auto t3 = chrono::steady_clock::now();
        //cout << "reading time is " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1000.0 << " milliseconds" << endl;
        //cout << "building time is " << chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0 << " milliseconds" << endl;
        //------------------------------------------------------- PREPROCESSING DONE!

        return chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0;
    }
    
    Q2_NSAnswer access(ll j) {
        //if(j < 0 || j > numAnswers) {
        //    cout << "tried to access answer no." << j << ", n = " << numAnswers << endl;
        //    throw runtime_error("index beyond range " + to_string(j));
        //}
        
        ll j__r_, j__n_, j__s_, j__p_;
        Q2_NSAnswer ans;
        find_answer__PS_(ans, j, j__s_);
        find_answer__P_(ans, j__p_);
        find_answer__S_(ans, j__s_, j__n_);
        find_answer__N_(ans, j__n_, j__r_);
        find_answer__R_(ans, j__r_);
        return move(ans);
    }
    
    #if defined(INVERSE_MAPPING) || defined(INVERTED_ACCESS)
    ll index(const Q2_NSAnswer& ans) {
        ll j__r_, j__n_, j__s_, j__ps_, j__p_;
        if(!find_index__R_(ans, j__r_)) {
            return -1;
        }

        if(!find_index__N_(ans, j__r_, j__n_)) {
            return -1;
        }

        if(!find_index__S_(ans, j__n_, j__s_)) {
            return -1;
        }

        if(!find_index__P_(ans, j__p_)) {
            return -1;
        }

        if(!find_index__PS_(ans, j__s_, j__ps_)) {
            return -1;
        }

        return j__ps_;
    }
    #endif
    
    
private:
    inline void find_answer__R_(Q2_NSAnswer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_Q2_NS
        const auto& bucket = split__r_tbl.buckets[answer.to<Q2_NS__R_Key>()];
        #else
        const auto& bucket = split__r_tbl.buckets[answer.to<Q2_NS__R_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q2_NS__R_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION_Q2_NS
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #else
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #endif
        
    }

    inline void find_answer__N_(Q2_NSAnswer& answer, ll j/*, int& position*/, ll& j__r_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_Q2_NS
        const auto& bucket = split__n_tbl.buckets[answer.to<Q2_NS__N_Key>()];
        #else
        const auto& bucket = split__n_tbl.buckets[answer.to<Q2_NS__N_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q2_NS__N_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION_Q2_NS
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__r_tbl.buckets[answer.to<Q2_NS__R_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__r_tbl.buckets[answer.to<Q2_NS__R_Key>()].totalWeight});
        #endif
        j__r_ = new_indices[0];
    }

    inline void find_answer__S_(Q2_NSAnswer& answer, ll j/*, int& position*/, ll& j__n_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_Q2_NS
        const auto& bucket = split__s_tbl.buckets[answer.to<Q2_NS__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<Q2_NS__S_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q2_NS__S_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION_Q2_NS
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n_tbl.buckets[answer.to<Q2_NS__N_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n_tbl.buckets[answer.to<Q2_NS__N_Key>()].totalWeight});
        #endif
        j__n_ = new_indices[0];
    }

    inline void find_answer__PS_(Q2_NSAnswer& answer, ll j/*, int& position*/, ll& j__s_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_Q2_NS
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q2_NS__PS_Key>()];
        #else
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q2_NS__PS_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q2_NS__PS_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION_Q2_NS
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<Q2_NS__S_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<Q2_NS__S_Key>()].totalWeight});
        #endif
        j__s_ = new_indices[0];
    }

    inline void find_answer__P_(Q2_NSAnswer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_Q2_NS
        const auto& bucket = split__p_tbl.buckets[answer.to<Q2_NS__P_Key>()];
        #else
        const auto& bucket = split__p_tbl.buckets[answer.to<Q2_NS__P_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q2_NS__P_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION_Q2_NS
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #else
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #endif
        
    }
    
    #if defined(INVERSE_MAPPING) || defined(INVERTED_ACCESS)
    inline bool find_index__R_(const Q2_NSAnswer& answer, ll& j) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_Q2_NS
        const auto& bucket = split__r_tbl.buckets[answer.to<Q2_NS__R_Key>()];
        #else
        const auto& bucket = split__r_tbl.buckets[answer.to<Q2_NS__R_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION_Q2_NS
        auto it = bucket.weightOffsetMap.find(answer.to<Q2_NS__R_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q2_NS__R_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION_Q2_NS
        j = it->second /*offset*/ /*+ IndexUtils::combine({}, {})*/;
        #else
        j = it->second /*offset*/ /*+ IndexUtils::combine({}, {})*/;
        #endif
        return true;
    }

    inline bool find_index__N_(const Q2_NSAnswer& answer, ll j__r_, ll& j) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_Q2_NS
        const auto& bucket = split__n_tbl.buckets[answer.to<Q2_NS__N_Key>()];
        #else
        const auto& bucket = split__n_tbl.buckets[answer.to<Q2_NS__N_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION_Q2_NS
        auto it = bucket.weightOffsetMap.find(answer.to<Q2_NS__N_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q2_NS__N_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION_Q2_NS
        j = it->second /*offset*/ + IndexUtils::combine({j__r_}, {split__r_tbl.buckets[answer.to<Q2_NS__R_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__r_}, {split__r_tbl.buckets[answer.to<Q2_NS__R_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__S_(const Q2_NSAnswer& answer, ll j__n_, ll& j) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_Q2_NS
        const auto& bucket = split__s_tbl.buckets[answer.to<Q2_NS__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<Q2_NS__S_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION_Q2_NS
        auto it = bucket.weightOffsetMap.find(answer.to<Q2_NS__S_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q2_NS__S_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION_Q2_NS
        j = it->second /*offset*/ + IndexUtils::combine({j__n_}, {split__n_tbl.buckets[answer.to<Q2_NS__N_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__n_}, {split__n_tbl.buckets[answer.to<Q2_NS__N_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__PS_(const Q2_NSAnswer& answer, ll j__s_, ll& j) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_Q2_NS
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q2_NS__PS_Key>()];
        #else
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q2_NS__PS_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION_Q2_NS
        auto it = bucket.weightOffsetMap.find(answer.to<Q2_NS__PS_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q2_NS__PS_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION_Q2_NS
        j = it->second /*offset*/ + IndexUtils::combine({j__s_}, {split__s_tbl.buckets[answer.to<Q2_NS__S_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__s_}, {split__s_tbl.buckets[answer.to<Q2_NS__S_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__P_(const Q2_NSAnswer& answer, ll& j) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION_Q2_NS
        const auto& bucket = split__p_tbl.buckets[answer.to<Q2_NS__P_Key>()];
        #else
        const auto& bucket = split__p_tbl.buckets[answer.to<Q2_NS__P_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION_Q2_NS
        auto it = bucket.weightOffsetMap.find(answer.to<Q2_NS__P_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q2_NS__P_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION_Q2_NS
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

typedef Q2_NSRandomAccessIndex Q2_NSIndex;

//------------------------------------------------------------------------------

#endif //RANDOMORDERENUMERATION_Q2_NSINDEX_H