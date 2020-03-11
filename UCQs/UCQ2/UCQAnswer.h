
#ifndef RANDOMORDERENUMERATION_UCQANSWER_H
#define RANDOMORDERENUMERATION_UCQANSWER_H

#include "../../CQs/Q2_N/files/Q2_NIndex.h"
#include "../../CQs/Q2_S/files/Q2_SIndex.h"
#include "../../CQs/Q2_P/files/Q2_PIndex.h"

struct UCQAnswer {
    //data
    int partKey;
    int suppKey;
    int nationKey;
    int regionKey;
    //end data
    
    UCQAnswer(const Q2_NAnswer& a) : partKey(a.partKey), suppKey(a.suppKey), nationKey(a.nationKey), regionKey(a.regionKey) {};
    
    UCQAnswer(const Q2_PAnswer& a) : partKey(a.partKey), suppKey(a.suppKey), nationKey(a.nationKey), regionKey(a.regionKey) {};
    
    UCQAnswer(const Q2_SAnswer& a) : partKey(a.partKey), suppKey(a.suppKey), nationKey(a.nationKey), regionKey(a.regionKey) {};
    
    
    template<typename T>
    T unwrap() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << partKey << ", " << suppKey << ", " << nationKey << ", " << regionKey << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << partKey << ", " << suppKey << ", " << nationKey << ", " << regionKey << "}";
        return st.str();
    }
};

  template<> Q2_NAnswer UCQAnswer::unwrap<Q2_NAnswer>() const {
      return {partKey, suppKey, nationKey, regionKey};
  }
  
  template<> Q2_PAnswer UCQAnswer::unwrap<Q2_PAnswer>() const {
      return {partKey, suppKey, nationKey, regionKey};
  }
  
  template<> Q2_SAnswer UCQAnswer::unwrap<Q2_SAnswer>() const {
      return {partKey, suppKey, nationKey, regionKey};
  }


#endif