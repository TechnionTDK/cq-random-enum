//
// Created by shai.zeevi on 05/06/2019.
//

#ifndef RANDOMORDERENUMERATION_ABSTRACTWEIGHTCALCULATOR_H
#define RANDOMORDERENUMERATION_ABSTRACTWEIGHTCALCULATOR_H

#include "../AbstractDatabase/SplitTable.h"

typedef long long ll;

template<typename KeyParcel1, typename Parcel1, typename... ChildTables>
struct AbstractSingleTableWeighter {

    void weight(SplitTable<KeyParcel1, Parcel1> &T, ChildTables const &... childTables) {
        weightTable(T, childTables...); //aggregates calls to weightingStep => all T's weights are calculated;

        //after the weighting has been done, calculate the prefix sum & offsetMapping for each bucket separately
        for (auto &p : T.buckets) {
            auto& tbl = p.second;
            tbl.weightPrefixSum = vector<long long>(tbl.data.size() + 1, 0);

            #if defined(INVERSE_MAPPING) || defined(INVERTED_ACCESS)
            tbl.weightOffsetMap.clear();
            #endif

            for (int i = 0; i < tbl.data.size(); i++) {
                #if defined(INVERSE_MAPPING) || defined(INVERTED_ACCESS)
                tbl.weightOffsetMap[tbl.data[i].parcel] = tbl.weightPrefixSum[i];
                #endif
                tbl.weightPrefixSum[i + 1] = tbl.weightPrefixSum[i] + tbl.data[i].weight;
                tbl.totalWeight += tbl.data[i].weight;
            }
        }

        //now T has calculated weights & totalWeights (for his parent to weight themselves)
        //be sure to call the singleTableWeighter in post-order
    }

    //only really needs to arrange the calls to weightingStep for each child
    virtual void weightTable(SplitTable<KeyParcel1, Parcel1> &table, ChildTables const &... childTables) = 0;

    template<typename KeyParcel2, typename Parcel2>
    inline static void weightingStep(SplitTable<KeyParcel1, Parcel1>& T1, const SplitTable<KeyParcel2, Parcel2>& T2) {
        for (auto& p : T1.buckets) {
            for (auto& row : p.second.data) {
                KeyParcel2 childKey = row.parcel.template to<KeyParcel2>();
                row.weight *= T2.buckets.at(childKey).totalWeight; //we assume child was already weighted
            }
        }
    }
};

template<typename... Tables>
struct QueryWeighter {
    //implement in derived class via specialization, implementation ONLY needs to call in postorder to singleWeighter's weight
    virtual void weight(Tables &... tables) = 0;
};


#endif //RANDOMORDERENUMERATION_ABSTRACTWEIGHTCALCULATOR_H
