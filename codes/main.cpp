#include <iostream>
#include "main1.h"
#include "node.h"
#include "process.h"
using namespace std;

int main() {
    extern string whole_content;               //储存转换后的文本
    string filename;
    cin >> filename;
    node* root = input(filename);
    dfs(root);
    whole_content += "</article></body></html>";
    output(whole_content, filename);
    return 0;
}
