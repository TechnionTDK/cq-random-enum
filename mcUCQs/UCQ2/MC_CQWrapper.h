//
// Created by shai.zeevi on 04/12/2019.
//

#ifndef TEMPLATEDRANDOMORDERENUMERATION_MC_CQWRAPPER_H
#define TEMPLATEDRANDOMORDERENUMERATION_MC_CQWRAPPER_H

#include <unordered_map>
#include <assert.h>

typedef long long ll;

using namespace std;

template<typename Ans>
struct MC_CQBase {
    virtual double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) = 0;

    virtual ll cardinality() = 0;

    virtual Ans access(ll j) = 0;

    //our intention is that inv-acc will only be used when the answer belongs to the query
    virtual ll inv_acc(Ans ans) = 0;

    virtual bool test(Ans ans) = 0;
};

//intended to be used with our generated RAIndex + Answer types
template<typename CQ_Index, typename Ans, typename WrapperAns>
struct MC_CQWrapper : MC_CQBase<WrapperAns> {

    CQ_Index* cq;

    MC_CQWrapper() : cq(nullptr) {
        cq = new CQ_Index();
        assert(cq != nullptr);
    }

    ~MC_CQWrapper() {
        delete cq;
    }

    inline double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) override {
        return cq->preprocessing(filenames, numlines);
    };

    inline ll cardinality() override {
        return cq->numAnswers;
    }

    inline WrapperAns access(ll j) override {
        return WrapperAns(cq->access(j));
    }

    //our intention is that inv-acc will only be used when the answer belongs to the query
    inline ll inv_acc(WrapperAns ans) override {
        ll j = cq->index(ans.template unwrap<Ans>());
        assert(j != -1);
        return j;
    }

    inline bool test(WrapperAns ans) override {
        return (cq->index(ans.template unwrap<Ans>()) != -1);
    }
};

#endif //TEMPLATEDRANDOMORDERENUMERATION_MC_CQWRAPPER_H
