/*140页第7题
对于一个包含100万随机数的数组排序，快速排序和插入排序*/
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

void Quick_sort(int a[],int first,int end) //快速排序 
{
	int temp,i,j;
	i=first;
	j=end;
	temp=a[i];    //初始化
	while(i<j)    //完成比temp大的在右边，比temp小的在左边
	{
		while((i<j)&&(a[j]>temp)) 
			j--;
		a[i]=a[j];
		while((i<j)&&(a[i]<=temp))
			i++;
		a[j]=a[i];
	}
	a[i]=temp;
	if((i-1)>first)	           //递归调用左半部数组部分
		Quick_sort(a,first,i-1);  //对左侧区域进行快速排序	
	if(end>(i+1))                //递归调用右半部数组部分
		Quick_sort(a,i+1,end);    //对右侧区域进行快速排序
}
int main()
{
    int i;
	int m[N];

    srand((unsigned)time(NULL));
	for(i=0;i<N;m[++i]=rand());
	Quick_sort(m,0,N);
	printf("从小到大排序后:\n");
	for(i=0;i<N;i++)
	{
	printf("    %d",m[i]);     //输出排序结果
	}
	printf( "\n" );
}

//下面的是插入排序

/*int insort(int s[], int n)    // 自定义函数 insort()
{
    int i,j;
    for(i=2;i<=n;i++)    //数组下标从2开始，s[0]做监视哨，s[1]一个数据无可比性
    {
        s[0]=s[i];    //给监视哨陚值
        j=i-1;    //确定要比较元素的最右边位黄
        while(s[0]<s[j])
        {
            s[j+1]=s[j];    //数据右移
            j--;    //产移向左边一个未比较的数
        }
        s[j+1]=s[0];    //在确定的位置插入s[i]
    }
    return 0;
}
int main()
{
    int a[N+1],i;    //定义数组及变量为基木整甩
    srand((unsigned)time(NULL));
	for(i=0;i<N;a[++i]=rand());
    insort(a,N);    //调用自定义函数 insort()
    printf("\n 插入数据排序后顺序：\n");
    for(i=1;i<=N;i++)
        printf("  %d",a[i]); //将排序后的数组输出
    printf("\n");
    return 0;
}*/

