
//  Created by hgl on 2018/1/23.
//  Copyright © 2018年 hgl. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "custom.h"

int indegree[MAX_VEX_NUM];//用来存放顶点的入度
/*
 初始化AOE-网
 */
struct Graph init(void){
    struct Graph g;
    int i,j,q,z;
    char data1,data2;
    int locate(struct Graph g,char data);
    printf("请输入顶点数:");
    scanf("%d",&g.vexnum);
    printf("请输入弧数:");
    scanf("%d",&g.arcnum);
    for(i=0;i<g.vexnum;i++){
       // struct VNode v;
        printf("请输入第%d个顶点:",i+1);
        scanf(" %c",&g.verts[i].info);
        g.verts[i].firstarc=NULL;
        g.verts[i].ve=0;//初始化最早开始
    }
    for(j=0;j<g.arcnum;j++){
        struct ArcNode * a=(struct ArcNode *)malloc(sizeof(struct ArcNode));
        printf("请输入第%d条边的尾点:",j+1);
        scanf(" %c",&data1);
        printf("请输入第%d条边的头顶点:",j+1);
        scanf(" %c",&data2);
        printf("请输入这条弧的权值:");
        scanf("%d",&a->info);
        q=locate(g, data1);
        z=locate(g, data2);
        indegree[z]++;//计算该顶点的入度
        a->adjvex=z;
        a->nextarc=NULL;
        if(g.verts[q].firstarc==NULL){
            g.verts[q].firstarc=a;
        }else{
            a->nextarc=g.verts[q].firstarc;
            g.verts[q].firstarc=a;
        }
    }
    return g;
}

/*
 根据顶点信息查找顶点的位置
 */
int locate(struct Graph g,char data){
    int i;
    for(i=0;g.verts[i].info!=data;i++);
    return i;
}

/*
  拓扑排序
 */
struct sqstack tpcSort(struct Graph * g){
    int i,j,k,count=0;
    struct ArcNode * p;
    struct sqstack s;//这个栈的作用是存放入度为0的顶点，可以避免重复检测入度为0的顶点
    struct sqstack t;//这个栈的作用是存放拓扑有序序列的顶点
    struct ArcNode * getNextArc(struct ArcNode * p);
    initStack(&s);//初始化栈s
    initStack(&t);//初始化栈t
    for(i=0;i<g->vexnum;i++){
        if(indegree[i]==0) push(&s, i);//把入度为0的顶点放入栈中，需要找入度为0的顶点时可以直接去栈中取
    }
    while(!stackEmpty(&s)){
        j=pop(&s);//取出入度为0的顶点
        push(&t, j);//入度为0的顶点放到t中
       // printf("%c\t",g->verts[j].info);//把这个顶点拿出来打印出来 这个是打印出拓扑有序序列
        count++;//计算入度为0的顶点的个数
        for(p=g->verts[j].firstarc;p!=NULL;p=getNextArc(p)){
            k=p->adjvex;
            if(--indegree[k]<=0) push(&s, k);//把和该顶点相邻的顶点的入度都减去1，这样可以间接实现删除以该顶点为尾的弧的操作，如果其邻接顶点的入度为0，就加入到栈中
            if(g->verts[j].ve+p->info > g->verts[k].ve){//判断 顶点的最早开始时间是依赖前面的顶点 关键路径上的顶点依赖前面最长路径上的顶点
                g->verts[k].ve=g->verts[j].ve+p->info;
            }
        }
    }
    if(count<g->vexnum){//count其实就代表拓扑有序序列中的顶点的个数
        printf("该有向图有环");
        exit(1);//直接退出程序
    }
    destory(&s);
    return t;
}

/*
  求关键路径
 */
void CriticalPath(void){
    int i,j,k,dut,ee,el;
    struct ArcNode * p;
    struct ArcNode * getNextArc(struct ArcNode * p);
    struct Graph g=init();
    struct sqstack t=tpcSort(&g);//拓扑排序，返回存放拓扑有序序列的顶点的栈
    for(i=0;i<g.vexnum;i++){
        g.verts[i].vl=g.verts[g.vexnum-1].ve;
        //这里把所有顶点的最晚开始时间都赋值为汇点的最早开始时间（除了最后一个顶点外其他顶点的值也可以赋一个比较大的值，因为汇点的最早开始时间等于最晚开始时间，前面所有顶点都要依赖它，它的值不能错)
    }
    while(!stackEmpty(&t)){//取出来的顶点时逆拓扑的，因为计算最迟开始时间，前一个顶点依赖后一个顶点，所以要逆序计算
        i=pop(&t);//取出栈顶元素
        for(p=g.verts[i].firstarc;p!=NULL;p=getNextArc(p)){
            k=p->adjvex;
            dut=p->info;
            if(g.verts[k].vl-dut<g.verts[i].vl){
                g.verts[i].vl=g.verts[k].vl-dut;
            }
        }
    }
    for(j=0;j<g.vexnum;j++){//打印出最早开始时间和最晚开始时间相等的顶点
        for(p=g.verts[j].firstarc;p!=NULL;p=getNextArc(p)){
            k=p->adjvex;
            dut=p->info;
            ee=g.verts[j].ve;//该弧的最早开始时间
            el=g.verts[k].vl-dut;//该弧的最晚开始时间
            if(ee==el){
                printf("起点:%c,终点:%c,弧的权值:%d,最早开始时间:%d,最晚开始时间:%d\n",g.verts[j].info,g.verts[k].info,dut,ee,el);
            }
        }
    }
}

/*
  求下一条以该顶点为尾的弧
 */
struct ArcNode * getNextArc(struct ArcNode * p){
    return p->nextarc;
}






