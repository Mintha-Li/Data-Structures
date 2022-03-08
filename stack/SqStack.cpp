#include "main.h"

#define MAXSIZE 100     /* 顺序存储结构最大长度暂定100 */

typedef struct 
{
    SElemType data[MAXSIZE];
    int top;    /* 用作栈顶指针 */
}SqStack;

/* 插入新元素成为栈顶元素 */
Status Push(SqStack *S,ElemType e)
{
    if(S->top == MAXSIZE-1)     /* 栈满 */
    {
        return ERROR;
    };
    S->top++;   /* 栈顶指针+1 */
    S->data[S->top]=e;  /* 将新元素赋值给栈顶空间 */
    return OK;
}

/* 若栈不空，则删除栈顶元素，用e返回其值，返回OK，否则返回ERROR */
Status Pop(SqStack *S,ElemType *e)
{
    if(S->top==-1)
        return ERROR;
    *e=S->data[S->top];     /* 将要删除的栈顶元素赋值给e */
    S->top--;               /* 栈顶指针-1 */
    return OK;
}
