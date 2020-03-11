//
// Created by shai.zeevi on 05/06/2019.
//

#ifndef RANDOMORDERENUMERATION_YANNAKAKISREDUCER_H
#define RANDOMORDERENUMERATION_YANNAKAKISREDUCER_H

#include "../AbstractDatabase/Table.h"
#include <unordered_set>
#include <algorithm>

template<typename... Tables>
struct YannakakisReducer {

    void reduce(Tables&... tbls) {
        reduceBottomUp(tbls...);
        reduceTopDown(tbls...);
    }

    //you just need to arrange the calls to oneBottomUp according to the tree structure
    virtual void reduceBottomUp(Tables &... tbls) = 0;

    //you just need to arrange the calls to oneTopDown according to the tree structure
    virtual void reduceTopDown(Tables &... tbls) = 0;


    template<typename Parcel1, typename Parcel2, typename InterParcel>
    inline void oneBottomUp(Table<Parcel1>& tbl, const Table<Parcel2>& childTbl) {
        //remove from tbl everything that can't match to something in childTbl

        unordered_set<InterParcel, hash<InterParcel>, equal_to<InterParcel>> marked;
        marked.reserve(childTbl.data.size());

        for (const Row<Parcel2> &r : childTbl.data) {
            marked.insert(r.parcel.template to<InterParcel>()); //tuples with this key-portion values are marked
        }

        //now, we can delete the unmarked nodes from the table
//        auto it = remove_if(tbl.data.begin(), tbl.data.end(),
//                            [marked](const Row<Parcel1>& r) {
//                                return (marked.find(r.parcel.template to<InterParcel>()) == marked.end());
//                            });
//        tbl.data.erase(it, tbl.data.end());

        vector<Row<Parcel1>> newRows;
        for(const Row<Parcel1>& r : tbl.data) {
            const Parcel1& p = r.parcel;
            if(marked.find(p.template to<InterParcel>()) != marked.end())
                newRows.emplace_back(p, 1);
        }
        tbl.data = move(newRows);
    }

    template<typename Parcel1, typename Parcel2, typename InterParcel>
    inline void oneTopDown(Table<Parcel1>& tbl, const Table<Parcel2>& parentTbl) {
        //remove from tbl everything that can't match to something in parentTbl

        unordered_set<InterParcel, hash<InterParcel>, equal_to<InterParcel>> marked;
        marked.reserve(parentTbl.data.size());

        for (const Row<Parcel2> &r : parentTbl.data) {
            marked.insert(r.parcel.template to<InterParcel>()); //tuples with this key-portion values are marked
        }

        //now, we can delete the unmarked nodes from this child
//        auto it = remove_if(tbl.data.begin(), tbl.data.end(),
//                            [marked](const Row<Parcel1>& r) {
//                                return (marked.find(r.parcel.template to<InterParcel>()) == marked.end());
//                            });
//        tbl.data.erase(it, tbl.data.end());

        vector<Row<Parcel1>> newRows;
        for(const Row<Parcel1>& r : tbl.data) {
            const Parcel1& p = r.parcel;
            if(marked.find(p.template to<InterParcel>()) != marked.end())
                newRows.emplace_back(p, 1);
        }
        tbl.data = move(newRows);
    }

};


#endif //RANDOMORDERENUMERATION_YANNAKAKISREDUCER_H
