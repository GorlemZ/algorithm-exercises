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

void merge(int a[], int c[], int sx, int midsx, int dx)
{
	
	int k=0;
	int i=midsx+1;
	int j=0;
	while(sx<midsx+1 && i<dx)
	{
		if(a[sx]<a[i])
		{
			c[k]=a[sx];
			sx++;	
		}
		else
		{
			c[k]=a[i];
			i++;			
		}
		k++;
	}
	while(sx<midsx+1)
	{
		c[k]=a[sx];
		sx++;
		k++;
	}
	while(i<dx)
	{
		c[k]=a[i];
		i++;
		k++;
	}
	
}

void mergesort ( int a[] , int sx , int dx )
{
	int q;
	int c[dx+1];
	int i;
	if(sx<dx)
	{
		q=(sx+dx)/2;
		mergesort(a, sx, q);
		mergesort(a, q+1, dx);
		merge(a, c, sx, q, dx);
	}
	
	for(i=0; i<dx; i++)
	{
		a[i]=c[i];	
	}
}


int main (void)
{
	int a[]= {4,6,3,6,8,9,4,33,3,5,6,6};
	int c[6];
	
	mergesort(a, 0, 12);
	
	stamp(a, 12);
	
}

