//
//  custom.h
//
//  Created by hgl on 2018/1/28.
//  Copyright © 2018年 hgl. All rights reserved.
//

#ifndef custom_h
#define custom_h
#define MAX_VEX_NUM 20  //顶点的最大数量
struct ArcNode{ //邻接表结构 边结构
    int adjvex;//该弧所指向的顶点的位置,对有向图来说就是该弧的头顶点
    struct ArcNode * nextarc;//指向下一条弧的指针
    int info;//该弧的权值
};
struct VNode{//邻接表结构 顶点结构
    char info;//顶点的相关信息
    struct ArcNode * firstarc;//指向第一条依附于该顶点的弧的指针，其实就是以该顶点为尾的弧
    int ve;//最早开始
    int vl;//最晚开始
};
struct Graph{//邻接表结构 图结构
    struct VNode verts[MAX_VEX_NUM];//存储顶点用数组
    int vexnum;//当前顶点的数量
    int arcnum;//当前边的数量
};
struct SNode{//栈中的元素结点
    int data;//存放图的顶点的位置
    struct SNode * next;//下一个元素
};
struct sqstack{
    struct SNode * base;//在栈构造之前和销毁之后，base的值为NULL
    struct SNode * top;//栈顶指针
};
void initStack(struct sqstack * s);
void push(struct sqstack * s,int e);
int pop(struct sqstack * s);
void destory(struct sqstack * s);
int stackEmpty(struct sqstack * s);
struct Graph init(void);
struct sqstack tpcSort(struct Graph * g);
void CriticalPath(void);
#endif /* custom_h */

