#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;     /*Status是函数类型，其值是函数结果状态代码，如OK等*/
typedef int ElemType;	/*ElemType 类型根据实际情况而定，这里假定为int*/
typedef int SElemType;  /* SElemType类型根据实际情况而定，这里假设为int */

// /* 线性表的双向链表存储结构 */
// typedef struct DulNode
// {
//     ElemType data;
//     struct DulNode *prior;  /* 直接前驱指针 */
//     struct DulNode *next;   /* 直接后继指针 */
// }DulNode,*DulLinkList;