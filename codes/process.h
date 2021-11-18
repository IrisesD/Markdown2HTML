//
// Created by 丁程 on 2021/6/30.
//

#ifndef SOFTWARE_PROCESS_H
#define SOFTWARE_PROCESS_H
#include "node.h"
#include <string>
using namespace std;

node* line_front(node* temp, string content);//处理行首标记的函数
node* line_mid(node* temp,string content1);         //处理行中标记的函数



#endif //SOFTWARE_PROCESS_H
