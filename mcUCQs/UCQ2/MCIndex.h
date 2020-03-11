//
// Created by shai.zeevi on 04/12/2019.
//

#ifndef TEMPLATEDRANDOMORDERENUMERATION_MCINDEX_H
#define TEMPLATEDRANDOMORDERENUMERATION_MCINDEX_H

#include <vector>
#include "MC_CQWrapper.h"

#define CQ MC_CQBase<Answer>*
#define MCUCQ MCIndexBase<Answer>*

#include "../../CQs/RandomOrderAuxCode/FisherYatesShuffler.h"

template<typename Answer>
struct MCIndexBase {

    //virtual MCIndexBase* build(CQ cq, MCIndexBase* ucq, vector<CQ> Ts) = 0;

    virtual double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) = 0;

    virtual Answer access(ll j) = 0;

    virtual bool test(Answer a) = 0;

    virtual ll cardinality() = 0;
};

template<typename Answer>
struct EmptyMCIndex : MCIndexBase<Answer> {

    inline double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) override {
        cout << "MCUCQ preprocessing" << endl;
        cout << "\t[EMPTY MCUCQ preprocessing]" << endl;
        return 0.0;
    }

    inline Answer access(ll j) override {
        throw runtime_error("cannot access empty mcUCQ");
    }

    inline bool test(Answer a) override {
        return false;
    }

    inline ll cardinality() override {
        return 0;
    }
};


template<typename Answer>
struct MCIndexOfTwo : MCIndexBase<Answer> {

public:
    MCIndexOfTwo() = default;

    MCIndexOfTwo(CQ _A, CQ _B, CQ _A_and_B) {
        build(_A,_B,_A_and_B);
    }

    MCIndexOfTwo* build(CQ _A, CQ _B, CQ _A_and_B) {
        A = _A;
        B = _B;
        A_and_B = _A_and_B;
        return this;
    }

    //we assume that nothing is preprocessed
    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) override {
        cout << "<A>" << endl;
        double build_in_millis = A->preprocessing(filenames, numlines);
        cout << "</A>" << endl;

        cout << "<B>" << endl;
        build_in_millis += B->preprocessing(filenames, numlines);
        cout << "</B>" << endl;

        cout << "<A and B>" << endl;
        build_in_millis += A_and_B->preprocessing(filenames, numlines);
        cout << "</A and B>" << endl;

        card = A->cardinality() + B->cardinality() - A_and_B->cardinality();
        return build_in_millis;
    };

    //we assume that 0 <= j < total_number_of_answers
    inline Answer access(ll j) override {
        if (j >= A->cardinality()) {
            return B->access(j - A->cardinality() + A_and_B->cardinality());
        } else {
            Answer a = A->access(j);
            return (B->test(a) ? B->access(computeK(a,j)) : a);
        }
    };

    inline bool test(Answer a) override {
        return A->test(a) || B->test(a);
    };

    ll cardinality() override {
        return card;
    }

private:
    CQ A = nullptr;
    CQ B = nullptr;
    CQ A_and_B = nullptr;
    ll card = 0;

    ll computeK(Answer a, ll j) { //j is a's index in A
        return A_and_B->inv_acc(a);
    }
};


template<typename Answer>
struct MCIndex : MCIndexBase<Answer> {

public:
    MCIndex() = default;

    MCIndex(CQ _cq, MCUCQ _ucq, const vector<CQ>& _Ts, const vector<int>& _T_sizes) {
        build(_cq, _ucq, _Ts, _T_sizes);
    }

    MCIndex* build(CQ _cq, MCUCQ _ucq, const vector<CQ>& _Ts, const vector<int>& _T_sizes) {
        cq = _cq;
        ucq = _ucq;
        Ts = _Ts;
        T_sizes = _T_sizes;
        __T_signs.reserve(Ts.size());
        __T_limits.reserve(Ts.size());
        return this;
    }

    //we assume that nothing is preprocessed
    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) override {
        cout << "<CQ>" << endl;
        double build_in_millis = cq->preprocessing(filenames, numlines);
        cout << "</CQ>" << endl;

        cout << "<UCQ>" << endl;
        build_in_millis += ucq->preprocessing(filenames, numlines);
        cout << "</UCQ>" << endl;

        for(int i = 0; i < Ts.size(); i++){
            cout << "<T>" << endl;
            auto T = Ts[i];
            build_in_millis += T->preprocessing(filenames, numlines);
            __T_signs[i] = (((T_sizes[i] + 1) % 2 == 0) ? 1 : -1);
            if(T->cardinality()) {
                __T_limits[i] = {cq->inv_acc(T->access(0)) /*j_c*/, cq->inv_acc(T->access(T->cardinality() - 1)) /*j_d*/};
            }
            cout << "</T>" << endl;
        }

        //constants
//        cout << "<constants>" << endl;
        cq_inter_ucq_card = calc_cq_inter_ucq_card(); //calc |A & B|
        card = cq->cardinality() + ucq->cardinality() - cq_inter_ucq_card;
//        cout << "|A & B| = " << cq_inter_ucq_card << endl;
//        cout << "</constants>" << endl;
        return build_in_millis;
    };

    //we assume that 0 <= j < total_number_of_answers
    inline Answer access(ll j) override {
        if (j >= cq->cardinality()) {
            return ucq->access(j - cq->cardinality() + cq_inter_ucq_card);
        } else {
            Answer a = cq->access(j);
            return (ucq->test(a) ? ucq->access(computeK(a,j)) : a);
        }
    };

    inline bool test(Answer a) override {
        return cq->test(a) || ucq->test(a);
    };

    ll cardinality() override {
        return card;
    }

private:
    CQ cq = nullptr;
    MCUCQ ucq = nullptr;
    vector<CQ> Ts;
    vector<int> T_sizes;
    ll card = 0;
    ll cq_inter_ucq_card = 0;

    //to make the binsearch more efficient
    vector<int> __T_signs;
    //to make to calculation of k more efficient
    vector<pair<ll,ll>> __T_limits;

    ll calc_cq_inter_ucq_card() {
        ll sz = 0;
        for(int i = 0; i < Ts.size(); i++){
            sz += __T_signs[i] * Ts[i]->cardinality();
        }
        return sz;
    }

    ll computeK(Answer a, ll j) { //j is a's index in cq
        ll k = 0;
        for(int i = 0; i < Ts.size(); i++){
            //Answer b = largest(Ts[i], a);
            //k += (((T_sizes[i] + 1) % 2 == 0) ? 1 : -1) * Ts[i]->inv_acc(b);
            k += __T_signs[i] * (index_of_largest(i, a, j));
        }
        return k;
        //return k - 1 /*-1 bc we count from 0*/;
    }

    /**
     * @param T - a partial CQ to this->cq where we wish to find n_T
     * @param a - an answer of this->cq
     * @param j - a's index in this->cq
     * @return - n_T = |{a_1,...,a_j} \intersect T|
     */
    ll index_of_largest(int idx, Answer a, ll j) { //returns the index of our largest *in T*
        CQ T = Ts[idx];

        if(__T_limits[idx].first > j) return 0;
        if(__T_limits[idx].second <= j) return T->cardinality();
        //if(__T_limits[idx].first == j) return 1; //possible removable

        ll k_c = 0;
        ll k_d = T->cardinality() - 1;
        while(k_c <= k_d) {
            ll k_tag = (k_c + k_d) / 2; //"mid" of a binary search
            ll j_tag = cq->inv_acc(T->access(k_tag));
            if(j_tag == j) {
                return k_tag + 1;
            }
            else if(j_tag < j) {
                k_c = k_tag + 1;
            } else /*j_tag > j*/ {
                k_d = k_tag - 1;
            }
        }
        return k_d + 1;
//        throw runtime_error("index_of_largest() failed");
    }

    /*Answer largest(CQ T, Answer a) { //maybe return ptr?
        ll j = cq->inv_acc(a);
        Answer c = T->access(0);
        ll j_c = cq->inv_acc(c);

        if(j_c == j) return c;
        if(j_c > j) throw runtime_error("no larger exists");

        ll k_c = 0;
        ll k_d = T->cardinality() - 1;
        Answer d = T->access(k_d);
        ll j_d = cq->inv_acc(d);

        if(j_d <= j) return d;

        while(k_c <= k_d) {
            ll k_tag = (k_c + k_d) / 2; //"mid" of a binary search
            Answer c_tag = T->access(k_tag); //k_tag's answer
            ll j_tag = cq->inv_acc(c_tag);
            if(j_tag == j) return c_tag;
            else if(j_tag < j) {
                //c = c_tag;
                //j_c = j_tag;
                k_c = k_tag; //+1;
            } else { //j_tag > j
                //d = c_tag;
                //j_d = j_tag;
                k_d = k_tag; //-1/;
            }
        }
        throw runtime_error("largest() failed");
    }*/
};

template<typename Answer>
struct MCRandomOrderEnum {
public:

    explicit MCRandomOrderEnum(MCIndexBase<Answer>* mcidx) : fyShuffler(), mcIndex(mcidx) {};

    inline double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) {
        mcIndex->preprocessing(filenames, numlines);
        fyShuffler.build(mcIndex->cardinality());
    }

    //in case we want to enumerate from an already built and preprocessed mcIndex
    //we just re-init our shuffler
    inline void build() {
        fyShuffler.build(mcIndex->cardinality());
    }

    inline Answer next() {
        return mcIndex->access(fyShuffler.next());
    }

    inline bool done() {
        return fyShuffler.done();
    }

    inline void resetShuffler() {
        fyShuffler.build(mcIndex->cardinality()); //rebuild shuffler;
    }

private:
    FisherYatesShuffler fyShuffler;
    MCIndexBase<Answer>* mcIndex;
};


#endif //TEMPLATEDRANDOMORDERENUMERATION_MCINDEX_H
