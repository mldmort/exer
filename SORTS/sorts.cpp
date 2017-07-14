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

int main() {

  int N;
  cout << "Please inter the size of the sorting problem (an integer): ";
  cin >> N;

  vector<double> unsorted;
  // initialize the unsorted somehow
  unsorted.resize(N);
  for (int i = 0; i < N; ++i) {
    unsorted[i] = double(rand()) / RAND_MAX * 100.0;
  }

  string sort_type;
  cout << "Please specify the method of sort, options for now, INSERT / MERGE (a string): ";
  cin >> sort_type;

  vector<double> sorted;
  if (sort_type == "INSERT") {
    InsertSort sortobj;
    sortobj.Sort(unsorted);
    sorted = unsorted;
  } else if (sort_type == "MERGE") {
    MergeSort sortobj;
    sorted = sortobj.Sort(unsorted);
  }

  // output
  for (int i = 0; i < sorted.size(); ++i) {
    cout << "i: " << i << " , data: " << sorted[i] << endl;
  }

  return 0;
}
