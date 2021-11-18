//
// Created by 丁程 on 2021/6/30.
//

#ifndef SOFTWARE_NODE_H
#define SOFTWARE_NODE_H
#include <string>
#include <vector>
using namespace std;
struct node{
    int type; //结点文本类型：规定纯文本为0，段落为1，斜体为2，粗体为3，
    // 删除线为4，下划线为5，标题为61-66，无序列表为7，有序列表为8,列表项为9
    //图片为10，超链接为11,行内代码为12,块代码为13.
    string content;             //结点文本内容：
    vector<struct node*> child;        //子结点
    int level;      //管理列表嵌套层级的数
};


#endif //SOFTWARE_NODE_H
