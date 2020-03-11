#ifndef RANDOMORDERENUMERATION_Q2ANSWER_H
#define RANDOMORDERENUMERATION_Q2ANSWER_H

#include <iostream>
#include <chrono>
#include <boost/functional/hash.hpp>

using namespace std;

#ifndef PROJECTION

#include "Q2__R_Parcel.h"
#include "Q2__N_Parcel.h"
#include "Q2__S_Parcel.h"
#include "Q2__PS_Parcel.h"
#include "Q2__P_Parcel.h"

struct Q2Answer {
    //data
    int partKey;
    int suppKey;
    int nationKey;
    int regionKey;
    //end data
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }
    
    template<typename T>
    void set(const T& t) {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << partKey;
        cout << ", " << suppKey;
        cout << ", " << nationKey;
        cout << ", " << regionKey << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << partKey;
        st << ", " << suppKey;
        st << ", " << nationKey;
        st << ", " << regionKey;
        st << "}";
        return st.str();
    }
};

template<> Q2__R_Key Q2Answer::to<Q2__R_Key>() const {
    return {regionKey};
}

template<> Q2__N_Key Q2Answer::to<Q2__N_Key>() const {
    return {nationKey};
}

template<> Q2__S_Key Q2Answer::to<Q2__S_Key>() const {
    return {suppKey};
}

template<> Q2__PS_Key Q2Answer::to<Q2__PS_Key>() const {
    return {};
}

template<> Q2__P_Key Q2Answer::to<Q2__P_Key>() const {
    return {partKey};
}

template<> Q2__R_Parcel Q2Answer::to<Q2__R_Parcel>() const {
    return {regionKey};
}

template<> Q2__N_Parcel Q2Answer::to<Q2__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> Q2__S_Parcel Q2Answer::to<Q2__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> Q2__PS_Parcel Q2Answer::to<Q2__PS_Parcel>() const {
    return {partKey, suppKey};
}

template<> Q2__P_Parcel Q2Answer::to<Q2__P_Parcel>() const {
    return {partKey};
}


template<> void Q2Answer::set<Q2__R_Parcel>(const Q2__R_Parcel& p) {
    regionKey = p.regionKey;
}

template<> void Q2Answer::set<Q2__N_Parcel>(const Q2__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void Q2Answer::set<Q2__S_Parcel>(const Q2__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void Q2Answer::set<Q2__PS_Parcel>(const Q2__PS_Parcel& p) {
    partKey = p.partKey;
    suppKey = p.suppKey;
}

template<> void Q2Answer::set<Q2__P_Parcel>(const Q2__P_Parcel& p) {
    partKey = p.partKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q2Answer> {
        size_t operator()(const Q2Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q2Answer> {
        bool operator()(const Q2Answer& lhs, const Q2Answer& rhs) const {
            return lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey;
        }
    };
}

#else

#include "Q2__R_Parcel.h"
#include "Q2__N_Parcel.h"
#include "Q2__S_Parcel.h"
#include "Q2__PS_Parcel.h"
#include "Q2__P_Parcel.h"

struct Q2Answer {
    //data
    int partKey;
    int suppKey;
    int nationKey;
    int regionKey;
    //end data
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }
    
    template<typename T>
    void set(const T& t) {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << partKey;
        cout << ", " << suppKey;
        cout << ", " << nationKey;
        cout << ", " << regionKey << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << partKey;
        st << ", " << suppKey;
        st << ", " << nationKey;
        st << ", " << regionKey;
        st << "}";
        return st.str();
    }
};

template<> Q2__R_Key Q2Answer::to<Q2__R_Key>() const {
    return {regionKey};
}

template<> Q2__N_Key Q2Answer::to<Q2__N_Key>() const {
    return {nationKey};
}

template<> Q2__S_Key Q2Answer::to<Q2__S_Key>() const {
    return {suppKey};
}

template<> Q2__PS_Key Q2Answer::to<Q2__PS_Key>() const {
    return {};
}

template<> Q2__P_Key Q2Answer::to<Q2__P_Key>() const {
    return {partKey};
}

template<> Q2__R_Parcel Q2Answer::to<Q2__R_Parcel>() const {
    return {regionKey};
}

template<> Q2__N_Parcel Q2Answer::to<Q2__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> Q2__S_Parcel Q2Answer::to<Q2__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> Q2__PS_Parcel Q2Answer::to<Q2__PS_Parcel>() const {
    return {partKey, suppKey};
}

template<> Q2__P_Parcel Q2Answer::to<Q2__P_Parcel>() const {
    return {partKey};
}


template<> void Q2Answer::set<Q2__R_Parcel>(const Q2__R_Parcel& p) {
    regionKey = p.regionKey;
}

template<> void Q2Answer::set<Q2__N_Parcel>(const Q2__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void Q2Answer::set<Q2__S_Parcel>(const Q2__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void Q2Answer::set<Q2__PS_Parcel>(const Q2__PS_Parcel& p) {
    partKey = p.partKey;
    suppKey = p.suppKey;
}

template<> void Q2Answer::set<Q2__P_Parcel>(const Q2__P_Parcel& p) {
    partKey = p.partKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q2Answer> {
        size_t operator()(const Q2Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q2Answer> {
        bool operator()(const Q2Answer& lhs, const Q2Answer& rhs) const {
            return lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey;
        }
    };
}

#endif

#endif //RANDOMORDERENUMERATION_Q2ANSWER_H