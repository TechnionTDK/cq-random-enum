//
// Created by shai.zeevi on 13/07/2019.
//

#ifndef TEMPLATEDRANDOMORDERENUMERATION_UCQRANDOMORDERENUMERATION_H
#define TEMPLATEDRANDOMORDERENUMERATION_UCQRANDOMORDERENUMERATION_H

#include "../CQs/RandomOrderAuxCode/RandomOrderEnumeration.h"
#include "../UCQs/UCQFisherYatesShuffler.h"

#define ENUMERATOR ROE_Base<Answer>*

using namespace std;

typedef pair<double, double> pdd;

template<typename Answer>
struct UCQEnumerator {
    vector<ENUMERATOR> QEnumerators;
    ll nGammaTaken = 0;

#if defined(TIMER)
    pdd lap() {
        pdd results = { answerMsecs, rejectionMsecs };
        answerMsecs = 0.0;
        rejectionMsecs = 0.0;
        return results;
    }
#endif

    inline bool empty() {
        return (sumNs == 0);
    }

    inline bool notEmpty() {
        return !empty();
    }

    void PrintCardinalityHistogram() const
	{
		cout << "Ns: [";
		for(int i = 0; i < Ns.size(); i++)
		{
			cout << (i > 0 ? ", " : "") << Ns[i];
		}
		cout << "]" << endl;
    }

    explicit UCQEnumerator(const vector<ENUMERATOR> &QEnumerators, ll gamma) : QEnumerators(QEnumerators), gamma(gamma),
            Ns(QEnumerators.size(), 0), sumNs(0) {};

    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) {
        // preprocessing involves preprocessing of each of the single enumerators
        double build_in_millis = 0;
        for (ENUMERATOR cqEnumerator : QEnumerators) {
            build_in_millis += cqEnumerator->preprocessing(filenames, numlines);
        }

        //initialize the weight array
        sumNs = 0;
        for (int i = 0; i < Ns.size(); i++) {
            Ns[i] = QEnumerators[i]->getNumAnswers();
            sumNs += Ns[i];
        }

        return build_in_millis;
    }

    Answer nextAnswer() {
#if defined(TIMER)
        auto t_start = chrono::steady_clock::now();
#endif
        while (notEmpty()) {
            int origin = chooseCQ();
            ll posInOrigin = -1;

            Answer ans(QEnumerators[origin]->nextAnswer(&posInOrigin));

            vector<pair<int,ll>> pVec(providersVec(ans, origin, posInOrigin));

            int owner = chooseOwnerArbitrarily(pVec);

            if(gap >= gamma)
            {
                nGammaTaken++;
                owner = origin; // manually make origin the owner if gamma was reached
            }

            for(const pair<int, ll>& p : pVec) {
                if(p.first == owner) continue;
                QEnumerators[p.first]->disqualifyAnswer(p.second);
                Ns[p.first]--;
                //sumNs--;
            }
            sumNs -= pVec.size() - 1;

            if (owner == origin) { //if origin is also the owner, an output occurs
                Ns[origin]--; //since if owner == origin we haven't decreased origin's stats
                sumNs--;
                gap = 0;

#if defined(TIMER)
                answerMsecs += chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - t_start).count() / 1000.0;
#endif
                return ans;
            }
#if defined(TIMER)
            else { //answer deferred
                rejectionMsecs += chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - t_start).count() / 1000.0;
            }
#endif

            gap++;
        }
        throw runtime_error("[DONE]: Enumeration success.");
    }

    void reset() {
        for(ENUMERATOR e : QEnumerators) {
            e->resetShuffler();
        }

        //re-initialize the weight array
        sumNs = 0;
        for (int i = 0; i < Ns.size(); i++) {
            Ns[i] = QEnumerators[i]->getNumAnswers();
            sumNs += Ns[i];
        }
    }

private:
    vector<ll> Ns; //the number of answers remaining from each query
    ll sumNs;
    default_random_engine generator = default_random_engine(system_clock::now().time_since_epoch().count());
    ll gap = 0;
    ll gamma = -1;

#if defined(TIMER)
    double answerMsecs = 0, rejectionMsecs = 0;
#endif

    int chooseCQ() {
        /*choose with prob P_i = Ns[i] / sumNs*/
        ll j = uniform_int_distribution<ll>(0, sumNs - 1)(generator);
        ll sum = 0;
        for (int q = 0; q < Ns.size(); q++) {
            if (j >= sum && j < sum + Ns[q]) {
                return q;
            }
            sum += Ns[q];
        }
        throw runtime_error("a random number was not chosen\n");
    }

    vector<pair<int, ll>> providersVec(const Answer& ans, int origin, ll posInOrigin) {
        vector<pair<int, ll>> pVec;//{make_pair(origin, posInOrigin)};

        for (int q = 0; q < QEnumerators.size(); q++) {
            if(q == origin) {
                pVec.emplace_back(q/* == origin*/,posInOrigin);
            } else {
                ENUMERATOR cqEnumerator = QEnumerators[q];
                ll j = cqEnumerator->findIndex(ans);
                if (j != ANSWER_NOT_FOUND && cqEnumerator->wasNotDisqualified(j)) {
                    pVec.emplace_back(q,j);
                }
            }
        }

        return move(pVec);
    }

    //owner is minimal providers, providers is actually sorted
    inline int chooseOwnerArbitrarily(const vector<pair<int, ll>>& providers) {
        // the way of choosing the owner does not matter, we'll choose using begin.
        return providers[0].first;
    }

    int chooseOwnerUniformly(const vector<pair<int,ll>>& providers) {
        return providers[uniform_int_distribution<int>(0, providers.size() - 1)(generator)].first;
    }

};


#endif //TEMPLATEDRANDOMORDERENUMERATION_UCQRANDOMORDERENUMERATION_H
