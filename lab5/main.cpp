#include <iostream>
#include <cstdio>
#include <sstream>
#include <iomanip>
typedef unsigned long long uint;

const uint SIZE=(sizeof(uint))*8,
           SIZE2=SIZE/2,
           POW2=uint(1)<<SIZE2;
const uint MAX_SIZE=10000;
using namespace std;
inline void addc(uint& a,const uint& b,uint& carry){
    a+=b;
    if(a<b)
        ++carry;
}

void long_len_correct(uint *src,uint &len){
    for(uint *ptr=src+len-1;!(*ptr);ptr--,len--);
}
void long_clear(uint *src,uint len){
    for(;len;src++,len--)
        *src=0;
}

void mult1(uint a,uint b,uint *res,uint& car){
    uint r0=(a%POW2)*(b%POW2),
         r01=(a%POW2)*(b>>SIZE2),
         r10=(a>>SIZE2)*(b%POW2),
         r1=(a>>SIZE2)*(b>>SIZE2);
    uint car0=0;
    addc(res[0],r0,car0);
    addc(res[0],(r01%POW2)<<SIZE2,car0);
    addc(res[0],(r10%POW2)<<SIZE2,car0);

    addc(res[1],car0,car);
    addc(res[1],r1,car);
    addc(res[1],r01>>SIZE2,car);
    addc(res[1],r10>>SIZE2,car);
}

void long_mult(uint *a, uint la,uint *b, uint lb, uint *res,uint &len){
    uint i,j,car0=0,car1=0,car2=0,maxi=la+lb-1;
    long_clear(res,la+lb);
    for(i=0;i<=maxi;i++){
        addc(res[i],car0,car1);
        for(j=0;j<=i;j++){
            if(j>=la)
                break;
            if((i-j)>=lb)
                continue;
            mult1(a[j],b[i-j],res+i,car2);
        }
        car0=car1;car1=car2;car2=0;
    }
    len=maxi+1;
    if(car0){
        len=maxi+1;
        res[len]=car0;
        len++;
    }
    if(car1){
        len=maxi+2;
        res[len]=car1;
        len++;
    }
    if(car2){
        len=maxi+3;
        res[len]=car2;
        len++;
    }
    long_len_correct(res,len);
}

void print_long(uint* num,uint len){
    for(uint *ptr=num+len-1;len;--ptr,--len){
        cout<<hex<<setw(sizeof(uint)*2)<<setfill('0')<<*ptr;
    }
    cout<<endl;
}

void long_copy(uint *src,uint len,uint* dst){
    for(;len;src++,dst++,len--)
        *dst=*src;
}

void long_from_string(const string &str,uint *res,uint &len){
    uint block_size=SIZE/4;
    int i; len=0;
    for(i=str.length()-block_size;i>=0;i-=block_size){
        istringstream istr(str.substr(i,block_size));
        istr>>hex>>*res;
        len++;res++;
    }
    if((i+block_size)>0){
        istringstream istr(str.substr(0,i+block_size));
        istr>>hex>>*res;
        len++;res++;
    }
}

void input_long(uint *res,uint &len){
    string s;
    cin>>s;
    long_clear(res,len);
    long_from_string(s,res,len);
}

int main()
{
    uint a[MAX_SIZE],c[MAX_SIZE],a_len=MAX_SIZE,c_len=MAX_SIZE;
    cout<<"Программа вычисляет A*C*C."<<endl;
    cout<<"Введите A."<<endl;
    input_long(a,a_len);
    cout<<"Введите C."<<endl;
    input_long(c,c_len);
    uint ac[MAX_SIZE],acc[MAX_SIZE],ac_len,acc_len;
    long_mult(a,a_len,c,c_len,ac,ac_len);
    long_mult(ac,ac_len,c,c_len,acc,acc_len);
    cout<<"A*C*C ="<<endl;
    print_long(acc,acc_len);
    return 0;
}

