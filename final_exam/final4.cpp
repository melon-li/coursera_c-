#include <iostream>
using namespace std;

class CType{
    private:
        int n;
    public:
        void setvalue(int n_){n = n_;}
        CType & operator++(int){
            n = n*n;
            return *this;
        }
        friend ostream & operator<<(ostream &out, const CType &c){
            out<<c.n;
            return out;
        }
};
int main(int argc, char* argv[]) {
        CType obj;
        int n;
        cin>>n;
        while ( n ) {
                obj.setvalue(n);
                cout<<obj++<<" "<<obj<<endl;
                cin>>n;
        }
        return 0;
}
