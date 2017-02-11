#include <iostream>
#include <cstring>
using namespace std;
// 在此处补充你的代码
class Array2{
    private:
        int row;
        int col;
        int *p = NULL;
    public:
        Array2(int r, int c){
            row = r;
            col = c;
            p = new int[c*r];
        }

        Array2(){
            p = NULL;
        } 

        Array2 & operator=(const Array2 & arr2){
             if(arr2.p == p) return *this;
             if(p) delete [] p;
             row = arr2.row;
             col = arr2.col;
             p = new int[row*col];
             memcpy(p, arr2.p, sizeof(int)*row*col);
             return *this;
        }

        int * operator[](int index){
            return p + col*index; 
        }

        int & operator()(int i, int j){
            return p[i*col + j]; 
        }
    
        ~Array2(){
             if(p) delete [] p;
        }
};

int main() {
    Array2 a(3,4);
    int i,j;
    for( i = 0;i < 3; ++i )
        for( j = 0; j < 4; j ++ ){
            a[i][j] = i * 4 + j;
//            cout<<a[i][j]<<",";
        }
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << a(i, j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b; b = a;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
