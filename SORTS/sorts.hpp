#ifndef _SORTS_HPP_
#define _SORTS_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "assert.h"
using namespace std;

class SortBase {
public:
  string name;

  SortBase() {}

  //virtual void Sort(vector<double>&) = 0;

};

class InsertSort:public SortBase {
public:
  
  InsertSort(): SortBase() {
     name = "InsertSort";
  }

  string getName() const {return name;}

  void Sort(vector<double>& dataVec) {
    for (int i = 1; i < dataVec.size(); ++i) {
      double temp = dataVec[i];
      int ind = i-1;
      while ((ind >= 0) && (dataVec[ind]>temp)) {
        dataVec[ind+1] = dataVec[ind];
        ind -= 1;
      }
      dataVec[ind+1] = temp;
    }
  }
};

class MergeSort:public SortBase {
public:

  MergeSort(): SortBase() {
     name = "MergeSort";
  }

  string getName() const {return name;}

  vector<double> Sort(const vector<double>& dataVec) {
    if (dataVec.size() <= 1) {
      // Do nothing already sorted trivially
      return dataVec;
    }
    const vector<double> vecL(dataVec.begin(),dataVec.begin()+dataVec.size()/2);
    const vector<double> vecR(dataVec.begin()+dataVec.size()/2,dataVec.end());
    const vector<double>& dataVecL = Sort(vecL);
    const vector<double>& dataVecR = Sort(vecR);
    return Merge(dataVecL,dataVecR); 
  }

  vector<double> Merge(const vector<double>& v0, const vector<double>& v1) {
    vector<double> vec;
    vec.resize(v0.size() + v1.size());
    int i = 0;
    int j = 0;
    for (int ind = 0; ind < v0.size()+v1.size(); ++ind) {
      if ((j>=v1.size()) || ((i<v0.size()) && (v0[i] < v1[j]))) {
        vec[ind] = v0[i];
        i++;
      } else {
        vec[ind] = v1[j];
        j++;
      }
    }
    return vec;
  }

};

class QuickSort:public SortBase {
public:

  QuickSort(): SortBase() {
    name = "QuickSort";
  }

  virtual ~QuickSort() {}

  string getName() const {return name;}

  // this method does not change the input dataVec
  // however it's not very memory efficient since 
  // we create another vector to return, which also 
  // require more work. an alternative is to sort in place
  vector<double> Sort(vector<double>& dataVec) {
    if (dataVec.size() <= 1) {
      return dataVec;
    }
    int ipivot = int(rand()/RAND_MAX*(dataVec.size()-1));
    double vpivot = dataVec[ipivot];
    vector<double> L, R;
    for (int i = 0; i < dataVec.size(); ++i) {
      if (i == ipivot) continue;
      if (dataVec[i] <= vpivot)
        L.push_back(dataVec[i]);
      else if (dataVec[i] > vpivot)
        R.push_back(dataVec[i]);
    }
    assert((L.size() + R.size()) == dataVec.size()-1);
    vector<double> sL = this->Sort(L);
    vector<double> sR = this->Sort(R);
    vector<double> retVec(sL);
    retVec.push_back(vpivot);
    for (int i = 0; i < sR.size(); ++i)
      retVec.push_back(sR[i]);
    return retVec;
  }

};

#endif
