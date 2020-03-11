//
// Created by shai.zeevi on 10/06/2019.
//

#ifndef TEMPLATEDRANDOMORDERENUMERATION_RANDOMORDERENUMERATION_H
#define TEMPLATEDRANDOMORDERENUMERATION_RANDOMORDERENUMERATION_H


#include <iostream>
#include <assert.h>
#include "FisherYatesShuffler.h"

typedef long long ll;

#define ANSWER_NOT_FOUND -1

//In a union, all queries need to have the same answer prototype
//that is mostly compulsory due to typing issues
template<typename Answer>
struct ROE_Base {
    virtual double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) = 0;

    virtual void resetShuffler() = 0;

    //a random answer is selected
    virtual Answer nextAnswer() = 0;

    //a random answer is selected, and its position is returned
    virtual Answer nextAnswer(ll* pos) = 0;

    virtual Answer access(ll j) = 0;

#if defined(INVERSE_MAPPING) || defined(INVERTED_ACCESS)
    /**
     * @param a - an Answer instance
     * @return 0 <= i < n, the index the answer if it exists and -1 otherwise
     */
    virtual ll findIndex(const Answer& a) = 0;
#endif

#ifdef INVERSE_MAPPING
    virtual void disqualifyAnswer(ll j/*, int origin, int me*/) = 0;

    virtual bool wasDisqualified(ll base) = 0;

    virtual bool wasNotDisqualified(ll base) = 0;
#endif

    virtual ll getNumAnswers() = 0;

//    virtual void checkShufflerStatus() = 0;
};

template<typename RAIndex, typename Shuffler, typename Answer>
struct RandomOrderEnumeration : ROE_Base<Answer> {
    RAIndex* index;
    Shuffler shuffler;

    RandomOrderEnumeration() :
            index(new RAIndex()), shuffler(Shuffler()) {};

    ~RandomOrderEnumeration() {
        delete index;
    }

    inline double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) override {
        double build_time = index->preprocessing(filenames, numlines);
        shuffler.build(index->numAnswers);
        return build_time;
    }

    inline void resetShuffler() override {
        shuffler.build(index->numAnswers); //rebuild shuffler
    }

    //a random answer is selected
    inline Answer nextAnswer() override {
        ll j = shuffler.next();
        return index->access(j);
    }

    inline Answer nextAnswer(ll* pos) override {
        *pos = shuffler.next();
        return index->access(*pos);
    }


    inline Answer access(ll j) override {
        return index->access(j);
    }

#if defined(INVERSE_MAPPING) || defined(INVERTED_ACCESS)
    inline ll findIndex(const Answer& a) override {
        //ll base = index->index(a);
        //if(base == ANSWER_NOT_FOUND) return ANSWER_NOT_FOUND;
        //if(!shuffler.fresh(base)) return ANSWER_NOT_FRESH;
        return index->index(a); //base;

    }

#endif

    #ifdef INVERSE_MAPPING
    inline void disqualifyAnswer(ll j/*, int origin, int me*/) override {
        shuffler.disqualify(j/*, origin, me*/);
    }

    inline bool wasDisqualified(ll base) override {
        return shuffler.wasDisqualified(base);
    }

    inline bool wasNotDisqualified(ll base) override {
        return !shuffler.wasDisqualified(base);
    }
    #endif

    inline ll getNumAnswers() override {
        return index->numAnswers;
    }

//    void checkShufflerStatus() override {
//        shuffler.checkStatus();
//    }
};


#endif //TEMPLATEDRANDOMORDERENUMERATION_RANDOMORDERENUMERATION_H
