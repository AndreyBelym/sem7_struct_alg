#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double calcI(double I0,double U,double phi,double eps){
    double t=U/phi,r0=1,r=t,s=1+r;
    unsigned n=2;
    while(r>=r0||r>=eps){
        r0=r;
        r*=t/n;
        s+=r;n++;
    }
    return (s-1)*I0;
}
double test_calcI(double I0,double U,double phi) {
    return I0*(exp(U/phi)-1);
}

int main()
{
    double I0,U,phi,eps;
    cout<<"Программа рассчитывает ток диоода."<<endl;
    cout<<"Введите тепловой ток."<<endl;
    cin>>I0;
    cout<<"Введите падение напряжения."<<endl;
    cin>>U;
    cout<<"Введите температурный потенциал."<<endl;
    cin>>phi;
    cout<<"Введите точность."<<endl;
    cin>>eps;
    cout<<"Значение, рассчитанное через ряд Тейлора: "<<endl;
    cout <<setprecision(19)<<calcI(I0,U,phi,eps)<<endl;
    cout<<"Значение, рассчитанное стандартными функциями: "<<endl;
    cout <<setprecision(19)<<test_calcI(I0,U,phi)<<endl;
    return 0;
}

