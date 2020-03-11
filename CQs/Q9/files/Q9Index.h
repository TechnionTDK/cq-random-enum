#ifndef RANDOMORDERENUMERATION_Q9INDEX_H
#define RANDOMORDERENUMERATION_Q9INDEX_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "../../TemplatedRandomAccess/YannakakisReducer.h"
#include "../../TemplatedRandomAccess/AbstractWeightCalculator.h"
#include "Q9__N_Parcel.h"
#include "Q9__S_Parcel.h"
#include "Q9__L_Parcel.h"
#include "Q9__PS_Parcel.h"
#include "Q9__O_Parcel.h"
#include "Q9__P_Parcel.h"
#include "Q9Answer.h"
#include "../../RandomAccessAuxCode/IndexUtils.h"

typedef long long ll;

using namespace std;

//------------------------------------ Yannakakis Reducer ------------------------------------------
//specifies reduction order
struct Q9YannakakisReducer : YannakakisReducer<Q9__N_Table, Q9__S_Table, Q9__L_Table, Q9__PS_Table, Q9__O_Table, Q9__P_Table> {
    //you just need to arrange the calls to oneBottomUp according to the tree structure
    void reduceBottomUp(Q9__N_Table& _n__tbl, Q9__S_Table& _s__tbl, Q9__L_Table& _l__tbl, Q9__PS_Table& _ps__tbl, Q9__O_Table& _o__tbl, Q9__P_Table& _p__tbl) override {
        oneBottomUp<Q9__S_Parcel, Q9__N_Parcel, Q9__N_Key>(_s__tbl, _n__tbl);
        oneBottomUp<Q9__PS_Parcel, Q9__P_Parcel, Q9__P_Key>(_ps__tbl, _p__tbl);
        oneBottomUp<Q9__L_Parcel, Q9__S_Parcel, Q9__S_Key>(_l__tbl, _s__tbl);
        oneBottomUp<Q9__L_Parcel, Q9__O_Parcel, Q9__O_Key>(_l__tbl, _o__tbl);
        oneBottomUp<Q9__L_Parcel, Q9__PS_Parcel, Q9__PS_Key>(_l__tbl, _ps__tbl);
    }

    //you just need to arrange the calls to oneTopDown according to the tree structure
    void reduceTopDown(Q9__N_Table& _n__tbl, Q9__S_Table& _s__tbl, Q9__L_Table& _l__tbl, Q9__PS_Table& _ps__tbl, Q9__O_Table& _o__tbl, Q9__P_Table& _p__tbl) override {
        oneTopDown<Q9__S_Parcel, Q9__L_Parcel, Q9__S_Key>(_s__tbl, _l__tbl);
        oneTopDown<Q9__O_Parcel, Q9__L_Parcel, Q9__O_Key>(_o__tbl, _l__tbl);
        oneTopDown<Q9__PS_Parcel, Q9__L_Parcel, Q9__PS_Key>(_ps__tbl, _l__tbl);
        oneTopDown<Q9__N_Parcel, Q9__S_Parcel, Q9__N_Key>(_n__tbl, _s__tbl);
        oneTopDown<Q9__P_Parcel, Q9__PS_Parcel, Q9__P_Key>(_p__tbl, _ps__tbl);
    }
};
//------------------------------------------------------------------------------

//------------------------------------ Table Weighter ------------------------------------------
#ifdef PROJECTION
struct Q9__N_Weighter : AbstractSingleTableWeighter<Q9__N_Key, Q9__N_Parcel> {//leaf
    inline void weightTable(Q9__N_SplitTable& split__n_tbl) override {}
};
#else
struct Q9__N_Weighter : AbstractSingleTableWeighter<Q9__N_Key, Q9__N_Parcel> {//leaf
    inline void weightTable(Q9__N_SplitTable& split__n_tbl) override {}
};
#endif


#ifdef PROJECTION
struct Q9__P_Weighter : AbstractSingleTableWeighter<Q9__P_Key, Q9__P_Parcel> {//leaf
    inline void weightTable(Q9__P_SplitTable& split__p_tbl) override {}
};
#else
struct Q9__P_Weighter : AbstractSingleTableWeighter<Q9__P_Key, Q9__P_Parcel> {//leaf
    inline void weightTable(Q9__P_SplitTable& split__p_tbl) override {}
};
#endif


#ifdef PROJECTION
struct Q9__S_Weighter : AbstractSingleTableWeighter<Q9__S_Key, Q9__S_Parcel, Q9__N_SplitTable> {//internal node
    inline void weightTable(Q9__S_SplitTable& split__s_tbl, const Q9__N_SplitTable& split__n_tbl) override {
        weightingStep(split__s_tbl, split__n_tbl);
    }
};
#else
struct Q9__S_Weighter : AbstractSingleTableWeighter<Q9__S_Key, Q9__S_Parcel, Q9__N_SplitTable> {//internal node
    inline void weightTable(Q9__S_SplitTable& split__s_tbl, const Q9__N_SplitTable& split__n_tbl) override {
        weightingStep(split__s_tbl, split__n_tbl);
    }
};
#endif


#ifdef PROJECTION
struct Q9__O_Weighter : AbstractSingleTableWeighter<Q9__O_Key, Q9__O_Parcel> {//leaf
    inline void weightTable(Q9__O_SplitTable& split__o_tbl) override {}
};
#else
struct Q9__O_Weighter : AbstractSingleTableWeighter<Q9__O_Key, Q9__O_Parcel> {//leaf
    inline void weightTable(Q9__O_SplitTable& split__o_tbl) override {}
};
#endif


#ifdef PROJECTION
struct Q9__PS_Weighter : AbstractSingleTableWeighter<Q9__PS_Key, Q9__PS_Parcel, Q9__P_SplitTable> {//internal node
    inline void weightTable(Q9__PS_SplitTable& split__ps_tbl, const Q9__P_SplitTable& split__p_tbl) override {
        weightingStep(split__ps_tbl, split__p_tbl);
    }
};
#else
struct Q9__PS_Weighter : AbstractSingleTableWeighter<Q9__PS_Key, Q9__PS_Parcel, Q9__P_SplitTable> {//internal node
    inline void weightTable(Q9__PS_SplitTable& split__ps_tbl, const Q9__P_SplitTable& split__p_tbl) override {
        weightingStep(split__ps_tbl, split__p_tbl);
    }
};
#endif


#ifdef PROJECTION
struct Q9__L_Weighter : AbstractSingleTableWeighter<Q9__L_Key, Q9__L_Parcel, Q9__S_SplitTable, Q9__O_SplitTable, Q9__PS_SplitTable> {//internal node
    inline void weightTable(Q9__L_SplitTable& split__l_tbl, const Q9__S_SplitTable& split__s_tbl, const Q9__O_SplitTable& split__o_tbl, const Q9__PS_SplitTable& split__ps_tbl) override {
        weightingStep(split__l_tbl, split__s_tbl);
        weightingStep(split__l_tbl, split__o_tbl);
        weightingStep(split__l_tbl, split__ps_tbl);
    }
};
#else
struct Q9__L_Weighter : AbstractSingleTableWeighter<Q9__L_Key, Q9__L_Parcel, Q9__S_SplitTable, Q9__O_SplitTable, Q9__PS_SplitTable> {//internal node
    inline void weightTable(Q9__L_SplitTable& split__l_tbl, const Q9__S_SplitTable& split__s_tbl, const Q9__O_SplitTable& split__o_tbl, const Q9__PS_SplitTable& split__ps_tbl) override {
        weightingStep(split__l_tbl, split__s_tbl);
        weightingStep(split__l_tbl, split__o_tbl);
        weightingStep(split__l_tbl, split__ps_tbl);
    }
};
#endif


#ifndef PROJECTION
struct Q9Weighter : QueryWeighter<Q9__N_SplitTable, Q9__S_SplitTable, Q9__L_SplitTable, Q9__PS_SplitTable, Q9__O_SplitTable, Q9__P_SplitTable> {
    inline void weight(Q9__N_SplitTable& split__n_tbl, Q9__S_SplitTable& split__s_tbl, Q9__L_SplitTable& split__l_tbl, Q9__PS_SplitTable& split__ps_tbl, Q9__O_SplitTable& split__o_tbl, Q9__P_SplitTable& split__p_tbl) override {
        Q9__N_Weighter().weight(split__n_tbl);

        Q9__P_Weighter().weight(split__p_tbl);

        Q9__S_Weighter().weight(split__s_tbl, split__n_tbl);

        Q9__O_Weighter().weight(split__o_tbl);

        Q9__PS_Weighter().weight(split__ps_tbl, split__p_tbl);

        Q9__L_Weighter().weight(split__l_tbl, split__s_tbl, split__o_tbl, split__ps_tbl);
    }
};
#else
struct Q9Weighter : QueryWeighter<Q9__N_SplitTable, Q9__S_SplitTable, Q9__L_SplitTable, Q9__PS_SplitTable, Q9__O_SplitTable, Q9__P_SplitTable> {
    inline void weight(Q9__N_SplitTable& split__n_tbl, Q9__S_SplitTable& split__s_tbl, Q9__L_SplitTable& split__l_tbl, Q9__PS_SplitTable& split__ps_tbl, Q9__O_SplitTable& split__o_tbl, Q9__P_SplitTable& split__p_tbl) override {
        Q9__N_Weighter().weight(split__n_tbl);

        Q9__P_Weighter().weight(split__p_tbl);

        Q9__S_Weighter().weight(split__s_tbl, split__n_tbl);

        Q9__O_Weighter().weight(split__o_tbl);

        Q9__PS_Weighter().weight(split__ps_tbl, split__p_tbl);

        Q9__L_Weighter().weight(split__l_tbl, split__s_tbl, split__o_tbl, split__ps_tbl);
    }
};
#endif
//------------------------------------------------------------------------------

//------------------------------------ RandomAccessIndex ------------------------------------------
struct Q9RandomAccessIndex {

    //Fields tables;
    #ifdef PROJECTION
    Q9__N_SplitTable split__n_tbl;
    Q9__S_SplitTable split__s_tbl;
    Q9__L_SplitTable split__l_tbl;
    Q9__PS_SplitTable split__ps_tbl;
    Q9__O_SplitTable split__o_tbl;
    Q9__P_SplitTable split__p_tbl;
    #else
    Q9__N_SplitTable split__n_tbl;
    Q9__S_SplitTable split__s_tbl;
    Q9__L_SplitTable split__l_tbl;
    Q9__PS_SplitTable split__ps_tbl;
    Q9__O_SplitTable split__o_tbl;
    Q9__P_SplitTable split__p_tbl;

    #endif
    ll numAnswers;
    
    
    //preprocessing
    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numLines) {
        //------------------------------------------------------- PREPROCESSING START!
        auto t1 = chrono::steady_clock::now();
        
        Q9__N_Table _n_tbl;
        Q9__S_Table _s_tbl;
        Q9__L_Table _l_tbl;
        Q9__PS_Table _ps_tbl;
        Q9__O_Table _o_tbl;
        Q9__P_Table _p_tbl;

        _n_tbl.loadFromFile(filenames.at("_N_"), numLines.at("_N_"));
        _s_tbl.loadFromFile(filenames.at("_S_"), numLines.at("_S_"));
        _l_tbl.loadFromFile(filenames.at("_L_"), numLines.at("_L_"));
        _ps_tbl.loadFromFile(filenames.at("_PS_"), numLines.at("_PS_"));
        _o_tbl.loadFromFile(filenames.at("_O_"), numLines.at("_O_"));
        _p_tbl.loadFromFile(filenames.at("_P_"), numLines.at("_P_"));
        
        auto t2 = chrono::steady_clock::now();
        
        Q9YannakakisReducer().reduce(_n_tbl, _s_tbl, _l_tbl, _ps_tbl, _o_tbl, _p_tbl);

        #ifdef PROJECTION
        split__n_tbl.loadFromTable(_n_tbl);
        split__s_tbl.loadFromTable(_s_tbl);
        split__l_tbl.loadFromTable(_l_tbl);
        split__ps_tbl.loadFromTable(_ps_tbl);
        split__o_tbl.loadFromTable(_o_tbl);
        split__p_tbl.loadFromTable(_p_tbl);
        #else
        split__n_tbl.loadFromTable(_n_tbl);
        split__s_tbl.loadFromTable(_s_tbl);
        split__l_tbl.loadFromTable(_l_tbl);
        split__ps_tbl.loadFromTable(_ps_tbl);
        split__o_tbl.loadFromTable(_o_tbl);
        split__p_tbl.loadFromTable(_p_tbl);
        #endif

        Q9Weighter().weight(split__n_tbl, split__s_tbl, split__l_tbl, split__ps_tbl, split__o_tbl, split__p_tbl);
        
        numAnswers = split__l_tbl.getCummulativeWeight();
        
        auto t3 = chrono::steady_clock::now();
        //cout << "reading time is " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1000.0 << " milliseconds" << endl;
        //cout << "building time is " << chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0 << " milliseconds" << endl;
        //------------------------------------------------------- PREPROCESSING DONE!

        return chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0;
    }
    
    Q9Answer access(ll j) {
        //if(j < 0 || j > numAnswers) {
        //    cout << "tried to access answer no." << j << ", n = " << numAnswers << endl;
        //    throw runtime_error("index beyond range " + to_string(j));
        //}
        
        ll j__n_, j__s_, j__ps_, j__o_, j__p_;
        Q9Answer ans;
        find_answer__L_(ans, j, j__s_, j__o_, j__ps_);
        find_answer__S_(ans, j__s_, j__n_);
        find_answer__O_(ans, j__o_);
        find_answer__PS_(ans, j__ps_, j__p_);
        find_answer__N_(ans, j__n_);
        find_answer__P_(ans, j__p_);
        return move(ans);
    }
    
    #ifdef INVERSE_MAPPING
    ll index(const Q9Answer& ans) {
        ll j__n_, j__s_, j__l_, j__ps_, j__o_, j__p_;
        if(!find_index__N_(ans, j__n_)) {
            return -1;
        }

        if(!find_index__P_(ans, j__p_)) {
            return -1;
        }

        if(!find_index__S_(ans, j__n_, j__s_)) {
            return -1;
        }

        if(!find_index__O_(ans, j__o_)) {
            return -1;
        }

        if(!find_index__PS_(ans, j__p_, j__ps_)) {
            return -1;
        }

        if(!find_index__L_(ans, j__s_, j__o_, j__ps_, j__l_)) {
            return -1;
        }

        return j__l_;
    }
    #endif
    
    
private:
    inline void find_answer__N_(Q9Answer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__n_tbl.buckets[answer.to<Q9__N_Key>()];
        #else
        const auto& bucket = split__n_tbl.buckets[answer.to<Q9__N_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q9__N_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #else
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #endif
        
    }

    inline void find_answer__S_(Q9Answer& answer, ll j/*, int& position*/, ll& j__n_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__s_tbl.buckets[answer.to<Q9__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<Q9__S_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q9__S_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n_tbl.buckets[answer.to<Q9__N_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n_tbl.buckets[answer.to<Q9__N_Key>()].totalWeight});
        #endif
        j__n_ = new_indices[0];
    }

    inline void find_answer__L_(Q9Answer& answer, ll j/*, int& position*/, ll& j__s_, ll& j__o_, ll& j__ps_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__l_tbl.buckets[answer.to<Q9__L_Key>()];
        #else
        const auto& bucket = split__l_tbl.buckets[answer.to<Q9__L_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q9__L_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<Q9__S_Key>()].totalWeight,
                                                                        split__o_tbl.buckets[answer.to<Q9__O_Key>()].totalWeight,
                                                                        split__ps_tbl.buckets[answer.to<Q9__PS_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<Q9__S_Key>()].totalWeight,
                                                                        split__o_tbl.buckets[answer.to<Q9__O_Key>()].totalWeight,
                                                                        split__ps_tbl.buckets[answer.to<Q9__PS_Key>()].totalWeight});
        #endif
        j__s_ = new_indices[0];
        j__o_ = new_indices[1];
        j__ps_ = new_indices[2];
    }

    inline void find_answer__PS_(Q9Answer& answer, ll j/*, int& position*/, ll& j__p_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q9__PS_Key>()];
        #else
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q9__PS_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q9__PS_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__p_tbl.buckets[answer.to<Q9__P_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__p_tbl.buckets[answer.to<Q9__P_Key>()].totalWeight});
        #endif
        j__p_ = new_indices[0];
    }

    inline void find_answer__O_(Q9Answer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__o_tbl.buckets[answer.to<Q9__O_Key>()];
        #else
        const auto& bucket = split__o_tbl.buckets[answer.to<Q9__O_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q9__O_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #else
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #endif
        
    }

    inline void find_answer__P_(Q9Answer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__p_tbl.buckets[answer.to<Q9__P_Key>()];
        #else
        const auto& bucket = split__p_tbl.buckets[answer.to<Q9__P_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q9__P_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #else
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #endif
        
    }
    
    #ifdef INVERSE_MAPPING
    inline bool find_index__N_(const Q9Answer& answer, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__n_tbl.buckets[answer.to<Q9__N_Key>()];
        #else
        const auto& bucket = split__n_tbl.buckets[answer.to<Q9__N_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__N_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__N_Parcel>());
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

    inline bool find_index__S_(const Q9Answer& answer, ll j__n_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__s_tbl.buckets[answer.to<Q9__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<Q9__S_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__S_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__S_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__n_}, {split__n_tbl.buckets[answer.to<Q9__N_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__n_}, {split__n_tbl.buckets[answer.to<Q9__N_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__L_(const Q9Answer& answer, ll j__s_, ll j__o_, ll j__ps_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__l_tbl.buckets[answer.to<Q9__L_Key>()];
        #else
        const auto& bucket = split__l_tbl.buckets[answer.to<Q9__L_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__L_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__L_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__s_, j__o_, j__ps_}, {split__s_tbl.buckets[answer.to<Q9__S_Key>()].totalWeight,
                                                                        split__o_tbl.buckets[answer.to<Q9__O_Key>()].totalWeight,
                                                                        split__ps_tbl.buckets[answer.to<Q9__PS_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__s_, j__o_, j__ps_}, {split__s_tbl.buckets[answer.to<Q9__S_Key>()].totalWeight,
                                                                        split__o_tbl.buckets[answer.to<Q9__O_Key>()].totalWeight,
                                                                        split__ps_tbl.buckets[answer.to<Q9__PS_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__PS_(const Q9Answer& answer, ll j__p_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q9__PS_Key>()];
        #else
        const auto& bucket = split__ps_tbl.buckets[answer.to<Q9__PS_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__PS_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__PS_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__p_}, {split__p_tbl.buckets[answer.to<Q9__P_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__p_}, {split__p_tbl.buckets[answer.to<Q9__P_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__O_(const Q9Answer& answer, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__o_tbl.buckets[answer.to<Q9__O_Key>()];
        #else
        const auto& bucket = split__o_tbl.buckets[answer.to<Q9__O_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__O_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__O_Parcel>());
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

    inline bool find_index__P_(const Q9Answer& answer, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__p_tbl.buckets[answer.to<Q9__P_Key>()];
        #else
        const auto& bucket = split__p_tbl.buckets[answer.to<Q9__P_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__P_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q9__P_Parcel>());
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

typedef Q9RandomAccessIndex Q9Index;

//------------------------------------------------------------------------------

#endif //RANDOMORDERENUMERATION_Q9INDEX_H