//
// Created by 丁程 on 2021/6/30.
//

#include "process.h"


int trim(string &s) {
    if (s.empty()) {
        return -1;
    }
    int n = s.find_first_not_of(' ');
    s.erase(0, n);
    n /= 4;
    return n;
}//在解决列表嵌套时去除左空格

node* line_mid(node* temp,string content1) {
    const char *ch = content1.c_str();
    int length = strlen(ch);
    bool flag_strong = false;       //粗体状态
    bool flag_em = false;           //斜体状态
    bool flag_s = false;            //删除线状态
    bool flag_u = false;            //下划线状态
    bool flag_img1 = false;         //图片状态1
    bool flag_img2 = false;         //图片状态2
    bool flag_link1 = false;        //链接状态
    bool flag_link2 = false;        //链接状态2
    bool flag_trans = false;
    bool flag_url = false;
    bool flag_incode = false;
    string img1, img2;
    string link1, link2;            //存放图片和链接的几个元素
    string code;
    for (int i = 0; i < length; ++i) {
        if (ch[i] == '`' && !flag_incode){          //行内代码
            flag_incode = true;
            continue;
        }
        if (flag_incode){
            if (ch[i] != '`'){
                code += ch[i];
                continue;
            }
            else{
                temp->content += "<code>" + code + "</code>";
                code.clear();
                flag_incode = false;
                continue;
            }
        }
        if (i < length - 1 &&
            ((ch[i] == '*' && ch[i + 1] == '*') || (ch[i] == '_' && ch[i + 1] == '_')) && !flag_url && !flag_incode) {          //粗体
            if (flag_strong) {
                temp->content += "</b>";
            } else {
                temp->content += "<b>";
            }
            flag_strong = !flag_strong;         //状态取反
            i++;        //跳过第二个*或_
            continue;
        }
        if ((i == length - 1 && (ch[i] == '*' || ch[i] == '_') && flag_em) || (i < length - 1 &&
                                                                               ((ch[i] == '*' && ch[i + 1] != '*') ||
                                                                                (ch[i] == '_' &&
                                                                                 ch[i + 1] != '_'))) && !flag_url && !flag_incode) {          //斜体
            if (flag_em) {
                temp->content += "</em>";
            } else {
                temp->content += "<em>";
            }
            flag_em = !flag_em;         //状态取反
            continue;
        }
        if (i < length - 2 && ((ch[i] == '<' && ch[i + 1] == 'u' && ch[i + 2] == '>')) && !flag_url && !flag_incode) {          //进入下划线状态
            flag_u = true;
            temp->content += "<u>";
            i += 2;         //  跳过剩下的字符
            continue;
        }
        if (i < length - 3 &&
            ((ch[i] == '<' && ch[i + 1] == '/' && ch[i + 2] == 'u' && ch[i + 3] == '>')) && !flag_url && !flag_incode) {     //离开下划线状态
            temp->content += "</u>";
            i += 3;         //  跳过剩下的字符
            continue;
        }
        if (i < length - 1 && ((ch[i] == '~' && ch[i + 1] == '~')) && !flag_url && !flag_incode) {          //删除线
            if (flag_s) {
                temp->content += "</s>";
            } else {
                temp->content += "<s>";
            }
            flag_s = !flag_s;         //状态取反
            i++;        //跳过第二个~
            continue;
        }
        if (i < length - 1 && ch[i] == '!' && ch[i + 1] == '[' && !flag_incode) {
            flag_img1 = true;
            i++;        //跳过'['
            continue;
        }
        if (ch[i] == '[') {
            flag_link1 = true;
            continue;
        }
        if (flag_trans && flag_link1) {
            flag_link2 = true;
            flag_link1 = false;
            flag_trans = false;
            flag_url = true;
            continue;
        }
        if (flag_trans && flag_img1) {
            flag_img2 = true;
            flag_img1 = false;
            flag_trans = false;
            flag_url = true;
            continue;
        }
        if (flag_img1) {
            if (ch[i] != ']')
                img1 += ch[i];
            else {
                flag_trans = true;
            }
            continue;
        }
        if (flag_img2) {
            if (ch[i] != ')')
                img2 += ch[i];
            else {
                temp->content += "<img src=\"" + img2 + "\" " + "alt=\"" + img1 + "\">";
                img1.clear();
                img2.clear();
                flag_url = false;
                flag_img2 = false;
            }
            continue;
        }
        if (flag_link1) {
            if (ch[i] != ']')
                link1 += ch[i];
            else {
                flag_trans = true;
            }
            continue;
        }
        if (flag_link2) {
            if (ch[i] != ')')
                link2 += ch[i];
            else {
                temp->content += "<a href=\"" + link2 + "\"" + ">" + link1 + "</a>";
                link1.clear();
                link2.clear();
                flag_url = false;
                flag_link2 = false;
            }
            continue;
        }
        if (i < length - 3 && ch[i] == '<' && ch[i + 1] == 'i' && ch[i + 2] == 'm' && ch[i + 3] == 'g' && !flag_incode) {
            temp->content += content1.substr(i, content1.find_first_of('>') - i);
            i = content1.find_first_of('>');
            continue;
        }

        temp->content += ch[i];             //纯文本
    }
    return temp;
}
bool flag_code = false;
    node *line_front(node *temp, string content) {
        bool nest = false;
        int level = trim(content);
        string chr = content.substr(0, 1);
        string chr1 = content.substr(1, 1);
        const char *ch = content.c_str();
        node *temp1 = new node;
        node *temp2 = temp;
        node *temp3 = temp;
        while (!temp2->child.empty()) {
            temp2 = temp2->child.back();     //temp2指向文本树的最深层最后子结点，用于判别层级关系
        }
        if (level == 1 && chr !="*" && chr != "-" && !(*ch >= '0' && *ch <= '9')){      //块代码情况1:开头空四格
            if (temp3->child.empty() || temp3->child.back()->type != 13)//判别是否是块代码第一行
            {
                node *_temp = new node;
                _temp->type = 13;
                _temp->level = level;
                temp3->child.push_back(_temp);
            }
            temp3 = temp3->child.back();
            temp1->type = 0;        //插入块代码结点之后,代码以文本形式呈现,不需要做处理
            temp1->content = content + "\n";
            temp3->child.push_back(temp1);
            return temp;
        }
        if (content.substr(0,3) == "```") {      //块代码情况2:开头与结尾```、
            if (!flag_code) {
                node *_temp = new node;
                _temp->type = 13;
                _temp->level = level;
                temp3->child.push_back(_temp);
                flag_code = true;
                return temp;
            }
            else
                flag_code = false;
            return temp;
        }
        if (flag_code){         //块代码情况2插入代码内容
            temp3 = temp3->child.back();
            temp1->type = 0;        //插入块代码结点之后,代码以文本形式呈现,不需要做处理
            temp1->content = content + "\n";
            temp3->child.push_back(temp1);
            return temp;
        }
        if ((chr == "*" || chr == "-") && chr1 == " ") {         //无序列表
            for (int p = 0; p < level; ++p) {
                temp3 = temp3->child.back();
            }
            if (temp3->child.empty() || temp3->child.back()->type != 7)//判别是否是第一个列表第一项 避免指针错误
            {
                node *_temp = new node;
                _temp->type = 7;
                _temp->level = level;
                temp3->child.push_back(_temp);
            }
            temp3 = temp3->child.back();
            temp1->type = 9;
            temp1->level = level;
            temp3->child.push_back(line_mid(temp1, content.substr(2)));
            return temp;
        } else if (*ch >= '0' && *ch <= '9') {          //有序列表
            while (*ch >= '0' && *ch <= '9')           //跳过数字
                ch++;
            for (int p = 0; p < level; ++p) {
                temp3 = temp3->child.back();
            }
            if (temp3->child.empty() || temp3->child.back()->type != 8)//判别是否是第一个列表第一项 避免指针错误
            {
                node *_temp = new node;
                _temp->type = 8;
                _temp->level = level;
                temp3->child.push_back(_temp);
            }
            temp3 = temp3->child.back();
            temp1->type = 9;
            temp1->level = level;
            temp3->child.push_back(line_mid(temp1, content.substr(3)));
            return temp;
        } else if (chr == "#")         //行首标记为标题
        {
            int n = 1;
            if (content.substr(0, 2) == "##")
                n = 2;
            if (content.substr(0, 3) == "###")
                n = 3;
            if (content.substr(0, 4) == "####")
                n = 4;
            if (content.substr(0, 5) == "#####")
                n = 5;
            if (content.substr(0, 6) == "######")
                n = 6;
            temp1->type = n + 60;
            temp->child.push_back(line_mid(temp1, content.substr(n + 1)));      //将去掉#的内容作为内容
            return temp;
        } else if (chr == "<") {
            temp1->type = 0;
            temp1->content = content;
            temp->child.push_back(temp1);
            return temp;
        } else        //无行首标记，段落
        {
            temp1->type = 1;
            temp->child.push_back(line_mid(temp1, content.substr(0)));
            return temp;
        }
    }