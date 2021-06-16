#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Data structure containing an array and a working array
struct Data{
    int size;
    int *sortit;
    int *working;
};

//Global Constants

//Function Prototypes
Data *fill(int);               //Fill the Array
void print(Data *,int);        //Print the array
void merge(Data *,int,int,int);//Merge 2 Arrays algorithm
void mrgSort(Data *,int,int);  //Merge Sort Recursions
void destroy(Data *);          //Deallocate
void mrkSort(Data *); 
void selectionSort(Data *arr, int n,int p) ;        //Mark sort/my sorting algorithm

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number generator
    srand(static_cast<unsigned int>(time(0)));
    //Allocate the arrays, Run on Mac
    //Mark sort data 10,000 -> 1/2 second, 100,000 -> 50 seconds
    //Merge sort  1,000,000 -> 1/2 second, 10,000,000 -> 5 seconds
    //          100,000,000 -> 60  seconds
    int n=100000,perLine=5;
    Data *a=fill(n);
    //Print the arrays
    //Sort the arrays then print
    int beg=time(0);
    mrgSort(a,0,a->size);
    //mrkSort(a);
    int totTime=time(0)-beg;
    cout<<"Total Run Time Merge Sort= "<<totTime<<" Seconds"<<endl;
    int numberToStop{9};

    Data *d=fill(n);
    //Print the arrays
    //Sort the arrays then print
    int beg1=time(0);
    selectionSort(d,n,numberToStop);
    //mrkSort(a);
    int totTime2=time(0)-beg1;
    cout<<"Total Run Time Selection Sort= "<<totTime2<<" Seconds"<<endl;
    //Deallocate data
    destroy(a);
    destroy(d);
    //Exit stage right
    return 0;
}

void mrkSort(Data *a){
    //Utilize mark sort as a comparison
    for(int pos=0;pos<a->size-1;pos++){
        for(int lst=pos+1;lst<a->size;lst++){
            if(a->sortit[pos]>a->sortit[lst]){
                int temp=a->sortit[pos];
                a->sortit[pos]=a->sortit[lst];
                a->sortit[lst]=temp;
            }
        }
    }
}

void destroy(Data *a){
    //Deallocate data elements
    delete []a->sortit;
    delete []a->working;
    delete a;
}

void mrgSort(Data *a,int beg,int end){
    int center=(beg+end)/2;//Split the task down the middle
    if((center-beg)>1)mrgSort(a,beg,center);//Got to be an array to split
    if((end-center)>1)mrgSort(a,center,end);//Got to be an array to split
    merge(a,beg,center,end);//Merge the sorted arrays into 1 larger sorted array
}

void merge(Data *a,int beg,int nlow,int nhigh){
    //Create a merged array
    int span=nhigh-beg;    //Span the range to merge
    int cntl=beg,cnth=nlow;//Independent counters to merge the split
    //Fill the array
    for(int i=0;i<span;i++){
        if(cntl==nlow){//Low done fill with the higher end of array
            a->working[i]=a->sortit[cnth++];
        }else if(cnth==nhigh){//High done fill with lower end of array
            a->working[i]=a->sortit[cntl++];
        }else if(a->sortit[cntl]<a->sortit[cnth]){
            a->working[i]=a->sortit[cntl++];//Fill with lower end
        }else{
            a->working[i]=a->sortit[cnth++];//Fill with higher end
        }
    }
    //Copy back from the working array to the sorted array
    for(int i=0;i<span;i++){
        a->sortit[beg+i]=a->working[i];
    }
}

void print(Data *a,int perLine){
    //First print the unsorted array
    cout<<endl;
    for(int i=0;i<a->size;i++){
        cout<<a->sortit[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

Data *fill(int n){
    //Allocate memory
    Data *data=new Data;
    data->size=n;
    data->sortit=new int[n];
    data->working=new int[n];
    for(int i=0;i<n;i++){
        data->sortit[i]=rand();
    }
    return data;
}
void swap(int *xp, int *yp)
{ 
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
} 
 
void selectionSort(Data *arr, int n, int p)
{
    int i, j, min_idx;
    int manySorted{};
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
      if(manySorted < p)
      {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
        if (arr->sortit[j] < arr->sortit[min_idx])
        {
          min_idx = j;
          manySorted++;
        }
            
 
        // Swap the found minimum element with the first element
        swap(&arr->sortit[min_idx], &arr->sortit[i]);
      }
      else
      {
        break;
      }
        
    }
}


