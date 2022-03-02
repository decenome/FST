#include <iostream>
#include <bitset>

using namespace std;

#define byte unsigned char

struct A{
    int len;
    char data[100];
};

struct B{
    double a;
    char b[10];
    int c;
    char d[10];
};

int main(){
    cout<<sizeof(B)<<endl;
    cout<<sizeof(A)<<endl;
    byte c[20];

    auto b1= B{
        1.1,"AAA",109,"BBbbbB"
    };

    shared_ptr<A>pa=std::make_shared<A>();
    pa->len=10;

    memcpy(pa->data, &b1,sizeof(b1));

    B b2;

    memcpy(&b2,pa->data,sizeof(b2));

    cout<<b2.a<<endl;
    cout<<b2.b<<endl;
    cout<<b2.c<<endl;
    cout<<b2.d<<endl;

    char* b3=(char*)&b2;

    cout<<b3<<endl;
    // for (size_t i = 0; i < sizeof(pa->data); i++)
    // {
    //     /* code */
    //     cout<<pa->data[i]<<endl;
    // }

    // memset(c,0,20);
    // memcpy(c,"123123",3);
    // memcpy(c+10,"123123",3);
    // for (size_t i = 0; i < 20; i++)
    //{
        /* code */
        // std::cout<<c[i]<<std::endl;
    //}
    
}