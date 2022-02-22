# 数据结构(Data Structure)

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

#### 1.定义

* 数据域：存储数据
* 指针域：

