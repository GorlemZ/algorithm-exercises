#include <stdio.h>

void stamp( int a[], int len)
{
	int i=0;
	while (i<len)
	{
		printf(" %d ", a[i]);
		i++;
	}
}

void scambia ( int a[] , int i , int j )
{
	int k, l;
	k=a[i];
	a[i]=a[j];
	a[j]=k;
	
}

void selectionsort ( int a[] , int n )
{
	int ind=0;
	int i=0;

	if(n>2)
	{
		while(i<n)
		{
			if(a[i]>=a[ind])
			ind=i;
			i++;
		}
		scambia(a, ind, n-1);
		selectionsort(a, n-1);
	}
	

}


int main (void)
{
	int a[]= {3,5,2,5,6,8,9,0,3,4,5,2};
	
	selectionsort(a, 12);
	stamp(a, 12);
	
}






