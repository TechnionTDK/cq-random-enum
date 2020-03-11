#ifndef RANDOMORDERENUMERATION_Q3INDEX_H
#define RANDOMORDERENUMERATION_Q3INDEX_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "../../TemplatedRandomAccess/YannakakisReducer.h"
#include "../../TemplatedRandomAccess/AbstractWeightCalculator.h"
#include "Q3__C_Parcel.h"
#include "Q3__L_Parcel.h"
#include "Q3__O_Parcel.h"
#include "Q3Answer.h"
#include "../../RandomAccessAuxCode/IndexUtils.h"

typedef long long ll;

using namespace std;

//------------------------------------ Yannakakis Reducer ------------------------------------------
//specifies reduction order
struct Q3YannakakisReducer : YannakakisReducer<Q3__C_Table, Q3__L_Table, Q3__O_Table> {
    //you just need to arrange the calls to oneBottomUp according to the tree structure
    void reduceBottomUp(Q3__C_Table& _c__tbl, Q3__L_Table& _l__tbl, Q3__O_Table& _o__tbl) override {
        oneBottomUp<Q3__O_Parcel, Q3__C_Parcel, Q3__C_Key>(_o__tbl, _c__tbl);
        oneBottomUp<Q3__O_Parcel, Q3__L_Parcel, Q3__L_Key>(_o__tbl, _l__tbl);
    }

    //you just need to arrange the calls to oneTopDown according to the tree structure
    void reduceTopDown(Q3__C_Table& _c__tbl, Q3__L_Table& _l__tbl, Q3__O_Table& _o__tbl) override {
        oneTopDown<Q3__L_Parcel, Q3__O_Parcel, Q3__L_Key>(_l__tbl, _o__tbl);
        oneTopDown<Q3__C_Parcel, Q3__O_Parcel, Q3__C_Key>(_c__tbl, _o__tbl);
    }
};
//------------------------------------------------------------------------------

//------------------------------------ Table Weighter ------------------------------------------
#ifdef PROJECTION
struct Q3__C_Weighter : AbstractSingleTableWeighter<Q3__C_Key, Q3__C_Parcel> {//leaf
    inline void weightTable(Q3__C_SplitTable& split__c_tbl) override {}
};
#else
struct Q3__C_Weighter : AbstractSingleTableWeighter<Q3__C_Key, Q3__C_Parcel> {//leaf
    inline void weightTable(Q3__C_SplitTable& split__c_tbl) override {}
};
#endif


#ifdef PROJECTION
struct Q3__L_Weighter : AbstractSingleTableWeighter<Q3__L_Key, Q3__L_Parcel> {//leaf
    inline void weightTable(Q3__L_SplitTable& split__l_tbl) override {}
};
#else
struct Q3__L_Weighter : AbstractSingleTableWeighter<Q3__L_Key, Q3__L_Parcel> {//leaf
    inline void weightTable(Q3__L_SplitTable& split__l_tbl) override {}
};
#endif


#ifdef PROJECTION
struct Q3__O_Weighter : AbstractSingleTableWeighter<Q3__O_Key, Q3__O_Parcel, Q3__L_SplitTable, Q3__C_SplitTable> {//internal node
    inline void weightTable(Q3__O_SplitTable& split__o_tbl, const Q3__L_SplitTable& split__l_tbl, const Q3__C_SplitTable& split__c_tbl) override {
        weightingStep(split__o_tbl, split__l_tbl);
        weightingStep(split__o_tbl, split__c_tbl);
    }
};
#else
struct Q3__O_Weighter : AbstractSingleTableWeighter<Q3__O_Key, Q3__O_Parcel, Q3__L_SplitTable, Q3__C_SplitTable> {//internal node
    inline void weightTable(Q3__O_SplitTable& split__o_tbl, const Q3__L_SplitTable& split__l_tbl, const Q3__C_SplitTable& split__c_tbl) override {
        weightingStep(split__o_tbl, split__l_tbl);
        weightingStep(split__o_tbl, split__c_tbl);
    }
};
#endif


#ifndef PROJECTION
struct Q3Weighter : QueryWeighter<Q3__C_SplitTable, Q3__L_SplitTable, Q3__O_SplitTable> {
    inline void weight(Q3__C_SplitTable& split__c_tbl, Q3__L_SplitTable& split__l_tbl, Q3__O_SplitTable& split__o_tbl) override {
        Q3__C_Weighter().weight(split__c_tbl);

        Q3__L_Weighter().weight(split__l_tbl);

        Q3__O_Weighter().weight(split__o_tbl, split__l_tbl, split__c_tbl);
    }
};
#else
struct Q3Weighter : QueryWeighter<Q3__C_SplitTable, Q3__L_SplitTable, Q3__O_SplitTable> {
    inline void weight(Q3__C_SplitTable& split__c_tbl, Q3__L_SplitTable& split__l_tbl, Q3__O_SplitTable& split__o_tbl) override {
        Q3__C_Weighter().weight(split__c_tbl);

        Q3__L_Weighter().weight(split__l_tbl);

        Q3__O_Weighter().weight(split__o_tbl, split__l_tbl, split__c_tbl);
    }
};
#endif
//------------------------------------------------------------------------------

//------------------------------------ RandomAccessIndex ------------------------------------------
struct Q3RandomAccessIndex {

    //Fields tables;
    #ifdef PROJECTION
    Q3__C_SplitTable split__c_tbl;
    Q3__L_SplitTable split__l_tbl;
    Q3__O_SplitTable split__o_tbl;
    #else
    Q3__C_SplitTable split__c_tbl;
    Q3__L_SplitTable split__l_tbl;
    Q3__O_SplitTable split__o_tbl;

    #endif
    ll numAnswers;
    
    
    //preprocessing
    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numLines) {
        //------------------------------------------------------- PREPROCESSING START!
        auto t1 = chrono::steady_clock::now();
        
        Q3__C_Table _c_tbl;
        Q3__L_Table _l_tbl;
        Q3__O_Table _o_tbl;

        _c_tbl.loadFromFile(filenames.at("_C_"), numLines.at("_C_"));
        _l_tbl.loadFromFile(filenames.at("_L_"), numLines.at("_L_"));
        _o_tbl.loadFromFile(filenames.at("_O_"), numLines.at("_O_"));
        
        auto t2 = chrono::steady_clock::now();
        
        Q3YannakakisReducer().reduce(_c_tbl, _l_tbl, _o_tbl);

        #ifdef PROJECTION
        split__c_tbl.loadFromTable(_c_tbl);
        split__l_tbl.loadFromTable(_l_tbl);
        split__o_tbl.loadFromTable(_o_tbl);
        #else
        split__c_tbl.loadFromTable(_c_tbl);
        split__l_tbl.loadFromTable(_l_tbl);
        split__o_tbl.loadFromTable(_o_tbl);
        #endif

        Q3Weighter().weight(split__c_tbl, split__l_tbl, split__o_tbl);
        
        numAnswers = split__o_tbl.getCummulativeWeight();
        
        auto t3 = chrono::steady_clock::now();
        //cout << "reading time is " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1000.0 << " milliseconds" << endl;
        //cout << "building time is " << chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0 << " milliseconds" << endl;
        //------------------------------------------------------- PREPROCESSING DONE!

        return chrono::duration_cast<chrono::microseconds>(t3 - t2).count() / 1000.0;
    }
    
    Q3Answer access(ll j) {
        //if(j < 0 || j > numAnswers) {
        //    cout << "tried to access answer no." << j << ", n = " << numAnswers << endl;
        //    throw runtime_error("index beyond range " + to_string(j));
        //}
        
        ll j__c_, j__l_;
        Q3Answer ans;
        find_answer__O_(ans, j, j__l_, j__c_);
        find_answer__L_(ans, j__l_);
        find_answer__C_(ans, j__c_);
        return move(ans);
    }
    
    #ifdef INVERSE_MAPPING
    ll index(const Q3Answer& ans) {
        ll j__c_, j__l_, j__o_;
        if(!find_index__C_(ans, j__c_)) {
            return -1;
        }

        if(!find_index__L_(ans, j__l_)) {
            return -1;
        }

        if(!find_index__O_(ans, j__l_, j__c_, j__o_)) {
            return -1;
        }

        return j__o_;
    }
    #endif
    
    
private:
    inline void find_answer__C_(Q3Answer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__c_tbl.buckets[answer.to<Q3__C_Key>()];
        #else
        const auto& bucket = split__c_tbl.buckets[answer.to<Q3__C_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q3__C_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #else
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #endif
        
    }

    inline void find_answer__L_(Q3Answer& answer, ll j/*, int& position*/) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__l_tbl.buckets[answer.to<Q3__L_Key>()];
        #else
        const auto& bucket = split__l_tbl.buckets[answer.to<Q3__L_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q3__L_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #else
        //vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {});
        #endif
        
    }

    inline void find_answer__O_(Q3Answer& answer, ll j/*, int& position*/, ll& j__l_, ll& j__c_) {
        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__o_tbl.buckets[answer.to<Q3__O_Key>()];
        #else
        const auto& bucket = split__o_tbl.buckets[answer.to<Q3__O_Key>()];
        #endif

        //step 2 - find tuple & update the answer
        int ind = getTupleIndex(bucket.weightPrefixSum, j);
        //Row<Q3__O_Parcel> r = bucket.data[ind];
        answer.set(bucket.data[ind].parcel);

        //step 3 - find position & indices for children
        ll j_tag = (j - bucket.weightPrefixSum[ind]); // relative inside the group
        #ifndef PROJECTION
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__l_tbl.buckets[answer.to<Q3__L_Key>()].totalWeight,
                                                                        split__c_tbl.buckets[answer.to<Q3__C_Key>()].totalWeight});
        #else
        vector<ll> new_indices = IndexUtils::split(j_tag/* / r.card*/, {split__l_tbl.buckets[answer.to<Q3__L_Key>()].totalWeight,
                                                                        split__c_tbl.buckets[answer.to<Q3__C_Key>()].totalWeight});
        #endif
        j__l_ = new_indices[0];
        j__c_ = new_indices[1];
    }
    
    #ifdef INVERSE_MAPPING
    inline bool find_index__C_(const Q3Answer& answer, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__c_tbl.buckets[answer.to<Q3__C_Key>()];
        #else
        const auto& bucket = split__c_tbl.buckets[answer.to<Q3__C_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q3__C_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q3__C_Parcel>());
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

    inline bool find_index__L_(const Q3Answer& answer, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__l_tbl.buckets[answer.to<Q3__L_Key>()];
        #else
        const auto& bucket = split__l_tbl.buckets[answer.to<Q3__L_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q3__L_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q3__L_Parcel>());
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

    inline bool find_index__O_(const Q3Answer& answer, ll j__l_, ll j__c_, ll& j) {
        //step 0 - check if we have a bucket at all

        //step 1 - find the appropriate bucket
        #ifndef PROJECTION
        const auto& bucket = split__o_tbl.buckets[answer.to<Q3__O_Key>()];
        #else
        const auto& bucket = split__o_tbl.buckets[answer.to<Q3__O_Key>()];
        #endif

        //step 2 - find tuple & its offset
        #ifndef PROJECTION
        auto it = bucket.weightOffsetMap.find(answer.to<Q3__O_Parcel>());
        #else
        auto it = bucket.weightOffsetMap.find(answer.to<Q3__O_Parcel>());
        #endif
        if(it == bucket.weightOffsetMap.end()) return false; //testing failed, this is not an answer
        
        //step 3 - find position & indices for children
        #ifndef PROJECTION
        j = it->second /*offset*/ + IndexUtils::combine({j__l_, j__c_}, {split__l_tbl.buckets[answer.to<Q3__L_Key>()].totalWeight,
                                                                        split__c_tbl.buckets[answer.to<Q3__C_Key>()].totalWeight});
        #else
        j = it->second /*offset*/ + IndexUtils::combine({j__l_, j__c_}, {split__l_tbl.buckets[answer.to<Q3__L_Key>()].totalWeight,
                                                                        split__c_tbl.buckets[answer.to<Q3__C_Key>()].totalWeight});
        #endif
        return true;
    }
    #endif
    
    static inline int getTupleIndex(const vector<ll>& prefixSum, ll j) {
        return (upper_bound(prefixSum.begin(), prefixSum.end(), j) - prefixSum.begin() - 1);
    }
};

typedef Q3RandomAccessIndex Q3Index;

//------------------------------------------------------------------------------

#endif //RANDOMORDERENUMERATION_Q3INDEX_H