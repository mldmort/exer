#include "sorts.hpp"

template<class T>
class DataFinder {
public:
  //vector<T> data; // data

  //DataFinder(vector<T> _data): data(_data) {}
  DataFinder() {}

  virtual ~DataFinder() {}

  double Find(vector<T> &D, int k) {
    assert(k < D.size());
    // if D.size()<50 sortMerge
    if (D.size() < 50) {
      MergeSort sortObj;
      vector<double> sorted = sortObj.Sort(D);
      return sorted[k-1];
    }
    // else define a pivot
    double pivot = FindPivot(D);
    // define a L and R arround the pivot
    vector<T> L;
    vector<T> R;
    Partition(D,L,R,pivot);
    if (L.size() == k-1) {
      return pivot;
    } else if (L.size() > k-1) {
      return Find(L,k);
    } else if (L.size() < k-1) {
      return Find(R,k-L.size()-1);
    } else {
      assert(0);
    }

    return 0;
  }

private:
  double FindPivot(vector<T> &D) {
    const int subVecSize = 5;
    const int subVecInd = int(subVecSize/2) + 1;
    int nSec = D.size()/subVecSize;
    if (D.size()%subVecSize != 0) 
      nSec++;
    vector<double> subVecMed;
    for (int i = 0; i < nSec-1; ++i) {
      vector<T> subD(D.begin()+i*subVecSize,D.begin()+(i+1)*subVecSize);
      subVecMed.push_back( Find(subD,subVecInd) );
    }
    vector<T> subD(D.begin()+(nSec-1)*subVecSize,D.end());
    subVecMed.push_back( Find(subD,subVecInd) );
    
    const int ind = int(subVecMed.size()/2);
    return Find(subVecMed,ind);
  }

  void Partition(vector<T> &D, vector<T> &L, vector<T> &R, double &p) {
    // don't put the value of p to any L or R
    for (int i = 0; i < D.size(); ++i) {
      if (D[i] < p) {
        L.push_back(D[i]);
      } else if (D[i] > p){
        R.push_back(D[i]);
      }
    }
  }

};

int main() {

  int N;
  cout << "Please inter the size of the array of random numbers (Enter an integer): ";
  cin >> N;

  vector<double> array;
  // initialize the array somehow
  array.resize(N);
  for (int i = 0; i < N; ++i) {
    array[i] = double(rand()) / RAND_MAX * 100.0;
  }

  int k;
  cout << "Size of the array is: " << N << ", Please enter the element required (k'th element, enter k): " << endl;
  cin >> k;
  cout << "You chose to get " << k << "'th element!" << endl;

  //double * arrayP = &array[0];
  for (int i = 0; i < N; ++i) {
    cout << "array: " << array[i] << endl;
  }
  DataFinder<double> myDataFinder;
  double answer = myDataFinder.Find(array,k);

  // output
  cout << "the " << k << "'th element is " << answer << endl;
  
  vector<double> sorted;
  MergeSort sortobj;
  sorted = sortobj.Sort(array);

  for (int i = 0; i < N; ++i) {
    cout << "sorted: " << sorted[i] << endl;
  }
  cout << "it should be equal: " << sorted[k-1] << endl;

  return 0;
}
