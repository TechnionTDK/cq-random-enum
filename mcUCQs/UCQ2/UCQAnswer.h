
#ifndef RANDOMORDERENUMERATION_UCQANSWER_H
#define RANDOMORDERENUMERATION_UCQANSWER_H

///singletons
#include "../../CQs/Q2_N/files/Q2_NIndex.h"
#include "../../CQs/Q2_P/files/Q2_PIndex.h"
#include "../../CQs/Q2_S/files/Q2_SIndex.h"

///pairs
#include "../../CQs/Q2_PS/files/Q2_PSIndex.h"
#include "../../CQs/Q2_NP/files/Q2_NPIndex.h"
#include "../../CQs/Q2_NS/files/Q2_NSIndex.h"

///triplets
#include "../../CQs/Q2_PSN/files/Q2_PSNIndex.h"

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
    
    UCQAnswer(const Q2_NPAnswer& a) : partKey(a.partKey), suppKey(a.suppKey), nationKey(a.nationKey), regionKey(a.regionKey) {};
    
    UCQAnswer(const Q2_NSAnswer& a) : partKey(a.partKey), suppKey(a.suppKey), nationKey(a.nationKey), regionKey(a.regionKey) {};
    
    UCQAnswer(const Q2_PSAnswer& a) : partKey(a.partKey), suppKey(a.suppKey), nationKey(a.nationKey), regionKey(a.regionKey) {};
    
    UCQAnswer(const Q2_PSNAnswer& a) : partKey(a.partKey), suppKey(a.suppKey), nationKey(a.nationKey), regionKey(a.regionKey) {};
    
    
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
  
  template<> Q2_NPAnswer UCQAnswer::unwrap<Q2_NPAnswer>() const {
      return {partKey, suppKey, nationKey, regionKey};
  }
  
  template<> Q2_NSAnswer UCQAnswer::unwrap<Q2_NSAnswer>() const {
      return {partKey, suppKey, nationKey, regionKey};
  }
  
  template<> Q2_PSAnswer UCQAnswer::unwrap<Q2_PSAnswer>() const {
      return {partKey, suppKey, nationKey, regionKey};
  }
  
  template<> Q2_PSNAnswer UCQAnswer::unwrap<Q2_PSNAnswer>() const {
      return {partKey, suppKey, nationKey, regionKey};
  }


#endif