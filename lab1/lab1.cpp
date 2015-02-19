#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;
void simple_sort(int arr[], int size)
{
  int i,j,tmp;
  for (j=1;j<size;j++)
  {
    i=j-1;
    tmp=arr[j];
    while (i>=0&&tmp<arr[i])
      arr[i+1]=arr[i--];
    arr[i+1]=tmp;
  }
}

void simple_sort2(int arr[],int size){
    int n=128;
    int beg,end,j,k,s=size/n,tmp;
    do{
        beg=0; s=size/n; end=beg+s;
        while(end<=size){
            for (j=beg+1;j<end;j++)
              {
                k=j-1;
                tmp=arr[j];
                while (k>=beg&&tmp<arr[k])
                  arr[k+1]=arr[k--];
                arr[k+1]=tmp;
              }
            beg=end; end+=s;
        }
        n/=2;
    } while(n>=1);
}
void print_array(int arr[],int size){
    for(int i=0;i<size;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

int* create_array(int n){
    srand(time(0));
    int* a=new int[n];
    for(int i=0;i<n;i++){
        a[i]=rand();
    }
    return a;
}
int* copy_array(int *a,int n){
    int *b=new int[n];
    for(int i=0;i<n;i++){
        b[i]=a[i];
    }
    return b;
}

int main(){
    int len=0;
    cout<<"Введите размер массива."<<endl;
    cin>>len;
    if(len<=0)
        return 0;

    int n;
    cout<<"Введите количество проходов."<<endl;
    cin>>n;
    if(n<=1)
        return 0;
    
    double avg_a=0,avg_b=0,t;
    
    for(int i=1;i<=n;++i){
        int *a=create_array(len),
            *b=copy_array(a,len);
        clock_t t1,t2;
        t1=clock();
        simple_sort(a,len);
        t2=clock();
        t=double(t2-t1)/CLOCKS_PER_SEC;
        cout<<"Проход #"<<i<<", simple_sort: "<<t<<endl;
        avg_a+=t;
        t1=clock();
        simple_sort2(b,len);
        t2=clock();
        t=double(t2-t1)/CLOCKS_PER_SEC;
        cout<<"Проход #"<<i<<", simple_sort2: "<<t<<endl;
        avg_b+=t;
        delete[] a; delete[] b;
    }
    avg_a/=n;avg_b/=n;
    cout<<"Среднее за "<<n<<" проходов: "<<endl;
    cout<<"simple_sort: "<<avg_a<<endl;
    cout<<"simple_sort2: "<<avg_b<<endl;
    return 0;
}
