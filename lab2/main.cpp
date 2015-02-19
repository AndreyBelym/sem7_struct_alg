#include <iostream>
#include <string>
using namespace std;
struct neg_bin{
    bool carry;
    int num;
};

bool sign_bit(int n){
    return n>>31;
};
void print_bin(int n){
    for(int i=0;i<32;i++)
    {
        cout<<(sign_bit(n)?'1':'0');
        n<<=1;
    };
    cout<<endl;
}
neg_bin bin2neg_bin(int n){
    bool cnt=false,carry=false;
    if(sign_bit(n)){
        cnt=true;
        n=~n;
    }
    int tmp=0,i=0;
    bool bit;
    while(n){
        cnt=!cnt;
        bit=n&1;
        if(carry){
            if(cnt&&!bit)
                carry=false;
            bit=!bit;
        } else {
            carry=bit&&!cnt;
        }
        tmp+=(bit?1<<i:0);
        n>>=1;
        i++;
    }
    neg_bin res;
    res.num=tmp;
    bool carry0=carry;
    bool carry1=carry&&cnt;
    res.num+=(carry0?1<<i:0);
	if(i>=31)
		res.carry=true;
	else{
		res.carry=false;
        res.num+=carry1?1<<(i+1):0;
	}
    return res;
}
int neg_bin2dec(neg_bin b){
    int i=0;
    int t=0,a=0;
    while(b.num){
        a=((b.num&1)*(1<<i));
        if(i%2)
            a=-a;
        t+=a;
        b.num>>=1;
        i++;
    }
    return t;
}
int main(){
    int n;
    cout<<"Введите целое число: ";
	cin>>n;
    if(n<0)
        n--;
	cout<<"Обратный код числа: ";
	print_bin(n);
	neg_bin b=bin2neg_bin(n);
	cout<<"Представление числа в системе счисления с основанием -2: "<<endl;
	if(b.carry)
		cout<<'1';
	print_bin(b.num);
    return 0;
}

