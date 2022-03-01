# 数据结构(Data Structures)

---

## 第3章 线性表

### 3.1  开场白

### 3.2  线性表的定义

> **线性表(List)：零个或多个数据元素的有限序列**

在较复杂的线性表中，一个数据元素可以由若干个数据项组成。

### 3.3  线性表的抽象数据类型

```markdown
ADT 线性表(List)
Data
	线性表的数据结构对象集合为{a1,a2,...,an},每一个元素的类型均为DataType。其中，除了第一个元素a1外，每一个元素有且仅有一个直接前驱元素，除了最后一个元素an外，每一个元素有且仅有一个直接后继元素。数据元素之间的关系是一对一关系的关系。
Operation
	InitList(*L):	初始化操作，建立一个空的线性表L。
	ListEmpty(L):	若线性表为空，返回true，否则返回false
	ClearList(*L):	将线性表清空
	GetElem(L,i,*e):	将线性表L中第i个位置的元素值返回给e。
	LocateElem(L,e):	在线性表L中查找与给定值e相等的元素，如果查找成功，返回该元素在表中序号表示成功；否则返回0表示失败。
	ListInsert(*L,i,e):	在线性表L中的第i个位置插入新元素e。
	ListDelete(*L,i,*e):	删除线性表L中第i个位置元素，并用e返回其值。
	ListLength:	返回线性表L的元素个数。
endADT
```

### 3.4  线性表的顺序存储结构

#### 1.定义

> **线性表的顺序存储结构，指的是用一段地址连续的存储单元依次存储线性表的数据元素。**

#### 2.顺序存储方法

C语言中，我们可以用**一维数组来实现顺序存储结构**

代码如下

```c
#define MAXSIZE 20	/*存储空间初始分配量*/
typedef int ElemType;	/*ElemType 类型根据实际情况而定，这里假定为int*/
typedef struct{
    ElemType data[MAXSIZE];	/*数组存储数据元素，最大值MAXSIZE*/
    int length;	/*线性表当前长度*/
}SqList;
```

描述顺序存储结构需要三个属性：

* 存储空间的起始位置：数组data，它的存储位置就是存储空间的存储位置

* 线性表的最大存储容量：数组长度MAXSIZE

* 线性表当前长度：length

#### 3.数组长度与线性表长度区别

线性表的长度是线性表中数据元素的个数，随着线性表插入和删除操作的进行，这个量是变化的。在任意时刻，线性表的长度应该小于等于数组的长度。

#### 4.地址计算方法

> **存储器中每个存储单元都有自己的编号，这个编号叫做地址**

  第i+1个数据元素的存储位置和第i个数据元素的存储位置满足以下关系（LOC表示获得存储位置的函数,c表示占用的存储单元空间）

> LOC(a~i+1~)=LOC(a~i~)+c

所以对于第i个数据元素a~i~的存储位置可以由a~1~推算得出

> LOC(a~i~)=LOC(a~1~)+(i-1)*c

显然，其存取时间性能为O(1)。我们通常把具有这一特点的存储结构称为随机存储结构。

### 3.5 顺序存储结构的插入与删除

#### 1.获得元素操作

```c
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
/*Status是函数类型，其值是函数结果状态代码，如OK等*/
/*初始条件：顺序线性表L已存在，1≤i≤ListLength(L)*/
/*操作结果：用e返回L中第i个数据元素的值*/
Status GetElem(SqList L,int i,ElemType *e)
{
    if(L.length==0||i<1||i>L.length)
        return ERROR;
    *e = L.data[i-1];
    return OK;
}
```

#### 2.插入操作

思路：

* 如果插入位置不合理，抛出异常
* 如果线性表长度大于等于数组长度，则抛出异常或动态增加容量；
* 从最后一个元素开始向前开始遍历到第i个位置，分别将它们都向后移动一位
* 将要插入的元素填入位置i
* 表长+1

```c
/*初始条件：顺序线性表L已存在，1≤i≤ListLength(L)*/
/*操作结果：在L中第i个位置之前插入新的数据元素e，L的长度+1*/
Status ListInsert(SqList *L,int i,ElemType e)
{
    int k;
    if(L->length==MAXSIZE)  /*顺序表已满*/
        return ERROR;
    if(i<1||i>L->length+1)  /*当i不在范围内时*/
        return ERROR;
    if(i<=L->length)    /*若插入数据位置不在表尾*/
    {
        for(k=L->length-1;k>=i-1;k--)   /*将要插入位置后的数据元素向后移动一位*/
            L->data[k+1]=L->data[k];
    }
    L->data[i-1]=e; /*将新元素插入*/
    L->length++;
    return OK;
}
```

#### 3.删除操作

思路：

* 如果删除位置不合理，抛出异常；
* 取出删除元素
* 从删除元素位置开始遍历到最后一个元素位置，分别将它们都向前移动一个位置
* 表长-1

```c
/*初始条件：顺序线性表L已存在，1≤i≤ListLength(L)*/
/*操作结果：删除L的第i个位置的元素，并用e返回其值，L的长度-1*/
Status ListDelete(SqList *L,int i,ElemType *e)
{
    int k;
    if(L->length==0)
        return ERROR;
    if(i<1||i>L->length)
        return ERROR;
    *e=L->data[i-1];
    if(i<L->length)
    {
        for(k=i;k<L->length;k++)
            L->data[k-1]=L->data[k];
    }
    L->length--;
    return OK;
}
```

可以看出在插入和删除操作时，平均时间复杂度还是O(n)

### 3.6 线性表的链式存储结构

#### 1&2&3.概念

* 数据域：存储数据
* 指针域：存储直接后继位置
* 结点（Node）：数据域与指针域组成的元素ai的存储映像
* 单链表：n个结点连接成一个链表，即为线性表的链式存储结构，因为此链表中每个结点只包含一个指针域，所以叫做单链表
* 头指针：链表中第一个结点的存储位置叫做头指针
* 头结点：有时为了方便对链表操作，会在单链表第一个结点前附设一个结点，称为头结点

无论链表是否为空，头指针均不为空。头指针是链表的必要元素。

#### 4.代码描述

```c
/*线性表的单链表存储结构*/
typedef struct Node
{
    ElemType data;
    struct Node *next;
    
}Node;
typedef struct Node *LinkList;  /*定义LinkList*/

```

### 3.7 单链表的读取

算法思路：

1. 声明一个指针p指向链表的第一个结点，初始化j从1开始；
2. 当j<i时，就遍历链表，让p的指针向后移动，不断指向下一结点，j累加1；
3. 若到链表尾p为空，则说明第i个结点不存在；
4. 若查找成功，返回结点p的数据。

```c
/*初始条件：顺序线性表L已存在，1≤i≤ListLength(L)*/
/*操作结果：用e返回L中第i个数据元素的值*/
Status GetElem(LinkList L,int i,ElemType *e)
{
    int j;
    LinkList p; /*声明一个指针p*/
    p=L->next;  /*让指针p指向链表的第一个结点*/
    j=1;    /*j为计数器*/
    while(p&&j<i)   /*p不为空并且j还没有等于i时，循环继续*/
    {
        p=p->next;  /*让p指向下一个结点*/
        ++j;
    }
    if(!p||j>i)
        return ERROR;   /*第一个结点不存在*/
    *e=p->data; /*取第i个结点的数据*/
    return OK;
}
```

### 3.8 单链表的插入与删除

#### 插入

算法：

1. 声明一个指针p指向链表头结点，初始化j从1开始；
2. 当j<i时，就遍历链表，让p的指针往后移动，不断指向下一结点，j累加1；
3. 若到链表末尾p为空，则说明第i个结点不存在；
4. 否则查找成功，在系统中生成一个空结点s；
5. 将数据元素e赋值给s->data；
6. 单链表的插入标准语句`s->next=p->next;p->next=s;`
7. 返回成功

```c
/*初始条件：顺序线性表L已存在，1≤i≤ListLength(L)*/
/*操作结果：在L中第i个结点位置之前插入新的数据元素e，L的长度+1*/
Status ListInsert(LinkList *L,int i,ElemType e)
{
    int j;
    LinkList p,s;
    p=*L;
    j=1;
    while(p&&j<i)   /*寻找第i-1个结点*/
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i)
        return ERROR;   /*第i个结点不存在*/
    s=(LinkList)malloc(sizeof(Node));   /*生成新结点*/
    s->data=e;
    s->next=p->next;    /*将p的后继结点赋值给s的后继*/
    p->next=s;  /*将s赋值给p的后继*/
    return OK;
}
```

#### 删除

算法：

1. 声明一个指针p指向链表头指针，初始化j从1开始
2. 当j<i时就遍历链表，让p的指针向后移动，不断指向下一个结点，j累加1
3. 若到链表末尾p为空，则说明第i个结点不存在
4. 否则查找成功，将欲删除的结点p->next赋值给q
5. 单链表的删除标准语句`p->next=q->next;`
6. 将结点q中的数据赋值给e，作为返回
7. 释放q结点
8. 返回成功

```c
/*初始条件：顺序线性表L已存在，1≤i≤ListLength(L)*/
/*操作结果：删除L中第i个结点，并用e返回其值位置L的长度-1*/
Status ListDelete(LinkList *L,int i,ElemType *e)
{
    int j;
    LinkList p,q;
    p=*L;
    j=1;
    while (p->next && j<i) /* 遍历寻找第i-1个结点 */
    {
        p-p->next;
        ++j;
    }
    if(!(p->next)||j>i)
        return ERROR;   /* 第i个结点不存在 */
    q=p->next;
    p->next=q->next;    /* 将q的后继赋值给p的后继 */
    *e=q->data;         /* 将q结点中的数据给e */
    free(q);    /* 让系统回收此结点，释放内存 */
    return OK;
}
```

显然，对于删除或者插入操作数据越频繁的操作，单链表的效率优势就越明显

### 3.9 单链表的整表创建

思路：

1. 声明一指针p和计数器变量i；
2. 初始化一空链表L
3. 让L的头结点指针指向NULL，即建立一个带头结点的单链表
4. 循环
   * 生成一个新结点赋值给p
   * 随机生成一个数字赋值给p的数值域p->data;
   * 将p插入到头结点与前一新节点之间

实现代码：

头插法：（即始终让头结点在第一的位置）

```c
/* 随机产生n个元素的值，建立带表头结点的单链(头插法) */
void CreateListHead(LinkList *L,int n){
    LinkList p;
    int i;
    srand(time(0)); /* 初始化随机数种子 */
    *L=(LinkList)malloc(sizeof(Node));
    (*L)->next=NULL;    /* 先建立一个带头结点的单链表 */
    for(i=0;i<n;i++)
    {
        p=(LinkList)malloc(sizeof(Node));   /* 生成新结点 */
        p->data=rand()%100+1;   /* 随机生成100以内数字 */
        p->next=(*L)->next;
        (*L)->next=p;   /* 插入到表头 */
    }
}
```

尾插法：（每次让新结点都插在终端结点的后面）

```c
/* 随机产生n个元素的值，建立带头结点的单链线性表L(尾插法) */
void CreateListTail(LinkList *L,int n){
    LinkList r,p;
    int i;
    srand(time(0)); /* 初始化随机数种子 */
    *L=(LinkList)malloc(sizeof(Node));  /* 为整个线性表 */
    r=*L;   /* r为指向尾部的结点 */
    for(i=0;i<n;i++)
    {
        p=(Node *)malloc(sizeof(Node)); /* 生成新结点 */ 
        p->data=rand()%100+1;   /* 随机生成100以内数字 */
        r->next=p;  /* 将表尾终端结点的指针指向新结点 */
        r=p;    /* 将当前的新结点定义为表尾终端结点 */
    }
    r->next=NULL;   /* 表示当前链表结束 */
}
```

### 3.10单链表的整表删除

算法思路

1. 声明一结点p和q；
2. 将第一个结点赋值给p；
3. 循环
   * 将下一个结点赋值给q
   * 释放p；
   * 将q赋值给p

实现代码：

```c
/* 初始条件：顺序线性表L已经存在 */
/* 操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{
    LinkList p,q;
    p=(*L)->next;   /* p指向第一个结点 */
    while(p)    /* 没到表尾 */
    {   
        q=p->next;  
        free(p);
        p=q;
    }
    (*L)->next=NULL;    /* 头结点指针域为空 */
    return OK;
}
```

### 3.11 单链表结构与顺序存储结构优缺点

1. 存储分配方式
2. 时间性能
3. 空间性能

### 3.12  静态链表

> **用数组描述的链表叫做静态链表（游标实现法）**

```c
/* 线性表的静态链表存储结构 */
#define MAXSIZE 1000    /* 假设链表最大长度为1000 */
typedef struct
{
    ElemType data;
    int cur;    /* 游标(Cursor)，为0时表示无指向 */
}Componet,StaticLinkList[MAXSIZE];
```

数组第一个和最后一个元素作为特殊元素处理，不存数据

第一个元素（下标为0的元素的cur存放备用链表第一个结点的下标）

最后一个元素的cur存放第一个有数值元素的结点的下标，相当于单链表中头结点的作用，当链表为空时，则为0

通常把未被使用的数组元素称为备用链表

* 初始化数组状态

```c
/* 将一组数组中space中各分量链成一备用链表 */
/* space[0].cur为头指针，"0"表示空指针 */
Status InitList(StaticLinkList space)
{
    int i;
    for(i=0;i<MAXSIZE-1;i++){
        space[i].cur=i+1;
    }
    space[MAXSIZE-1].cur=0; /* 目前链表为空，最后一个元素的cur为0 */
    return OK;
}
```

#### 插入操作

结点申请操作

```c
/* 若备用空间链表非空，则返回分配的结点下标，否则返回0 */
int Malloc_SLL(StaticLinkList space)
{
    int i=space[0].cur; /* 当前数组的第一个元素的cur存的值， */
                        /* 就是要返回的第一个备用空闲的下标 */
    if(space[0].cur)
        space[0].cur=space[i].cur;  /* 由于要拿出一个分量来使用了，所以我们 */
                                    /* 就得把它的下一个分量拿来做备用 */
    return i;    
}
```

实现

```c
/* 在L中第i个元素之前插入新的数据元素e */
Status ListInsert(StaticLinkList L,int i,ElemType e)
{
    int j,k,l;
    k=MAXSIZE-1;    /* 注意k首先是最后一个元素的下标 */
    if(i<1||i>ListLength(L)+1)
        return ERROR;
    j=Malloc_SLL(L);    /* 获得空闲分量的下标 */
    if(j)
    {
        L[j].data=e;    /* 将数值赋值给此分量的data */
        for(l=1;l<=i-1;l++) /* 找到第i个元素之前的位置 */
            k=L[k].cur;
        L[j].cur=L[k].cur;  /* 把第i个元素之前的cur值赋值给新元素的cur */
        L[k].cur=j; /* 把新元素的下标赋值给第i个元素之前元素的cur */
        return OK;
    }
    return ERROR;
}
```

#### 删除操作

释放节点函数

```c
/* 将下标为k的空间节点回收到备用链表 */
void Free_SLL(StaticLinkList space,int k)
{
    space[k].cur=space[0].cur;  /* 把第一个元素cur赋值给要删除的分量cur */
    space[0].cur=k;             /* 把要删除的分量下标赋值给第一个元素的cur */
}
```

实现

```c
/* 删除在L中的第i个数据元素e */
Status ListDelete(StaticLinkList L,int i)
{
    int j,k;
    if(i<1||i>ListLength(L))
        return ERROR;
    k=MAXSIZE-1;
    for(j=1;j<i-1;j++)
        k=L[k].cur;
    j=L[k].cur;
    L[k].cur=L[j].cur;
    Free_SLL(L,j);
    return OK;
}
```

* 数据元素个数函数

```c
/* 初始条件：SLL L已经存在 */
/* 操作结果：返回L中的数据元素个数 */
int ListLength(StaticLinkList L)
{
    int j=0;
    int i=L[MAXSIZE-1].cur;
    while(i)
    {
        i=L[i].cur;
        j++;
    }
    return j;
}
```

#### 优缺点比较

优点：

在插入和删除操作时，只需要修改游标，从而避免了顺序存储结构中插入和删除需要大量移动数据

缺点：

没有解决连续存储分配带来的表长难以确定的问题

失去了顺序存储结构随机存取的特性

### 3.13 循环链表

> 将单链表中终端结点的指针端由空指针改为指向头结点，就使整个单链表形成一个环，这种首尾相接的单链表称为单循环链表，简称循环链表

使用循环链表可以从一个结点出发，访问到全部结点

循环的结束条件p->next不等于头节点

为了使访问头结点和尾结点的时间均为O(1)，可以使用尾指针rear来表示循环链表

举例：合并两个循环链表rearA，rearB

```c
p=rearA->next;	/*保存A表的头结点*/
rearA->next=rearB->next->next;	/*将本是指向B表的第一个结点赋值给rearA->next*/
q=rearB->next;	
rearB->next=p;	/*将原本A表的头结点赋值给rearB->next*/
free(q);	/*释放q*/
```

### 3.14双向链表

> **双向链表(double linked list)是在单链表中的每个结点再设置一个指向其前驱结点的指针域**

```c
/* 线性表的双向链表存储结构 */
typedef struct DulNode
{
    ElemType data;
    struct DulNode *prior;  /* 直接前驱指针 */
    struct DulNode *next;   /* 直接后继指针 */
}DulNode,*DulLinkList;
```

显然有以下结论

`p->next->prior=p->prior->next=p`

双向链表是从单链表中扩展出的，其许多操作与单链表类似

但插入和删除时要搞定两个指针(代码略)

即插入时先搞定要插入元素的前驱和后继，再搞定后结点的前驱，最后解决前结点的后继

删除操作应先搞定要删除元素前后的指针指向，再释放

### 3.15 总结回顾

线性表：

| 顺序存储结构 | 链式存储结构                      |
| ------------ | --------------------------------- |
|              | 单链表;静态链表;循环链表;双向链表 |



