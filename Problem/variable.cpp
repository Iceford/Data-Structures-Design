#include <map>
#include <vector>
#include "LinkedList.h"
#include "variable.h"
vector<MyLinkedList> fruits_after;            //将其定义为全局函数，减少内存消耗，方便调用
vector<vector<vector<string>>> fruits_before; //将之前的文章保存进三维矩阵
vector<book> book1;                           //标志容器
map<string, int> ma;                          //映射容器：用于映射文件夹fruit-after下文件的字符串和在fruits_after容器中的位置
string opeStr[100];                           //字符串数组