//
//  Huffman.h
//  huffman
//
//  Created by bondsam on 2018/5/9.
//  Copyright © 2018年 bondsam. All rights reserved.
//

#ifndef Huffman_h
#define Huffman_h
#include <iostream>
#include <iomanip>
#define N 10
using namespace std;
struct HNode
{
    int weight;
    int parent;
    int lchild;
    int rchild;
};
struct HCode {
    char data;
    char code[100];
};
class huffman
{
private:
    
    
    char leaf[1024];  //记录叶节点
    int a[1024];  //记录出现次数（权值）
public:
    char str[1024];  //记录字符
    HNode*HTree;
    HCode*HCodeTable;
    int n;  //叶节点数
    void init();
    void CreateTree();
    void Min(int &x,int &y,int s,int e);
    void CreateTable();
    void Encode(char *d);
    void Decode(char *s,char *d);
    void Print(int i,int m);
    void Reverse(char *c);
    ~huffman();
};
void huffman::init()

{
    int ch = -1;
    ch = cin.get();
    if (ch==-1) {
        throw "error";
    }
    int temp[1024]={0};//暂时储存字符
    int i=0;
    while ((ch!='\n')&&(ch!='\r')&&(ch!='\0')) {
        temp[ch]++;
        str[i++]=ch;
        ch=cin.get();
    }
    str[i]='\0';
    //整理
    n=0;
    for (int i =0; i<1024; i++) {
        if (temp[i]!=0) {
            leaf[n]=(char)i;
            a[n]=temp[i];
            n++;
        }
    }
    
}
void huffman::CreateTree()
{
    if (n>=1) {
        HTree=new HNode[2*n-1];//有2n-1个结点
    }
    //HTree=new HNode[2*n-1];//有2n-1个结点
    for (int i=0; i<n; i++) {
        HTree[i].weight=a[i];
        HTree[i].parent=HTree[i].lchild=HTree[i].rchild=-1;//初始化
    }
    int x,y;
    for (int  i =n; i<2*n-1; i++) {
        Min(x, y, 0, i);
        HTree[x].parent=HTree[y].parent=i;
        HTree[i].weight=HTree[x].weight+HTree[y].weight;
        HTree[i].lchild=x;
        HTree[i].rchild=y;
        HTree[i].parent=-1;
        
        
    }
}
void huffman::Min(int &x, int &y, int s, int e)
{
    int i;
    for (i=s; i<=e; i++) {
        if (HTree[i].parent==-1) {
            x=y=i;break;
        }
    }
    for(;i<e;i++)
    {
        if (HTree[i].parent==-1) {
            if (HTree[i].weight<HTree[x].weight) {
                y=x;x=i;
            }
            else if((x==y)||(HTree[i].weight<HTree[y].weight))
                y=i;
        }
        
    }
}
void huffman::CreateTable()
{
    HCodeTable=new HCode[n];
    for (int i =0; i<n; i++) {
        HCodeTable[i].data=leaf[i];
        int child=i;
        int parent=HTree[i].parent;
        int k=0;
        while (parent!=-1) {
            if (child==HTree[parent].lchild) {
                HCodeTable[i].code[k]='0';
            }
            else {
                HCodeTable[i].code[k]='1';
            }
            k++;
            child=parent;
            parent=HTree[child].parent;
        }
        HCodeTable[i].code[k]='\0';//标记结束
        Reverse(HCodeTable[i].code);
        
    }
}
void huffman::Encode(char *d)
{
    char *s=str;
    while (*s!='\0') {
        for (int i =0; i<n; i++) {
            if (*s==HCodeTable[i].data) {
                strcat(d, HCodeTable[i].code);
                break;
            }
        }
        s++;
    }
}
void huffman::Print(int i,int m)
{
    if(i>=0)
    {if (HTree[i].lchild==-1) {
        cout<<setfill(' ')<<setw(m+1)<<leaf[i]<<setfill('-')<<setw(N-m)<<'\n';
    }
    else
    {
        cout<<setfill(' ')<<setw(m+1)<<HTree[i].weight<<setfill('-')<<setw(N-m)<<'\n';
        Print(HTree[i].lchild,m+1);
        Print(HTree[i].rchild,m+1);
    }
    }
}
void huffman::Reverse(char *c)
{
    int count=0;
    char k;
    while (c[count+1]!=0) {
        count++;
        
    }
    for (int i =0; i<=count/2; i++) {
        k=c[i];
        c[i]=c[count-i];
        c[count-i]=k;
    }
    
}
void huffman::Decode(char *s,char *d)
{
    while (*s!='\0') {
        int parent = 2*n-2;
        while (HTree[parent].lchild!=-1) {
            if (*s=='0') {
                parent= HTree[parent].lchild;
            }
            else
                parent=HTree[parent].rchild;
            s++;
        }
        *d=HCodeTable[parent].data;
        d++;
    }
}

huffman::~huffman()
{
    delete []HTree;
    delete []HCodeTable;
}
#endif /* Huffman_h */
