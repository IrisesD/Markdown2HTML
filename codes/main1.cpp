//
// Created by 丁程 on 2021/6/30.
//
#include "process.h"
#include "main1.h"
#include "node.h"
node* input(string filename){
    node* root = new node;                         //文本树根结点
    string content;
    string temp;
    ifstream inputfile;
    inputfile.open(filename, ios::in);          //以文件流形式打开
    if(!inputfile)
    {
        cout<<"打开文件失败！"<< filename << endl;
        exit(1);            //打开文件失败
    }
    while(!inputfile.eof()){
        getline(inputfile, temp);               //逐行读取文件
        if(temp.length() != 0)                      //跳过空行
            root = line_front(root, temp);            //调用line_front函数处理行首标记
    }
    inputfile.close();                      //关闭文件
    return root;
}

void output(string content, string filename){
    string new_filename;
    new_filename = filename.substr(0,filename.rfind("."));
    new_filename += ".html";
    ofstream outputfile;
    outputfile.open(new_filename, ios::out);
    outputfile << content;
    outputfile.close();
}
string whole_content =
        "<!DOCTYPE html><html><head>\
        <meta charset=\"utf-8\">\
        <title>Markdown</title>\
        <link rel=\"stylesheet\" href=\"github-markdown.css\">\
        </head><body><article class=\"markdown-body\">";

node* dfs(node* root){
    if (root->type == 0)
        whole_content += "";
    else if(root->type == 1)
            whole_content += "<p>";
    else if(root->type == 2)
            whole_content += "<em>";
        else if(root->type == 3)
            whole_content += "<b>";
        else if(root->type == 4)
            whole_content += "<s>";
        else if(root->type == 5)
            whole_content += "<u>";
        else if(root->type > 60)
            switch (root->type) {
                case 61:
                    whole_content += "<h1>";
                    break;
                case 62:
                    whole_content += "<h2>";
                    break;
                case 63:
                    whole_content += "<h3>";
                    break;
                case 64:
                    whole_content += "<h4>";
                    break;
                case 65:
                    whole_content += "<h5>";
                    break;
                case 66:
                    whole_content += "<h6>";
                    break;
            }
        else if(root->type == 7)
            whole_content += "<ul>";
        else if(root->type == 8)
            whole_content += "<ol>";
        else if(root->type == 9)
            whole_content += "<li>";
        else if(root->type == 13)
            whole_content += "<pre><code>";
        whole_content += root->content;
    for(int i = 0; i < root->child.size();i++) {
        dfs(root->child[i]);
    }
        if (root->type == 0)
            whole_content += "";
        else if(root->type == 1)
            whole_content += "</p>";
        else if(root->type == 2)
            whole_content += "</em>";
        else if(root->type == 3)
            whole_content += "</b>";
        else if(root->type == 4)
            whole_content += "</s>";
        else if(root->type == 5)
            whole_content += "</u>";
        else if(root->type > 60)
            switch (root->type) {
                case 61:
                    whole_content += "</h1>";
                    break;
                case 62:
                    whole_content += "</h2>";
                    break;
                case 63:
                    whole_content += "</h3>";
                    break;
                case 64:
                    whole_content += "</h4>";
                    break;
                case 65:
                    whole_content += "</h5>";
                    break;
                case 66:
                    whole_content += "</h6>";
                    break;
            }
        else if(root->type == 7)
            whole_content += "</ul>";
        else if(root->type == 8)
            whole_content += "</ol>";
        else if(root->type == 9)
            whole_content += "</li>";
        else if (root->type == 13)
            whole_content += "</code></pre>";
        return root;

}