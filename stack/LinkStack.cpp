#include "main.h"

typedef struct StackNode
{
    SElemType data;
    struct StackNode *next;
}StackNode,*LinkStackPtr;

typedef struct LinkStack
{
    LinkStackPtr top;
    int count;
}LinkStack;

/* 插入元素e成为栈顶元素 */
Status Push(LinkStack *S,SElemType e)
{
    LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
    s->data=e;
    s->next=S->top; /* 把当前栈顶元素的赋值给新结点的直接后继 */
    S->top=s;       /* 将新结点s赋值给栈顶指针 */
    S->count++;
    return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(LinkStack *S,SElemType *e)
{
    LinkStackPtr p;
    if(StackEmpty(*S))
        return ERROR;
    *e=S->top->data;
    p=S->top;               /* 将栈顶结点赋值给p */
    S->top=S->top->next;    /* 使得栈顶指针下移一位，指向后一结点 */
    free(p);                /* 释放结点p */
    S->count--;
    return OK;
}


Status StackEmpty(LinkStack S)
{
    if(S.count==-1)
        return OK;
    return ERROR;
}