//
//  main.cpp
//  huffman
//
//  Created by bondsam on 2018/5/8.
//  Copyright © 2018年 bondsam. All rights reserved.
//

#include "Huffman.h"
#include "iostream"
using namespace std;
int main()
{
    huffman HFCode;
    cout<<"请输入你要编码的字符串："<<endl;
    //HFCode.init();
    try {
        HFCode.init();
    } catch (char *msg) {
        cerr<<*msg<<endl;
        
    } 
    cout<<"创建Huffman树"<<endl;
    HFCode.CreateTree();
    HFCode.Print(2*HFCode.n-2, 1);
    
    cout<<"创建Huffman表"<<endl;
    HFCode.CreateTable();
    for (int i=0; i<HFCode.n; i++) {
        cout<<HFCode.HCodeTable[i].data<<'\t'<<HFCode.HCodeTable[i].code<<endl;
    }
    char d[1024]={0};
    HFCode.Encode(d);
    cout<<"编码结果"<<d<<endl;
    
    char e[1024]={0};
    HFCode.Decode(d, e);
    cout<<"解码结果"<<e<<endl;
    

    
    
    
    
    
}
