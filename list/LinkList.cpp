#include "main.h"

/*线性表的单链表存储结构*/
typedef struct Node
{
    ElemType data;
    struct Node *next;
    
}Node;
typedef struct Node *LinkList;  /*定义LinkList*/

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