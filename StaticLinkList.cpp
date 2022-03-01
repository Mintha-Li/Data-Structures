#include "main.cpp"
/* 线性表的静态链表存储结构 */
#define MAXSIZE 1000    /* 假设链表最大长度为1000 */
typedef struct
{
    ElemType data;
    int cur;    /* 游标(Cursor)，为0时表示无指向 */
}Componet,StaticLinkList[MAXSIZE];

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

/* 将下标为k的空间节点回收到备用链表 */
void Free_SLL(StaticLinkList space,int k)
{
    space[k].cur=space[0].cur;  /* 把第一个元素cur赋值给要删除的分量cur */
    space[0].cur=k;             /* 把要删除的分量下标赋值给第一个元素的cur */
}

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