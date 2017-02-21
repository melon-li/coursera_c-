#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double num;
    cin >> num;
   // cout.setf(ios::fixed);//makes cout print floats with a fixed number of decimals
   // cout.precision(5);//sets this number to be five
    cout <<fixed<< setprecision(5)<<num << endl;
   
    //cout.unsetf(ios::fixed);//remove the setf(ios::fixed) 
  //  cout.setf(ios::scientific);
   // cout.precision(7);
    cout <<scientific<<setprecision(7)<< num << endl;
    return 0;
}
