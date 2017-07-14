#include <iostream>
#include <math.h>
#include <string.h>
#include <sstream>
#include <math.h>

using namespace std;

string mult_table[10][10];
void FillMultTable() {
  for (int i = 0; i < 10; i++)
    for(int j = 0; j < 10; j++) {
      ostringstream oss;
      oss << i*j;
      mult_table[i][j] = oss.str();
    }
}

string add(string a, string b) {
  int na = a.length();
  int nb = b.length();

  if (na>nb)
    b = string(na-nb,'0') + b;
  else
    a = string(nb-na,'0') + a;
  
  int n = a.length();
  string c(n,'0');
  int ext = 0;
  for (int i = n-1 ; i >=0 ; --i) {
    int sum = (a[i]-'0') + (b[i]-'0') + ext;
    int mod = sum % 10;
    ext = sum / 10;
    c[i] = '0' + mod;
  }
  if ( ext == 1)
    c = '1' + c; 

  return c;
}

string mult(const string& a, const string& b) {
  if ((a.length() == 1) && (b.length() == 1))
    return mult_table[a[0]-'0'][b[0]-'0'];
  
  if (a.empty() || b.empty()) 
    return "0";

  int na = a.length();
  int nb = b.length();
  string a0 = a.substr(0,na/2);
  string a1 = a.substr(na/2,string::npos); 
  string b0 = b.substr(0,nb/2);
  string b1 = b.substr(nb/2,string::npos); 
  //cout << "a0: " << a0 << " , a1: " << a1 << " , b0: " << b0 << " , b1: " << b1 << endl;
  
  string res = mult(a1,b1);
  res = add(res, mult(a0,b1) + string(na-na/2,'0'));
  res = add(res, mult(a1,b0) + string(nb-nb/2,'0'));
  res = add(res, mult(a0,b0) + string(na-na/2+nb-nb/2,'0'));

  return res;
}

/*
int mult(int a , int b, int n) { 
  if (n == 1) {
    return a*b;
  }
  else {
    int n_new = n/2;
    int a0 = a/(pow(10,n_new));
    int a1 = a - a0*pow(10,n_new);
    int b0 = b/(pow(10,n_new));
    int b1 = b - b0*pow(10,n_new);
    //cout << "a0: " << a0 << " , a1: " << a1 << " , b0: " << b0 << " , b1: " << b1 << endl;
    //cout << 
    //getchar();
    return ( mult(a0,b0,n_new)*pow(10,n) + (mult(a0,b1,n_new) + mult(a1,b0,n_new))*pow(10,n_new) + mult(a1,b1,n_new) );
  }
}
*/
int main() {
  FillMultTable();

  string a, b;
  cin >> a >> b;
  cout << "a: " << a << " , b: " << b << endl;
  
  cout << "a+b = " << add(a,b) << endl;
  
  cout << "a*b: " << mult(a,b) << endl;
  //cout << a*b << endl;

  //cout << mult_table[5][6] << ", " << mult_table[7][8] << endl;
  return 0;
}
