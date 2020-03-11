#ifndef RANDOMORDERENUMERATION_Q7_1INDEX_H
#define RANDOMORDERENUMERATION_Q7_1INDEX_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "../../TemplatedRandomAccess/YannakakisReducer.h"
#include "../../TemplatedRandomAccess/AbstractWeightCalculator.h"
#include "Q7_1__O_Parcel.h"
#include "Q7_1__C_Parcel.h"
#include "Q7_1__L_Parcel.h"
#include "Q7_1__N2_Parcel.h"
#include "Q7_1__S_Parcel.h"
#include "Q7_1__N1_Parcel.h"
#include "Q7_1Answer.h"
#include "../../RandomAccessAuxCode/IndexUtils.h"

typedef long long ll;

using namespace std;

//------------------------------------ Yannakakis Reducer ------------------------------------------
//specifies reduction order
struct Q7_1YannakakisReducer : YannakakisReducer<Q7_1__O_Table, Q7_1__C_Table, Q7_1__L_Table, Q7_1__N2_Table, Q7_1__S_Table, Q7_1__N1_Table> {
    //you just need to arrange the calls to oneBottomUp according to the tree structure
    void reduceBottomUp(Q7_1__O_Table& _o__tbl, Q7_1__C_Table& _c__tbl, Q7_1__L_Table& _l__tbl, Q7_1__N2_Table& _n2__tbl, Q7_1__S_Table& _s__tbl, Q7_1__N1_Table& _n1__tbl) override {
        oneBottomUp<Q7_1__C_Parcel, Q7_1__N2_Parcel, Q7_1__N2_Key>(_c__tbl, _n2__tbl);
        oneBottomUp<Q7_1__O_Parcel, Q7_1__C_Parcel, Q7_1__C_Key>(_o__tbl, _c__tbl);
        oneBottomUp<Q7_1__S_Parcel, Q7_1__N1_Parcel, Q7_1__N1_Key>(_s__tbl, _n1__tbl);
        oneBottomUp<Q7_1__L_Parcel, Q7_1__S_Parcel, Q7_1__S_Key>(_l__tbl, _s__tbl);
        oneBottomUp<Q7_1__O_Parcel, Q7_1__L_Parcel, Q7_1__L_Key>(_o__tbl, _l__tbl);
    }

    //you just need to arrange the calls to oneTopDown according to the tree structure
    void reduceTopDown(Q7_1__O_Table& _o__tbl, Q7_1__C_Table& _c__tbl, Q7_1__L_Table& _l__tbl, Q7_1__N2_Table& _n2__tbl, Q7_1__S_Table& _s__tbl, Q7_1__N1_Table& _n1__tbl) override {
        oneTopDown<Q7_1__L_Parcel, Q7_1__O_Parcel, Q7_1__L_Key>(_l__tbl, _o__tbl);
        oneTopDown<Q7_1__C_Parcel, Q7_1__O_Parcel, Q7_1__C_Key>(_c__tbl, _o__tbl);
        oneTopDown<Q7_1__N2_Parcel, Q7_1__C_Parcel, Q7_1__N2_Key>(_n2__tbl, _c__tbl);
        oneTopDown<Q7_1__S_Parcel, Q7_1__L_Parcel, Q7_1__S_Key>(_s__tbl, _l__tbl);
        oneTopDown<Q7_1__N1_Parcel, Q7_1__S_Parcel, Q7_1__N1_Key>(_n1__tbl, _s__tbl);
    }
};
//------------------------------------------------------------------------------

//------------------------------------ Table Weighter ------------------------------------------
#ifdef PROJECTION
struct Q7_1__N2_Weighter : AbstractSingleTableWeighter<Q7_1__N2_Key, Q7_1__N2_Parcel> {//leaf
    inline void weightTable(Q7_1__N2_SplitTable& split__n2_tbl) override {}
};
#else
struct Q7_1__N2_Weighter : AbstractSingleTableWeighter<Q7_1__N2_Key, Q7_1__N2_Parcel> {//leaf
    inline void weightTable(Q7_1__N2_SplitTable& split__n2_tbl) override {}
};
#endif


#ifdef PROJECTION
struct Q7_1__C_Weighter : AbstractSingleTableWeighter<Q7_1__C_Key, Q7_1__C_Parcel, Q7_1__N2_SplitTable> {//internal node
    inline void weightTable(Q7_1__C_SplitTable& split__c_tbl, const Q7_1__N2_SplitTable& split__n2_tbl) override {
        weightingStep(split__c_tbl, split__n2_tbl);
    }
};
#else
struct Q7_1__C_Weighter : AbstractSingleTableWeighter<Q7_1__C_Key, Q7_1__C_Parcel, Q7_1__N2_SplitTable> {//internal node
    inline void weightTable(Q7_1__C_SplitTable& split__c_tbl, const Q7_1__N2_SplitTable& split__n2_tbl) override {
        weightingStep(split__c_tbl, split__n2_tbl);
    }
};
#endif


#ifdef PROJECTION
struct Q7_1__N1_Weighter : AbstractSingleTableWeighter<Q7_1__N1_Key, Q7_1__N1_Parcel> {//leaf
    inline void weightTable(Q7_1__N1_SplitTable& split__n1_tbl) override {}
};
#else
struct Q7_1__N1_Weighter : AbstractSingleTableWeighter<Q7_1__N1_Key, Q7_1__N1_Parcel> {//leaf
    inline void weightTable(Q7_1__N1_SplitTable& split__n1_tbl) override {}
};
#endif


#ifdef PROJECTION
struct Q7_1__S_Weighter : AbstractSingleTableWeighter<Q7_1__S_Key, Q7_1__S_Parcel, Q7_1__N1_SplitTable> {//internal node
    inline void weightTable(Q7_1__S_SplitTable& split__s_tbl, const Q7_1__N1_SplitTable& split__n1_tbl) override {
        weightingStep(split__s_tbl, split__n1_tbl);
    }
};
#else
struct Q7_1__S_Weighter : AbstractSingleTableWeighter<Q7_1__S_Key, Q7_1__S_Parcel, Q7_1__N1_SplitTable> {//internal node
    inline void weightTable(Q7_1__S_SplitTable& split__s_tbl, const Q7_1__N1_SplitTable& split__n1_tbl) override {
        weightingStep(split__s_tbl, split__n1_tbl);
    }
};
#endif


#ifdef PROJECTION
struct Q7_1__L_Weighter : AbstractSingleTableWeighter<Q7_1__L_Key, Q7_1__L_Parcel, Q7_1__S_SplitTable> {//internal node
    inline void weightTable(Q7_1__L_SplitTable& split__l_tbl, const Q7_1__S_SplitTable& split__s_tbl) override {
        weightingStep(split__l_tbl, split__s_tbl);
    }
};
#else
struct Q7_1__L_Weighter : AbstractSingleTableWeighter<Q7_1__L_Key, Q7_1__L_Parcel, Q7_1__S_SplitTable> {//internal node
    inline void weightTable(Q7_1__L_SplitTable& split__l_tbl, const Q7_1__S_SplitTable& split__s_tbl) override {
        weightingStep(split__l_tbl, split__s_tbl);
    }
};
#endif


#ifdef PROJECTION
struct Q7_1__O_Weighter : AbstractSingleTableWeighter<Q7_1__O_Key, Q7_1__O_Parcel, Q7_1__L_SplitTable, Q7_1__C_SplitTable> {//internal node
    inline void weightTable(Q7_1__O_SplitTable& split__o_tbl, const Q7_1__L_SplitTable& split__l_tbl, const Q7_1__C_SplitTable& split__c_tbl) override {
        weightingStep(split__o_tbl, split__l_tbl);
        weightingStep(split__o_tbl, split__c_tbl);
    }
};
#else
struct Q7_1__O_Weighter : AbstractSingleTableWeighter<Q7_1__O_Key, Q7_1__O_Parcel, Q7_1__L_SplitTable, Q7_1__C_SplitTable> {//internal node
    inline void weightTable(Q7_1__O_SplitTable& split__o_tbl, const Q7_1__L_SplitTable& split__l_tbl, const Q7_1__C_SplitTable& split__c_tbl) override {
        weightingStep(split__o_tbl, split__l_tbl);
        weightingStep(split__o_tbl, split__c_tbl);
    }
};
#endif


#ifndef PROJECTION
struct Q7_1Weighter : QueryWeighter<Q7_1__O_SplitTable, Q7_1__C_SplitTable, Q7_1__L_SplitTable, Q7_1__N2_SplitTable, Q7_1__S_SplitTable, Q7_1__N1_SplitTable> {
    inline void weight(Q7_1__O_SplitTable& split__o_tbl, Q7_1__C_SplitTable& split__c_tbl, Q7_1__L_SplitTable& split__l_tbl, Q7_1__N2_SplitTable& split__n2_tbl, Q7_1__S_SplitTable& split__s_tbl, Q7_1__N1_SplitTable& split__n1_tbl) override {
        Q7_1__N2_Weighter().weight(split__n2_tbl);

        Q7_1__C_Weighter().weight(split__c_tbl, split__n2_tbl);

        Q7_1__N1_Weighter().weight(split__n1_tbl);

        Q7_1__S_Weighter().weight(split__s_tbl, split__n1_tbl);

        Q7_1__L_Weighter().weight(split__l_tbl, split__s_tbl);

        Q7_1__O_Weighter().weight(split__o_tbl, split__l_tbl, split__c_tbl);
    }
};
#else
struct Q7_1Weighter : QueryWeighter<Q7_1__O_SplitTable, Q7_1__C_SplitTable, Q7_1__L_SplitTable, Q7_1__N2_SplitTable, Q7_1__S_SplitTable, Q7_1__N1_SplitTable> {
    inline void weight(Q7_1__O_SplitTable& split__o_tbl, Q7_1__C_SplitTable& split__c_tbl, Q7_1__L_SplitTable& split__l_tbl, Q7_1__N2_SplitTable& split__n2_tbl, Q7_1__S_SplitTable& split__s_tbl, Q7_1__N1_SplitTable& split__n1_tbl) override {
        Q7_1__N2_Weighter().weight(split__n2_tbl);

        Q7_1__C_Weighter().weight(split__c_tbl, split__n2_tbl);

        Q7_1__N1_Weighter().weight(split__n1_tbl);

        Q7_1__S_Weighter().weight(split__s_tbl, split__n1_tbl);

        Q7_1__L_Weighter().weight(split__l_tbl, split__s_tbl);

        Q7_1__O_Weighter().weight(split__o_tbl, split__l_tbl, split__c_tbl);
    }
};
#endif
//------------------------------------------------------------------------------

bool Q7_1_N1_NationSelect(void* arg, void* parcel) {
  return ((Q7_1__N1_Parcel*)parcel)->n1_name == "UNITED STATES";
}

//------------------------------------ RandomAccessIndex ------------------------------------------
struct Q7_1RandomAccessIndex {

    //Fields tables;
    #ifdef PROJECTION
    Q7_1__O_SplitTable split__o_tbl;
    Q7_1__C_SplitTable split__c_tbl;
    Q7_1__L_SplitTable split__l_tbl;
    Q7_1__N2_SplitTable split__n2_tbl;
    Q7_1__S_SplitTable split__s_tbl;
    Q7_1__N1_SplitTable split__n1_tbl;
    #else
    Q7_1__O_SplitTable split__o_tbl;
    Q7_1__C_SplitTable split__c_tbl;
    Q7_1__L_SplitTable split__l_tbl;
    Q7_1__N2_SplitTable split__n2_tbl;
    Q7_1__S_SplitTable split__s_tbl;
    Q7_1__N1_SplitTable split__n1_tbl;

    #endif
    ll numAnswers;
    
    
    //preprocessing
    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numLines) {
        cout << "\t[Q7_1 PREPROCESSING]" << endl;
        //------------------------------------------------------- PREPROCESSING START!
        auto t1 = chrono::steady_clock::now();
        
        Q7_1__O_Table _o_tbl;
        Q7_1__C_Table _c_tbl;
        Q7_1__L_Table _l_tbl;
        Q7_1__N2_Table _n2_tbl;
        Q7_1__S_Table _s_tbl;
        Q7_1__N1_Table _n1_tbl;

        _o_tbl.loadFromFile(filenames.at("_O_"), numLines.at("_O_"));
        _c_tbl.loadFromFile(filenames.at("_C_"), numLines.at("_C_"));
        _l_tbl.loadFromFile(filenames.at("_L_"), numLines.at("_L_"));
        _n2_tbl.loadFromFile(filenames.at("_N2_"), numLines.at("_N2_"));
        _s_tbl.loadFromFile(filenames.at("_S_"), numLines.at("_S_"));
        _n1_tbl.loadFromFile(filenames.at("_N1_"), numLines.at("_N1_")/*, Q7_1_N1_NationSelect*/);
        
        auto t2 = chrono::steady_clock::now();
        
        _n1_tbl = _n1_tbl.select(Q7_1_N1_NationSelect);
        
        Q7_1YannakakisReducer().reduce(_o_tbl, _c_tbl, _l_tbl, _n2_tbl, _s_tbl, _n1_tbl);

        #ifdef PROJECTION
        split__o_tbl.loadFromTable(_o_tbl);
        split__c_tbl.loadFromTable(_c_tbl);
        split__l_tbl.loadFromTable(_l_tbl);
        split__n2_tbl.loadFromTable(_n2_tbl);
        split__s_tbl.loadFromTable(_s_tbl);
        split__n1_tbl.loadFromTable(_n1_tbl);
        #else
        split__o_tbl.loadFromTable(_o_tbl);
        split__c_tbl.loadFromTable(_c_tbl);
        split__l_tbl.loadFromTable(_l_tbl);
        split__n2_tbl.loadFromTable(_n2_tbl);
        split__s_tbl.loadFromTable(_s_tbl);
        split__n1_tbl.loadFromTable(_n1_tbl);
        #endif

        Q7_1Weighter().weight(split__o_tbl, split__c_tbl, split__l_tbl, split__n2_tbl, split__s_tbl, split__n1_tbl);
        
        numAnswers = split__o_tbl.getCummulativeWeight();
        
        auto t3 = chrono::steady_clock::now();
        cout << "Q7_1 READING IN MSEC is " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1000.0 << " milliseconds" << endl;
        cout << "Q7_1 PREPROCESSING IN MSEC is " << chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0 << " milliseconds" << endl;
        //------------------------------------------------------- PREPROCESSING DONE!

        return chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0;
    }
    
    Q7_1Answer access(ll j) {
        //if(j < 0 || j > numAnswers) {
        //    cout << "tried to access answer no." << j << ", n = " << numAnswers << endl;
        //    throw runtime_error("index beyond range " + to_string(j));
        //}
        
        ll j__c_, j__l_, j__n2_, j__s_, j__n1_;
        Q7_1Answer ans;
        find_answer__O_(ans, j, j__l_, j__c_);
        find_answer__C_(ans, j__c_, j__n2_);
        find_answer__L_(ans, j__l_, j__s_);
        find_answer__N2_(ans, j__n2_);
        find_answer__S_(ans, j__s_, j__n1_);
        find_answer__N1_(ans, j__n1_);
        return move(ans);
    }
    
    #if defined(INVERSE_MAPPING) || defined(INVERTED_ACCESS)
    ll index(const Q7_1Answer& ans) {
        ll j__o_, j__c_, j__l_, j__n2_, j__s_, j__n1_;
        if(!find_index__N2_(ans, j__n2_)) {
            return -1;
        }

        if(!find_index__C_(ans, j__n2_, j__c_)) {
            return -1;
        }

        if(!find_index__N1_(ans, j__n1_)) {
            return -1;
        }

        if(!find_index__S_(ans, j__n1_, j__s_)) {
            return -1;
        }

        if(!find_index__L_(ans, j__s_, j__l_)) {
            return -1;
        }

        if(!find_index__O_(ans, j__l_, j__c_, j__o_)) {
            return -1;
        }

        return j__o_;
    }
    #endif
    
    
private:
    inline void find_answer__O_(Q7_1Answer& answer, ll j/*, int& position*/, ll& j__l_, ll& j__c_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__o_tbl.buckets[answer.to<Q7_1__O_Key>()];
        #else
        const auto& bucket = split__o_tbl.buckets[answer.to<Q7_1__O_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q7_1__O_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__l_tbl.buckets[answer.to<Q7_1__L_Key>()].totalWeight,
                                                                        split__c_tbl.buckets[answer.to<Q7_1__C_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__l_tbl.buckets[answer.to<Q7_1__L_Key>()].totalWeight,
                                                                        split__c_tbl.buckets[answer.to<Q7_1__C_Key>()].totalWeight});
        #endif
        j__l_ = new_indices[0];
        j__c_ = new_indices[1];
    }

    inline void find_answer__C_(Q7_1Answer& answer, ll j/*, int& position*/, ll& j__n2_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__c_tbl.buckets[answer.to<Q7_1__C_Key>()];
        #else
        const auto& bucket = split__c_tbl.buckets[answer.to<Q7_1__C_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q7_1__C_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n2_tbl.buckets[answer.to<Q7_1__N2_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n2_tbl.buckets[answer.to<Q7_1__N2_Key>()].totalWeight});
        #endif
        j__n2_ = new_indices[0];
    }

    inline void find_answer__L_(Q7_1Answer& answer, ll j/*, int& position*/, ll& j__s_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__l_tbl.buckets[answer.to<Q7_1__L_Key>()];
        #else
        const auto& bucket = split__l_tbl.buckets[answer.to<Q7_1__L_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q7_1__L_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<Q7_1__S_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__s_tbl.buckets[answer.to<Q7_1__S_Key>()].totalWeight});
        #endif
        j__s_ = new_indices[0];
    }

    inline void find_answer__N2_(Q7_1Answer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__n2_tbl.buckets[answer.to<Q7_1__N2_Key>()];
        #else
        const auto& bucket = split__n2_tbl.buckets[answer.to<Q7_1__N2_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q7_1__N2_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #else
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #endif
        
    }

    inline void find_answer__S_(Q7_1Answer& answer, ll j/*, int& position*/, ll& j__n1_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__s_tbl.buckets[answer.to<Q7_1__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<Q7_1__S_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q7_1__S_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n1_tbl.buckets[answer.to<Q7_1__N1_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__n1_tbl.buckets[answer.to<Q7_1__N1_Key>()].totalWeight});
        #endif
        j__n1_ = new_indices[0];
    }

    inline void find_answer__N1_(Q7_1Answer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__n1_tbl.buckets[answer.to<Q7_1__N1_Key>()];
        #else
        const auto& bucket = split__n1_tbl.buckets[answer.to<Q7_1__N1_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q7_1__N1_Parcel> r = bucket.data[ind];
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
    inline bool find_index__O_(const Q7_1Answer& answer, ll j__l_, ll j__c_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__o_tbl.buckets[answer.to<Q7_1__O_Key>()];
        #else
        const auto& bucket = split__o_tbl.buckets[answer.to<Q7_1__O_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__O_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__O_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__l_, j__c_}, {split__l_tbl.buckets[answer.to<Q7_1__L_Key>()].totalWeight,
                                                                        split__c_tbl.buckets[answer.to<Q7_1__C_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__l_, j__c_}, {split__l_tbl.buckets[answer.to<Q7_1__L_Key>()].totalWeight,
                                                                        split__c_tbl.buckets[answer.to<Q7_1__C_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__C_(const Q7_1Answer& answer, ll j__n2_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__c_tbl.buckets[answer.to<Q7_1__C_Key>()];
        #else
        const auto& bucket = split__c_tbl.buckets[answer.to<Q7_1__C_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__C_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__C_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__n2_}, {split__n2_tbl.buckets[answer.to<Q7_1__N2_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__n2_}, {split__n2_tbl.buckets[answer.to<Q7_1__N2_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__L_(const Q7_1Answer& answer, ll j__s_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__l_tbl.buckets[answer.to<Q7_1__L_Key>()];
        #else
        const auto& bucket = split__l_tbl.buckets[answer.to<Q7_1__L_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__L_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__L_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__s_}, {split__s_tbl.buckets[answer.to<Q7_1__S_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__s_}, {split__s_tbl.buckets[answer.to<Q7_1__S_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__N2_(const Q7_1Answer& answer, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__n2_tbl.buckets[answer.to<Q7_1__N2_Key>()];
        #else
        const auto& bucket = split__n2_tbl.buckets[answer.to<Q7_1__N2_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__N2_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__N2_Parcel>());
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

    inline bool find_index__S_(const Q7_1Answer& answer, ll j__n1_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__s_tbl.buckets[answer.to<Q7_1__S_Key>()];
        #else
        const auto& bucket = split__s_tbl.buckets[answer.to<Q7_1__S_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__S_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__S_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__n1_}, {split__n1_tbl.buckets[answer.to<Q7_1__N1_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__n1_}, {split__n1_tbl.buckets[answer.to<Q7_1__N1_Key>()].totalWeight});
        #endif
        return true;
    }

    inline bool find_index__N1_(const Q7_1Answer& answer, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__n1_tbl.buckets[answer.to<Q7_1__N1_Key>()];
        #else
        const auto& bucket = split__n1_tbl.buckets[answer.to<Q7_1__N1_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__N1_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q7_1__N1_Parcel>());
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

typedef Q7_1RandomAccessIndex Q7_1Index;

//------------------------------------------------------------------------------

#endif //RANDOMORDERENUMERATION_Q7_1INDEX_H