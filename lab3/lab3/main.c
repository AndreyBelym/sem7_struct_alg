#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//�吝� ᯨ᮪-�⥪ ��� �㭪樨 ���஢��
typedef struct stack {
    long high,low; //����� � ������ �࠭��� ⥪�饣� ��१�� ���஢��
    struct stack *prev; //�।��騩 ����� �⥪�
} STACK;

STACK* push(STACK *list,long low, long high){
  STACK *new_elem;
    new_elem=(STACK*)malloc(sizeof(STACK));
    if (new_elem!=NULL){
        new_elem->low=low;
        new_elem->high=high;
        new_elem->prev=list;
    }
    return new_elem;
}
STACK* pop(STACK *list){
  STACK *old_elem;
    if (list!=NULL){
        old_elem=list->prev;
        free(list);
    } else old_elem=NULL;
    return old_elem;
};

void clearstack(STACK *list){
  STACK *rider;
    rider=list;
    while(rider!=NULL){
        rider=pop(rider);
    }
};

int QuickSort(int *array, long size) {

  int log;

  int  swap,x;
  STACK *stck=NULL,*tmp=NULL;
  long i,j, L, R;

    log=((stck=push(stck,0,size-1))!=NULL);
    while (log&&(stck!=NULL)){
        L=stck->low; R=stck->high;
        stck=pop(stck);
        while (log&&L<R){
            i=L;j=R;x=array[(L+R)/2];
            do{
                while (array[i]<x) i++;
                while (x<array[j]) j--;
                if (i<=j){
                    swap=array[i];array[i]=array[j];array[j]=swap;
                    i++;j--;
                }
            }while(i<=j);
            if (R-i<j-L){
                if (L<j){
                    log=((tmp=push(stck,L,j))!=NULL);
                    if (log)
                        stck=tmp;
                    else
                        clearstack(stck);
                }
                L=i;

            } else {
                if (i<R){
                    log=((tmp=push(stck,i,R))!=NULL);
                    if (log)
                        stck=tmp;
                    else
                        clearstack(stck);
                }
                R=j;
            }
        }
    };
    return log;
}   

int main(){
    int n;
    int *X;
    int i=0;
    time_t t1,t2;

    srand(time(NULL));
    printf("������ ࠧ��� ���ᨢ�.\n");
    scanf("%d",&n);

    X=malloc(n*sizeof(int));
    for(i=0;i<n;++i){
        X[i]=rand();
    }
//    printf("��室�� ���ᨢ:\n");
//    for(i=0;i<n;++i){
//	    printf("%d ",X[i]);
//    }
    printf("\n");
    time(&t1);
    QuickSort(X,n);
    time(&t2);
//    printf("�����஢���� ���ᨢ:\n");
//    for(i=0;i<n;++i){
//	    printf("%d ",X[i]);
//    }
    printf("����祭��� �६�: %f ᥪ.\n",difftime(t2,t1));
    printf("\n");
    return 0;
}
