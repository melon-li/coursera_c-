#include <iostream>
using namespace std;
// 在此处补充你的代码
template <class T>
class CArray3D{
    private:
        template <class T1>
        class CArray2D{
             private:
                 int i;
                 int j;
                 T1 *p2d;
             public:
                 CArray2D(){p = NULL;}
                 CArray2D(int i_, int j_){
                     i = i_;
                     j = j_;
                     p2d = new T1[i*j];
                 }
                 T1 * operator[](int index){
                     return p2d + j*index;
                 }
                 ~CArray2D(){
                     if(p) delete [] p2d;
                 }
        };

    private:
        int x;
        int y;
        int z;
        CArray2D <T> **p;

    public:
        CArray3D(){ p = NULL;}
        CArray3D(int x_, int y_, int z_){
            x = x_;
            y = y_;
            z = z_;
            p = new CArray2D <T> *[x];
            for(int i=0; i<x; i++){
                p[i] = new CArray2D<T>(y, z);
            }
        }
        ~CArray3D(){
            if(p)delete [] p;
        }
    
        CArray2D<T> & operator[](int i){
            return *p[i];
        }
        T & operator()(int i, int j, int k){
            return (*p[i])[j][k];
        }
};

int main()
{
    CArray3D<int> a(3,4,5);
    int No = 0;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                //cout << a[i][j][k] << ",";
                cout << a(i, j, k) << ",";
    return 0;
}
