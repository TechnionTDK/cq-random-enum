//
// Created by shai.zeevi on 13/07/2019.
//

#ifndef TEMPLATEDRANDOMORDERENUMERATION_UCQRANDOMORDERENUMERATION_H
#define TEMPLATEDRANDOMORDERENUMERATION_UCQRANDOMORDERENUMERATION_H

#include "../CQs/RandomOrderAuxCode/RandomOrderEnumeration.h"
#include "UCQFisherYatesShuffler.h"

#define ENUMERATOR ROE_Base<Answer>*

typedef pair<double, double> pdd;

template<typename Answer>
struct UCQEnumerator {
    vector<ENUMERATOR> QEnumerators;


    inline bool empty() {
        return (sumNs == 0);
    }

    inline bool notEmpty() {
        return !empty();
    }

    const vector<ll>& cardHist() {
        return Ns;
    }

    explicit UCQEnumerator(const vector<ENUMERATOR> &QEnumerators) : QEnumerators(QEnumerators),
            Ns(QEnumerators.size(), 0), sumNs(0) {};

    double preprocessing(const unordered_map<string, string>& filenames, const unordered_map<string, int>& numlines) {
        // preprocessing involves preprocessing of each of the single enumerators
        double build_in_millis = 0;
        int j = 0;
        for (ENUMERATOR cqEnumerator : QEnumerators) {
            build_in_millis += cqEnumerator->preprocessing(filenames, numlines);
            j++;
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
        while (notEmpty()) {

#ifdef TIME_COUNT
            auto t_start = chrono::steady_clock::now();
#endif

            int origin = chooseCQ();
            ll posInOrigin = -1;
            Answer ans(QEnumerators[origin]->nextAnswer(&posInOrigin));
            /* unordered_map<int, ll> providersMap(providers(ans, origin, posInOrigin)); //pMap[q] = j <=> QEnumerators[q][j] = ans

            //int owner = chooseOwnerArbitrarily(providersMap);
            int owner = chooseOwnerUniformly(providersMap);

            providersMap.erase(owner); // we don't need to disqualify ans from owner
            for (auto p : providersMap) {
                QEnumerators[p.first]->disqualifyAnswer(p.second);
                Ns[p.first]--;
                sumNs--;
            }*/
            vector<pair<int,ll>> pVec(providersVec(ans, origin, posInOrigin));
            /*int owner = chooseOwnerUniformly(pVec);
             * */
            int owner = chooseOwnerArbitrarily(pVec);
            /*//owner is the first one
//            for(int i = 1; i < pVec.size(); i++) {
//                pair<int, ll> p = pVec[i];
//                QEnumerators[p.first]->disqualifyAnswer(p.second);
//                Ns[p.first]--;
//                //sumNs--;
//            }
//            sumNs -= pVec.size() - 1;
            */
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
#ifdef TIME_COUNT
                msecs_for_answers += chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - t_start).count() / 1000.0;
#endif
                return ans;
            }
#ifdef TIME_COUNT
            else { //answer deferred
                msecs_for_rejections += chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - t_start).count() / 1000.0;
            }
#endif
        }
        throw runtime_error("[DONE]: Enumeration success.");
    }

    void resetShuffler() {
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

#ifdef TIME_COUNT
    void resetTimer() {
        msecs_for_answers = 0;
        msecs_for_rejections = 0;
    }

    pdd getTime() {
        return {msecs_for_answers, msecs_for_rejections};
    }
#endif

private:
    vector<ll> Ns; //the number of answers remaining from each query
    ll sumNs;
    default_random_engine generator = default_random_engine(system_clock::now().time_since_epoch().count());

#ifdef TIME_COUNT
    //------------------------------------------------
    double msecs_for_answers = 0;
    double msecs_for_rejections = 0;
    //------------------------------------------------
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

    unordered_map<int, ll> providers(const Answer& ans, int origin, ll posInOrigin) {
        unordered_map<int, ll> pMap; //each cell is (q,j) where ans is the j-th answer of QEnumerators[q]
        pMap[origin] = posInOrigin; //origin produced the answer just now, so testing returns true. Also, it can't be disqualified

        for (int q = 0; q < QEnumerators.size(); q++) {
            if(q == origin) continue;
            ENUMERATOR cqEnumerator = QEnumerators[q];
            ll j = cqEnumerator->findIndex(ans);
            if (j != ANSWER_NOT_FOUND && cqEnumerator->wasNotDisqualified(j)) {
                pMap[q] = j;
            }
        }
        return move(pMap);
    }

    int chooseOwnerUniformly(const unordered_map<int, ll>& providers) {
        vector<int> keys;
        keys.reserve(providers.size());
        for (auto &p : providers) {
            keys.push_back(p.first);
        }

        return keys[uniform_int_distribution<int>(0, keys.size() - 1)(generator)];
    }

    inline int chooseOwnerArbitrarily(const unordered_map<int, ll>& providers) {
        // the way of choosing the owner does not matter, we'll choose using begin.
        return providers.begin()->first;
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
