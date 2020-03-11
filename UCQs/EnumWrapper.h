//
// Created by shai.zeevi on 20/08/2019.
//

#include "../CQs/RandomOrderAuxCode/RandomOrderEnumeration.h"

#ifndef TEMPLATEDRANDOMORDERENUMERATION_INDEXWRAPPER_H
#define TEMPLATEDRANDOMORDERENUMERATION_INDEXWRAPPER_H

#endif //TEMPLATEDRANDOMORDERENUMERATION_INDEXWRAPPER_H


template<typename Enum, typename Ans, typename WrapperAns>
struct EnumWrapper : ROE_Base<WrapperAns> {

    Enum* enume;

    EnumWrapper() : enume(nullptr) {
        enume = new Enum();
        assert(enume != nullptr);
    }

    ~EnumWrapper() {
        delete enume;
    }


    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) override {
        return enume->preprocessing(filenames, numlines);
    };

    void resetShuffler() override {
      enume->resetShuffler();
    };

    //a random answer is selected
    WrapperAns nextAnswer() override {
        return WrapperAns(enume->nextAnswer());
    };

    //a random answer is selected and its position is returned
    WrapperAns nextAnswer(ll* pos) override {
        return WrapperAns(enume->nextAnswer(pos));
    };

    WrapperAns access(ll j) override {
        return WrapperAns(enume->access(j));
    };

#ifdef INVERSE_MAPPING
    /**
     * @param a - an Answer instance
     * @return 0 <= i < n, the index the answer if it exists and -1 otherwise
     */
    ll findIndex(const WrapperAns& a) override {
        return enume->findIndex(a.template unwrap<Ans>());
    };

    void disqualifyAnswer(ll j/*, int origin, int me*/) override {
        enume->disqualifyAnswer(j/*, origin, me*/);
    };

    bool wasDisqualified(ll base) override {
        return enume->wasDisqualified(base);
    };

    bool wasNotDisqualified(ll base) override {
        return enume->wasNotDisqualified(base);
    };
#endif

    ll getNumAnswers() override {
        return enume->getNumAnswers();
    };
};
