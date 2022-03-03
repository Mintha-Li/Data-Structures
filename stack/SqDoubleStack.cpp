#include "main.h"

#define MAXSIZE 100     /* 顺序存储结构最大长度暂定100 */

/* 两栈共享空间结构 */
typedef struct 
{
    SElemType data[MAXSIZE];
    int top1;   /* 栈1栈顶指针 */
    int top2;   /* 栈2栈顶指针 */
}SqDoubleStack;

/* 插入元素e成为新的栈顶元素 */
Status Push(SqDoubleStack *S,SElemType e,int stackNumber)
{
    if(S->top1+1==S->top2)  /* 栈已满，不能再push元素了 */
        return ERROR;
    if(stackNumber==1)          /* 栈1有元素进栈 */
        S->data[++S->top1]=e;   /* 若栈1则先top1+1后给数组赋值 */
    else if(stackNumber==2)     /* 栈2有元素进栈 */
        S->data[--S->top2]=e;   /* 若站2则先top2-1后给数组赋值 */
    return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR */
Status Pop(SqDoubleStack *S,SElemType *e,int stackNumber)
{
    if (stackNumber==1)
    {
        if(S->top1==-1)         /* 说明栈1是空栈，溢出 */
            return ERROR;
        *e=S->data[S->top1--];  /* 将栈1的栈顶元素出栈 */
    }
    else if(stackNumber==2)
    {
        if(S->top2==MAXSIZE)    /* 说明栈2是空栈，溢出 */
            return ERROR;
        *e=S->data[S->top2++];  /* 将栈2的栈顶元素出栈 */
    }
    return OK;
}