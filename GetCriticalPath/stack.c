//
//  stack.c
//
//  Created by zyq on 2018/1/28.
//  Copyright © 2018年 hgl. All rights reserved.
//

#include <stdio.h>
#include "custom.h"
#include <stdlib.h>

/*
 初始化栈
 */
void initStack(struct sqstack * s){
    s->base=(struct SNode *)malloc(sizeof(struct SNode));
    if(s->base==NULL){
        printf("创建栈失败");
        exit(1);
    }
    s->top=s->base;
    s->base->next=NULL;
}

/*
 元素入栈
 */
void push(struct sqstack * s,int e){
    struct SNode * p;
    //链式栈就不存在栈满的情况
    if(s->base==NULL){//假如栈不存在
        printf("栈不存在");
        return;
    }
    p=(struct SNode *)malloc(sizeof(struct SNode));
    if(p==NULL){
        printf("元素入栈失败");
        return;
    }
    s->top->data=e;
    p->next=s->top;
    s->top=p;
}

/*
 删除栈顶的元素
 */
int pop(struct sqstack * s){
    int e;
    struct SNode * p;
    if(s->top==s->base){//空栈的标志
        return -1;
    }else{
        p=s->top;
        s->top=p->next;
        e=s->top->data;
        free(p);
    }
    return e;
}

/*
 销毁栈
 */
void destory(struct sqstack * s){
    struct SNode * p;
    if(s->base==s->base){
        p=s->base;
        s->base=s->top=NULL;
        free(p);
        return;
    }
    while(s->base!=s->top){
        p=s->top;
        s->top=p->next;
        free(p);
    }
    p=s->base;
    s->base=s->top=NULL;
    free(p);
}

/*
 判断栈是否为空
 */
int stackEmpty(struct sqstack * s){
    if(s->base==s->top){
        return 1;
    }else{
        return 0;
    }
}






