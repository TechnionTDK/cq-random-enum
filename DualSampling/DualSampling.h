//
// Created by shai on 11/14/2020.
//

#ifndef CODE_DUALSAMPLING_H
#define CODE_DUALSAMPLING_H

#include "../CQs/RandomOrderAuxCode/RandomOrderEnumeration.h"
#include "../UCQs/UCQFisherYatesShuffler.h"

#define ENUMERATOR ROE_Base<Answer>*

#define CHOICE_UNINIT 0
#define CHOICE_HEAD 1
#define CHOICE_TAIL 2

template<typename Answer>
struct DualSamplingBase {

    virtual double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) = 0;

    virtual Answer sample() = 0;

    virtual bool test(Answer a) = 0;

    virtual ll count() = 0;

    virtual void disqualify(Answer a) = 0;

    virtual void putBack(const Answer& a) = 0;

    virtual Answer peek() = 0;

    virtual void commit(const Answer& a) = 0;

    virtual void PrintCardinalityHistogram() = 0;

    virtual void reset() = 0;
};


template<typename Answer>
struct UnitaryDualSampling : public DualSamplingBase<Answer> {

    UnitaryDualSampling(ENUMERATOR pCQ) {
        this->cq = pCQ;
    }

    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) override {
        double build_time = cq->preprocessing(filenames, numlines);
        nAnswers = cq->getNumAnswers();
        return build_time;
    };

    Answer sample() override {
        nAnswers--;
        return cq->nextAnswer();
    }

    bool test(Answer a) override {
        return (-1 != cq->findIndex(a));
    }

    ll count() override {
        return nAnswers;
    }

    void disqualify(Answer a) override {
        assert(test(a));
        cq->disqualifyAnswer(a);
        nAnswers--;
    }

    void putBack(const Answer& a) override {
        assert(test(a));

        cq->putBack(a);
        nAnswers++;
    }

    Answer peek() override
    {
        return cq->peek();
    }

    void commit(const Answer& a) override
    {
        assert(test(a));
        cq->commit(a);
        nAnswers--;
    }

    void PrintCardinalityHistogram() override
    {
        cout << nAnswers << " ";
    }

    void reset() override
    {
        cq->resetShuffler();
        nAnswers = cq->getNumAnswers();
    }

private:
    ENUMERATOR cq = nullptr;
    ll nAnswers = -1;
};


template<typename Answer>
struct DualSampling : public DualSamplingBase<Answer> {

    /**
     * @param qs - vector of the <italic>m</italic> CQs in the union
     * @param intersectionSizes - a vector of size m-1, where the i-th element is:
     *                                 |S_i & DualSampling(S_{i+1},...,S_{m-1})|
     *                            Aka the number of answers shared between the head and the tail
     */
    DualSampling(vector<ENUMERATOR> qs, vector<ll> intersectionSizes)
    {
        assert(qs.size() >= 2);

        headCQ = new UnitaryDualSampling<Answer>(qs[0]);
        intersection_size = intersectionSizes[0];
        qs.erase(qs.begin());
        intersectionSizes.erase(intersectionSizes.begin());

        if(qs.size() == 1)
        {
            // base case
            tailUCQ = new UnitaryDualSampling<Answer>(qs[0]);
        }
        else
        {
            // At least 2 CQs
            tailUCQ = new DualSampling<Answer>(qs, intersectionSizes);
        }

        _choices_ = new DualSamplingBase<Answer>*[3];
        _choices_[0] = nullptr;
        _choices_[CHOICE_HEAD] = headCQ;
        _choices_[CHOICE_TAIL] = tailUCQ;
    }

    ~DualSampling()
    {
        delete headCQ;
        delete tailUCQ;
        delete _choices_;
    }

    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) override
    {
        double build_time = 0;
        build_time += headCQ->preprocessing(filenames, numlines);
        build_time += tailUCQ->preprocessing(filenames, numlines);
        nAnswers = headCQ->count() + tailUCQ->count() - intersection_size;
        return build_time;
    }

    Answer sample() override
    {
        assert(headCQ->count() + tailUCQ->count() > 0);

        if (headCQ->count() + tailUCQ->count() == 1)
        {
            if (headCQ->count() == 1) {
                nAnswers--;
                return headCQ->sample();
            } else {
                nAnswers--;
                return tailUCQ->sample();
            }
        }

        if (headCQ->count() + tailUCQ->count() > 1)
        {
            int c1 = CHOICE_UNINIT, c2 = CHOICE_UNINIT;
            Answer a1 = chooseAnswer(&c1);
            Answer a2 = chooseAnswer(&c2);
            bool bShared1 = shared(a1);
            bool bShared2 = shared(a2);

            bool choseC1 = true;
            if (bShared1 && !bShared2)
            {
                choseC1 = chooseWithProb(asymProb()); // TRUE means C1 o.w. C2
            } else if (!bShared1 && bShared2)
            {
                choseC1 = chooseWithProb(1 - asymProb()); // TRUE means C1 o.w. C2
            }

            if(choseC1)
            {
                returnAnswer(c2, a2);

                if(bShared1)
                {
                    deleteAnswer(flipChoice(c1), a1);
                }

                nAnswers--;
                return a1;
            }
            else
            {
                returnAnswer(c1, a1);

                if(bShared2)
                {
                    deleteAnswer(flipChoice(c2), a2);
                }

                nAnswers--;
                return a2;
            }
        }
    }

    Answer peek() override
    {
        assert(headCQ->count() + tailUCQ->count() > 0);

        // Only one answer is possible, we return it
        if (headCQ->count() + tailUCQ->count() == 1)
        {
            if (headCQ->count() == 1) {
                nAnswers--;
                return headCQ->peek();
            } else {
                nAnswers--;
                return tailUCQ->peek();
            }
        }

        if (headCQ->count() + tailUCQ->count() > 1)
        {
            int c1 = CHOICE_UNINIT, c2 = CHOICE_UNINIT;
            Answer a1 = peekAnswer(c1);
            Answer a2 = peekAnswer(c2);
            bool bShared1 = shared(a1);
            bool bShared2 = shared(a2);

            bool choseC1 = true;
            if (bShared1 && !bShared2)
            {
                choseC1 = chooseWithProb(asymProb()); // TRUE means C1 o.w. C2
            } else if (!bShared1 && bShared2)
            {
                choseC1 = chooseWithProb(1 - asymProb()); // TRUE means C1 o.w. C2
            }

            if(choseC1)
            {
                return a1;
            }
            else
            {
                return a2;
            }
        }
    }

    void commit(const Answer& a) override
    {
        if(headCQ->test(a))
        {
            headCQ->commit(a);
        }

        if(tailUCQ->test(a))
        {
            tailUCQ->commit(a);
        }

        nAnswers--;
    }

    bool test(Answer a) override
    {
        return headCQ->test(a) || tailUCQ->test(a);
    }

    ll count() override
    {
        return nAnswers;
    }

    void disqualify(Answer a) override
    {
        assert(test(a));

        if(headCQ->test(a))
        {
            headCQ->disqualify(a);
        }

        if(tailUCQ->test(a))
        {
            tailUCQ->disqualify(a);
        }

        nAnswers--;
    }

    void putBack(const Answer& a) override
    {
        assert(test(a));

        if(headCQ->test(a))
        {
            headCQ->putBack(a);
        }

        if(tailUCQ->test(a))
        {
            tailUCQ->putBack(a);
        }

        nAnswers++;
    }

    void PrintCardinalityHistogram() override
    {
        cout << headCQ->count() << " ";
        tailUCQ->PrintCardinalityHistogram();
    }

    void reset() override
    {
        headCQ->reset();
        tailUCQ->reset();
        nAnswers = headCQ->count() + tailUCQ->count() - intersection_size;
    }

private:
    UnitaryDualSampling<Answer>* headCQ = nullptr;
    DualSamplingBase<Answer>* tailUCQ = nullptr;
    ll intersection_size = -1;
    ll nAnswers = -1;

    DualSamplingBase<Answer>** _choices_  = nullptr;


    int flipChoice(int choice)
    {
        switch(choice)
        {
            case CHOICE_UNINIT:
                throw runtime_error("Can't flip choice UNINIT\n");
            case CHOICE_HEAD:
                return CHOICE_TAIL;
            case CHOICE_TAIL:
                return CHOICE_HEAD;
        }
    }

	bool shared(const Answer& a)
	{
		return (headCQ->test(a) && tailUCQ->test(a));
	}

    Answer chooseAnswer(int* choice)
    {
		default_random_engine generator = default_random_engine(system_clock::now().time_since_epoch().count());
        ll j = uniform_int_distribution<ll>(1, headCQ->count() + tailUCQ->count())(generator);

        if (j <= headCQ->count()) {  // case HEAD
            *choice = CHOICE_HEAD;
            return headCQ->sample();
        } else {                     // case TAIL
            *choice = CHOICE_TAIL;
            return tailUCQ->sample();
        }
    }

    double asymProb()
    {
        return (double)(nAnswers - intersection_size) / (double)(4*nAnswers);
    }

    bool chooseWithProb(double p)
    {
        uniform_real_distribution<double> unif(0,1);
        default_random_engine re;
        double random_double = unif(re);
        return (random_double < p);
    }

    void returnAnswer(int choice, const Answer& a)
    {
	    _choices_[choice]->putBack(a);
    }

    void deleteAnswer(int choice, const Answer& a)
    {
        _choices_[choice]->disqualify(a);
    }

    Answer peekAnswer(int& choice)
    {
        default_random_engine generator = default_random_engine(system_clock::now().time_since_epoch().count());
        ll j = uniform_int_distribution<ll>(1, headCQ->count() + tailUCQ->count())(generator);

        if (j <= headCQ->count()) {  // case HEAD
            choice = CHOICE_HEAD;
            return std::move(headCQ->peek());
        } else {                     // case TAIL
            choice = CHOICE_TAIL;
            return std::move(tailUCQ->peek());
        }
    }

};

#endif //CODE_DUALSAMPLING_H
