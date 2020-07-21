//回溯法2--用回溯法生成{1,2,3,4}的所有排列
import java.util.Arrays;
public class RC
{ 
    static int count=0;
    public static void main(String args[])
    {
      int a[]={1,2,3,4};
      p(a,0);
      System.out.println(count);
   }
    public static void p(int a[],int b)
    {
       if(b>=a.length){
         count++;
        System.out.println(java.util.Arrays.toString(a));
       } 
       for(int i=b;i<a.length;i++)
       {//从for循环中找出未标记过的一个数，把他标记了，再把剩下未标记的数去递归，交给子方法去做。如果都选完了，那么输出就可以了。
	 if(!used(a,b,i))
	 continue;
	 {//两个数字，进行交换。
	   int k=a[b];
	   a[b]=a[i];
	   a[i]=k;
          }
	   p(a,b+1);//利用递归进行下一个数的交换
	   {
	     int k=a[b];
	     a[b]=a[i];
	     a[i]=k;
          }
       }
    }
 /*排除重复情况的组合*/
    public static boolean used(int a[],int b,int i)
      {
        for(int j=b;j<i;j++)
         {
           if(a[i]==a[j])
           {
	      return false;
	    }
          }
	     return true;
     }
 }
