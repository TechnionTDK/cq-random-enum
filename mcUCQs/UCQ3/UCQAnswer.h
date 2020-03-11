
#ifndef RANDOMORDERENUMERATION_UCQANSWER_H
#define RANDOMORDERENUMERATION_UCQANSWER_H

#include "../../CQs/QA/files/QAAnswer.h"
#include "../../CQs/QE/files/QEAnswer.h"
#include "../../CQs/QAE/files/QAEAnswer.h"

struct UCQAnswer {
    //data
    int orderKey;
    int suppKey;
    int nationKey;
    int regionKey;
    string rname;
    //end data
    
    UCQAnswer(const QAAnswer& a) : orderKey(a.orderKey), suppKey(a.suppKey), nationKey(a.nationKey), regionKey(a.regionKey), rname(a.rname) {};
    
    UCQAnswer(const QEAnswer& a) : orderKey(a.orderKey), suppKey(a.suppKey), nationKey(a.nationKey), regionKey(a.regionKey), rname(a.rname) {};
    
    UCQAnswer(const QAEAnswer& a) : orderKey(a.orderKey), suppKey(a.suppKey), nationKey(a.nationKey), regionKey(a.regionKey), rname(a.rname) {};
    
    template<typename T>
    T unwrap() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << orderKey;
        cout << ", " << suppKey;
        cout << ", " << nationKey;
        cout << ", " << regionKey;
        cout << ", " << rname << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << orderKey;
        st << ", " << suppKey;
        st << ", " << nationKey;
        st << ", " << regionKey;
        st << ", " << rname;
        st << "}";
        return st.str();
    }
};

template<> QAAnswer UCQAnswer::unwrap<QAAnswer>() const {
    return {orderKey, suppKey, nationKey, regionKey, rname};
}

template<> QEAnswer UCQAnswer::unwrap<QEAnswer>() const {
    return {orderKey, suppKey, nationKey, regionKey, rname};
}

template<> QAEAnswer UCQAnswer::unwrap<QAEAnswer>() const {
    return {orderKey, suppKey, nationKey, regionKey, rname};
}




#endif