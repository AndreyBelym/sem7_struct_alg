#include <iostream>

using namespace std;

class DivByZeroExcpt:public std::exception {};
class WrongNumberExcpt: public std::exception {};
struct rational {
    int n,m,z;
};
int gcd(int a,int b){
    int r;
    if(b>a){
        r=b;b=a;a=r;
    }
    while(b){
        r=a%b;
        a=b;
        b=r;
    }
    return a;
}

void rational_simplify(rational &a){
    int r=gcd(a.n,a.m);
    a.n/=r; a.m/=r;
}
void rational_norm(rational &a){
    rational_simplify(a);
    a.z+=a.n/a.m;
    a.n%=a.m;
}
void rational_denorm(rational &a){
    a.n+=a.m*a.z;
    a.z=0;
    rational_simplify(a);
}


rational rational_plus(rational a,rational b){
    rational res;
    res.z=a.z+b.z;
    if(a.m==b.m){
        res.n=a.n+b.n;
        res.m=a.m;
    } else {
        res.n=a.n*b.m+b.n*a.m;
        res.m=a.m*b.m;
    }
    rational_norm(res);
    return res;
}

rational rational_div(rational a,rational b){
    rational res;
    rational_denorm(a); rational_denorm(b);
    if(!b.n)
        throw DivByZeroExcpt();
    res.n=a.n*b.m;
    res.m=a.m*b.n;
    res.z=0;
    rational_norm(res);
    return res;
}
void rational_print(const rational& a){
    cout<<a.z<<" "<<a.n<<"/"<<a.m<<endl;
}
void rational_input(rational &a){
    cin>>noskipws;
    char c;
    cin>>ws>>a.z>>c>>a.n>>c>>a.m;
    cin>>skipws;
    if(!cin.good()||!a.m)
        throw WrongNumberExcpt();
}

int main()
{
    rational a,b,c,d,r;
    cout<<"Программа рассчитывает значение выражения C+B/A/D."<<endl;
    try {
        cout<<"Введите A."<<endl;
        rational_input(a);
        cout<<"Введите B."<<endl;
        rational_input(b);
        cout<<"Введите С."<<endl;
        rational_input(c);
        cout<<"Введите D."<<endl;
        rational_input(d);
        r=rational_div(b,a);
        cout<<"B/A = "<<endl;
        rational_print(r);
        r=rational_div(r,d);
        cout<<"B/A/D = "<<endl;
        rational_print(r);
        r=rational_plus(c,r);
        cout<<"C+B/A/D ="<<endl;
        rational_print(r);
    } catch (DivByZeroExcpt) {
        cerr<<"Деление на ноль!"<<endl;
        exit(-1);
    } catch (WrongNumberExcpt) {
        cerr<<"Неправильное число!"<<endl;
        exit(-2);
    }

    return 0;
}

