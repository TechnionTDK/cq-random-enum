#ifndef RANDOMORDERENUMERATION_Q2_NSANSWER_H
#define RANDOMORDERENUMERATION_Q2_NSANSWER_H

#include <iostream>
#include <chrono>
#include <boost/functional/hash.hpp>

using namespace std;

#ifndef PROJECTION_Q2_NS

#include "Q2_NS__R_Parcel.h"
#include "Q2_NS__N_Parcel.h"
#include "Q2_NS__S_Parcel.h"
#include "Q2_NS__PS_Parcel.h"
#include "Q2_NS__P_Parcel.h"

struct Q2_NSAnswer {
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

template<> Q2_NS__R_Key Q2_NSAnswer::to<Q2_NS__R_Key>() const {
    return {regionKey};
}

template<> Q2_NS__N_Key Q2_NSAnswer::to<Q2_NS__N_Key>() const {
    return {nationKey};
}

template<> Q2_NS__S_Key Q2_NSAnswer::to<Q2_NS__S_Key>() const {
    return {suppKey};
}

template<> Q2_NS__PS_Key Q2_NSAnswer::to<Q2_NS__PS_Key>() const {
    return {};
}

template<> Q2_NS__P_Key Q2_NSAnswer::to<Q2_NS__P_Key>() const {
    return {partKey};
}

template<> Q2_NS__R_Parcel Q2_NSAnswer::to<Q2_NS__R_Parcel>() const {
    return {regionKey};
}

template<> Q2_NS__N_Parcel Q2_NSAnswer::to<Q2_NS__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> Q2_NS__S_Parcel Q2_NSAnswer::to<Q2_NS__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> Q2_NS__PS_Parcel Q2_NSAnswer::to<Q2_NS__PS_Parcel>() const {
    return {partKey, suppKey};
}

template<> Q2_NS__P_Parcel Q2_NSAnswer::to<Q2_NS__P_Parcel>() const {
    return {partKey};
}


template<> void Q2_NSAnswer::set<Q2_NS__R_Parcel>(const Q2_NS__R_Parcel& p) {
    regionKey = p.regionKey;
}

template<> void Q2_NSAnswer::set<Q2_NS__N_Parcel>(const Q2_NS__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void Q2_NSAnswer::set<Q2_NS__S_Parcel>(const Q2_NS__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void Q2_NSAnswer::set<Q2_NS__PS_Parcel>(const Q2_NS__PS_Parcel& p) {
    partKey = p.partKey;
    suppKey = p.suppKey;
}

template<> void Q2_NSAnswer::set<Q2_NS__P_Parcel>(const Q2_NS__P_Parcel& p) {
    partKey = p.partKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q2_NSAnswer> {
        size_t operator()(const Q2_NSAnswer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q2_NSAnswer> {
        bool operator()(const Q2_NSAnswer& lhs, const Q2_NSAnswer& rhs) const {
            return lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey;
        }
    };
}

#else

#include "Q2_NS__R_Parcel.h"
#include "Q2_NS__N_Parcel.h"
#include "Q2_NS__S_Parcel.h"
#include "Q2_NS__PS_Parcel.h"
#include "Q2_NS__P_Parcel.h"

struct Q2_NSAnswer {
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

template<> Q2_NS__R_Key Q2_NSAnswer::to<Q2_NS__R_Key>() const {
    return {regionKey};
}

template<> Q2_NS__N_Key Q2_NSAnswer::to<Q2_NS__N_Key>() const {
    return {nationKey};
}

template<> Q2_NS__S_Key Q2_NSAnswer::to<Q2_NS__S_Key>() const {
    return {suppKey};
}

template<> Q2_NS__PS_Key Q2_NSAnswer::to<Q2_NS__PS_Key>() const {
    return {};
}

template<> Q2_NS__P_Key Q2_NSAnswer::to<Q2_NS__P_Key>() const {
    return {partKey};
}

template<> Q2_NS__R_Parcel Q2_NSAnswer::to<Q2_NS__R_Parcel>() const {
    return {regionKey};
}

template<> Q2_NS__N_Parcel Q2_NSAnswer::to<Q2_NS__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> Q2_NS__S_Parcel Q2_NSAnswer::to<Q2_NS__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> Q2_NS__PS_Parcel Q2_NSAnswer::to<Q2_NS__PS_Parcel>() const {
    return {partKey, suppKey};
}

template<> Q2_NS__P_Parcel Q2_NSAnswer::to<Q2_NS__P_Parcel>() const {
    return {partKey};
}


template<> void Q2_NSAnswer::set<Q2_NS__R_Parcel>(const Q2_NS__R_Parcel& p) {
    regionKey = p.regionKey;
}

template<> void Q2_NSAnswer::set<Q2_NS__N_Parcel>(const Q2_NS__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void Q2_NSAnswer::set<Q2_NS__S_Parcel>(const Q2_NS__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void Q2_NSAnswer::set<Q2_NS__PS_Parcel>(const Q2_NS__PS_Parcel& p) {
    partKey = p.partKey;
    suppKey = p.suppKey;
}

template<> void Q2_NSAnswer::set<Q2_NS__P_Parcel>(const Q2_NS__P_Parcel& p) {
    partKey = p.partKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q2_NSAnswer> {
        size_t operator()(const Q2_NSAnswer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q2_NSAnswer> {
        bool operator()(const Q2_NSAnswer& lhs, const Q2_NSAnswer& rhs) const {
            return lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey;
        }
    };
}

#endif

#endif //RANDOMORDERENUMERATION_Q2_NSANSWER_H