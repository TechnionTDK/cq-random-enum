#ifndef RANDOMORDERENUMERATION_Q0ANSWER_H
#define RANDOMORDERENUMERATION_Q0ANSWER_H

#include <iostream>
#include <chrono>
#include <boost/functional/hash.hpp>

using namespace std;

#ifndef PROJECTION

#include "Q0__R_Parcel.h"
#include "Q0__N_Parcel.h"
#include "Q0__S_Parcel.h"
#include "Q0__PS_Parcel.h"

struct Q0Answer {
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

template<> Q0__R_Key Q0Answer::to<Q0__R_Key>() const {
    return {regionKey};
}

template<> Q0__N_Key Q0Answer::to<Q0__N_Key>() const {
    return {nationKey};
}

template<> Q0__S_Key Q0Answer::to<Q0__S_Key>() const {
    return {suppKey};
}

template<> Q0__PS_Key Q0Answer::to<Q0__PS_Key>() const {
    return {};
}

template<> Q0__R_Parcel Q0Answer::to<Q0__R_Parcel>() const {
    return {regionKey};
}

template<> Q0__N_Parcel Q0Answer::to<Q0__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> Q0__S_Parcel Q0Answer::to<Q0__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> Q0__PS_Parcel Q0Answer::to<Q0__PS_Parcel>() const {
    return {partKey, suppKey};
}


template<> void Q0Answer::set<Q0__R_Parcel>(const Q0__R_Parcel& p) {
    regionKey = p.regionKey;
}

template<> void Q0Answer::set<Q0__N_Parcel>(const Q0__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void Q0Answer::set<Q0__S_Parcel>(const Q0__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void Q0Answer::set<Q0__PS_Parcel>(const Q0__PS_Parcel& p) {
    partKey = p.partKey;
    suppKey = p.suppKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q0Answer> {
        size_t operator()(const Q0Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q0Answer> {
        bool operator()(const Q0Answer& lhs, const Q0Answer& rhs) const {
            return lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey;
        }
    };
}

#else

#include "Q0__R_Parcel.h"
#include "Q0__N_Parcel.h"
#include "Q0__S_Parcel.h"
#include "Q0__PS_Parcel.h"

struct Q0Answer {
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

template<> Q0__R_Key Q0Answer::to<Q0__R_Key>() const {
    return {regionKey};
}

template<> Q0__N_Key Q0Answer::to<Q0__N_Key>() const {
    return {nationKey};
}

template<> Q0__S_Key Q0Answer::to<Q0__S_Key>() const {
    return {suppKey};
}

template<> Q0__PS_Key Q0Answer::to<Q0__PS_Key>() const {
    return {};
}

template<> Q0__R_Parcel Q0Answer::to<Q0__R_Parcel>() const {
    return {regionKey};
}

template<> Q0__N_Parcel Q0Answer::to<Q0__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> Q0__S_Parcel Q0Answer::to<Q0__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> Q0__PS_Parcel Q0Answer::to<Q0__PS_Parcel>() const {
    return {partKey, suppKey};
}


template<> void Q0Answer::set<Q0__R_Parcel>(const Q0__R_Parcel& p) {
    regionKey = p.regionKey;
}

template<> void Q0Answer::set<Q0__N_Parcel>(const Q0__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void Q0Answer::set<Q0__S_Parcel>(const Q0__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void Q0Answer::set<Q0__PS_Parcel>(const Q0__PS_Parcel& p) {
    partKey = p.partKey;
    suppKey = p.suppKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q0Answer> {
        size_t operator()(const Q0Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q0Answer> {
        bool operator()(const Q0Answer& lhs, const Q0Answer& rhs) const {
            return lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey;
        }
    };
}

#endif

#endif //RANDOMORDERENUMERATION_Q0ANSWER_H