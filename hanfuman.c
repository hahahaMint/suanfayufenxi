//a写一个程序，为给定的英文文本构造一套哈夫曼编码，并对该文本编码。
  b写一个程序，对一段用哈夫曼编码的英文文本进行解码。
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAXLEN 100
typedef struct Huffmantree {char ch; /*键值*/
int weight,mark; /*weight为权值,mark为标志域*/
struct Huffmantree *parent,*lchild,*rchild,*next;}
Hftree,*linktree;/*整理输入的字符串，合并相同的项，并求出每个字符在数组中出现的次数 */
linktree tidycharacter(char character[])
{int i=0;
linktree tree,ptr,beforeptr,node; /*链式 ,tree为头结点,beforeptr为ptr的前一结点,node为新申请的结点*/
tree=(linktree)malloc(sizeof(Hftree));/*创建单链表的头结点*/
  if(!tree)return NULL;tree->next=NULL; /* 头结点为空,且后续结点为空*/
  for(i=0;character[i]!='\0'&&character[i]!='\n';i++) 
  { /*遍历直到字符串结束为止*/ptr=tree;
  beforeptr=tree;
  node=(linktree)malloc(sizeof(Hftree)); /*新申请结点node*/
  if(!node)return NULL;
  node->next=NULL;
  node->parent=NULL;
  node->lchild=NULL;
  node->rchild=NULL; /*置空*/
  node->mark=0;
  node->ch=character[i];
  node->weight=1;
  if(tree->next==NULL)tree->next=node; /*头结点的下一结点为空,连接node*/
  else 
  {
  ptr=tree->next;
  while(ptr&&ptr->ch!=node->ch) 
  {/*将指针移至链表尾*/
  ptr=ptr->next;
  beforeptr=beforeptr->next;/*后移*/
  }
  if(ptr&&ptr->ch==node->ch)
   {/*如果链表中某结点的字符与新结点的字符相同*//*将该结点的权加一*/
   ptr->weight=ptr->weight+1;
   free(node); /*释放node结点的存储空间*/
   }
   else 
   {/*新结点与表中结点不相同,将新结点插入链表后*/
   node->next=beforeptr->next;
   beforeptr->next=node; /*node连接在beforeptr之后*/
   }
   }
   }
   return tree;
   }
   
   /*将整理完的字符串按出现次数从小到大的顺序排列 */
   linktree taxisnode(linktree tree)
   {
   linktree head,ph,pt,beforeph; /*head为新链表的表头结点*/
   head=(linktree)malloc(sizeof(Hftree));/*创建新链表的头结点*/
   if(!head)return NULL;head->next=NULL; /*新结点的头结点为空,后续结点也为空*/
   ph=head;beforeph=head;while(tree->next) 
   {
   pt=tree->next;/*取被操作链表的首元结点*/
   tree->next=pt->next;
   pt->next=NULL; /*取出pt所指向的结点*/
   ph=head->next;
   beforeph=head;
   if(head->next==NULL)head->next=pt;/*创建当前操作链表首元结点*/
   else {while(ph&&ph->weight<pt->weight)
    {/*将被操作结点插入相应位置*/
	ph=ph->next;
	beforeph=beforeph->next;
	}
	pt->next=beforeph->next;
	beforeph->next=pt;
	}
	}
	free(tree);
	return head;
	}
	
/*用排完序的字符串建立霍夫曼树 */
linktree createHftree(linktree tree)
{
linktree p,q,newnode,beforep;
for(p=tree->next,q=p->next;p!=NULL&&q!=NULL;p=tree->next,q=p->next) 
{
tree->next=q->next;
q->next=NULL;
p->next=NULL;
newnode=(linktree)malloc(sizeof(Hftree));/*申请新结点作为霍夫曼树的中间结点*/
if(!newnode)return NULL;
newnode->next=NULL;
newnode->mark=0;
newnode->lchild=p;/*取链表头结点后的两个结点作为新结点的左、右儿子*/
newnode->rchild=q;
p->parent=newnode;
q->parent=newnode;
newnode->weight=p->weight+q->weight;
p=tree->next;
beforep=tree;
if(p!=NULL&&p->weight>=newnode->weight)
 {/*将新结点插入原链表的相应位置*/
 newnode->next=beforep->next;
 beforep->next=newnode;
 }
 else {
 while(p!=NULL&&p->weight<newnode->weight) 
 {
 p=p->next;beforep=beforep->next;
 }
 newnode->next=beforep->next;
 beforep->next=newnode;
 }
 }
 return (tree->next);
 }
 /*对哈夫曼树进行编码 */
 void Huffmancoding(linktree tree)
 {
 int index=0;
 char *code;
 linktree ptr=tree;
 code=(char *)malloc(10*sizeof(char));/*此数组用于统计霍夫曼编码*/
  printf("字符以及它的相应权数哈夫曼编码\n\n");
 if(ptr==NULL) 
 {
 printf("哈夫曼树是空的!\n");
 exit(0);
 }
 else 
 {
 while(ptr->lchild&&ptr->rchild&&ptr->mark==0)
  {
  while(ptr->lchild&&ptr->lchild->mark==0)
   {
   code[index++]='0';ptr=ptr->lchild;
   if(!ptr->lchild&&!ptr->rchild) 
   {
   ptr->mark=1;code[index]='\0';
   printf("\tw[%c]=%d\t\t\t",ptr->ch,ptr->weight);
   for(index=0;code[index]!='\0';index++)printf("%c",code[index]);
   printf("\n");ptr=tree;index=0;
   }
   }
   if(ptr->rchild&&ptr->rchild->mark==0) 
   {
   ptr=ptr->rchild;
   code[index++]='1';
   }
   if(!ptr->lchild&&!ptr->rchild) 
   {
   ptr->mark=1;
   code[index++]='\0';
   printf("\tw[%c]=%d\t\t\t",ptr->ch,ptr->weight);
   for(index=0;code[index]!='\0';index++)
   printf("%c",code[index]);
   printf("\n");ptr=tree;index=0;
   }
   if(ptr->lchild->mark==1&&ptr->rchild->mark==1)
   {
   ptr->mark=1;ptr=tree;index=0;
   }
   }
   }
   printf("\n");free(code);
   }	
void main()
{ 
int n;
char character[MAXLEN],code[MAXLEN];
linktree temp,ht,htree,ptr=NULL;
printf("编码:\n请输入字符串:\n\n");
scanf("%s",character);
printf("\n");
temp=tidycharacter(character);
ht=taxisnode(temp);
htree=createHftree(ht);
Huffmancoding(htree);
}
