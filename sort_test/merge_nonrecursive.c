#include <stdio.h>
void Merge(int arr[],int low,int mid,int high)
{
	int i=low,j=mid+1,k=0;
	int temp[high-low+1];
	while(i<=mid&&j<=high)
	{
		if(arr[i]<=arr[j])
			temp[k++]=arr[i++];
		else
			temp[k++]=arr[j++];
	}
	while(i<=mid) temp[k++]=arr[i++];
	while(j<=high) temp[k++]=arr[j++];
	for(i=low,k=0;i<=high;i++,k++)
		arr[i]=temp[k];
}

void MergeSort(int arr[],int n)
{
	int size=1,low,mid,high;
	while(size<=n-1)
	{
		low=0;
		while(low+size<=n-1)
		{
			mid=low+size-1;
			high=mid+size;
			if(high>n-1)
				high=n-1;
			Merge(arr,low,mid,high);
			low=high+1;
		}
		size*=2;
	}
}

int main(void)
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int i;
	MergeSort(a, sizeof(a) / sizeof(*a));//参数和递归略不同，n代表数组中元素个数，即数组最大下标是n-1
	//merge_sort(a, sizeof(a) / sizeof(*a));
	for (i = 0; i < sizeof(a) / sizeof(*a); i++) {
		fprintf(stdout, "a[%d]:%d\n", i, a[i]);
	}
	return 0;
}
