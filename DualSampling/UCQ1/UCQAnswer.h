
#ifndef RANDOMORDERENUMERATION_UCQANSWER_H
#define RANDOMORDERENUMERATION_UCQANSWER_H

#include "../../CQs/Q7_1/files/Q7_1Answer.h"
#include "../../CQs/Q7_2/files/Q7_2Answer.h"

struct UCQAnswer {
    //data
    int orderKey;
    int custKey;
    int nationKey1;
    int nationKey2;
    int partKey;
    int suppKey;
    int lnumber;
    string n1_name;
    string n2_name;
    //end data
	
    
    UCQAnswer(const Q7_1Answer& a) : orderKey(a.orderKey), custKey(a.custKey), nationKey1(a.nationKey1), nationKey2(a.nationKey2),
    partKey(a.partKey), suppKey(a.suppKey), lnumber(a.lnumber), n1_name(a.n1_name), n2_name(a.n2_name) {};
    
    UCQAnswer(const Q7_2Answer& a) : orderKey(a.orderKey), custKey(a.custKey), nationKey1(a.nationKey1), nationKey2(a.nationKey2),
    partKey(a.partKey), suppKey(a.suppKey), lnumber(a.lnumber), n1_name(a.n1_name), n2_name(a.n2_name) {};
    
    
    template<typename T>
    T unwrap() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << orderKey << ", " << custKey << ", " << nationKey1 << ", " << nationKey2 << ", " << partKey
         << ", " << suppKey << ", " << lnumber << ", " << n1_name << ", " << n2_name << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << orderKey << ", " << custKey << ", " << nationKey1 << ", " << nationKey2 << ", " << partKey
         << ", " << suppKey << ", " << lnumber << ", " << n1_name << ", " << n2_name << "}";
        return st.str();
    }
};

  template<> Q7_1Answer UCQAnswer::unwrap<Q7_1Answer>() const {
      return {orderKey, custKey, nationKey1, nationKey2, partKey, suppKey, lnumber, n1_name, n2_name};
  }

  template<> Q7_2Answer UCQAnswer::unwrap<Q7_2Answer>() const {
      return {orderKey, custKey, nationKey1, nationKey2, partKey, suppKey, lnumber, n1_name, n2_name};
  }


#endif