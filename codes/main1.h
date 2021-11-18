//
// Created by 丁程 on 2021/6/30.
//

#ifndef SOFTWARE_MAIN1_H
#define SOFTWARE_MAIN1_H
#include <string>
#include "node.h"
#include <iostream>
#include <ios>
#include <fstream>
#include <vector>
using namespace std;


    node* input(string filename);                     //根据文件名打开文件并读取文本
    node* dfs(node* root);               //用于对文本树进行深度优先搜索的函数
    void output(string content, string filename);        //用于输出转换后文本的函数




#endif //SOFTWARE_MAIN1_H
