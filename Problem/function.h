#pragma once
#include<sstream>
#include"LinkedList.h"
#include"variable.h" 

MyLinkedList findBool(string ch)
{
    stringstream inout;//输入输出流
    string le, ri, ope, openow, now;
    inout.clear();
    inout << ch;
    inout >> le;
    // 分别用来保存每次执行的结果和，出现（）时候用temp保存myl，
    //新出现的字符串则赋值给myl开始
    //blank是空白链表用来清空链表的
    MyLinkedList myl, temp, blank;
    if (ma[le] != 0)myl = fruits_after[ma[le] - 1];
    else myl.setStr(le);
    while (inout >> ope)
    {
        if (ope == "&")
        {
            inout >> ri;
            if (ri == "(")
            {
                inout >> now;
                openow = ope;//保存括号前的符号
                if (ma[now] == 0)
                {
                    cout << now << " 不存在" << endl;
                    temp = myl;
                    myl = blank;//空链表
                }
                else
                {
                    temp = myl;
                    myl = fruits_after[ma[now] - 1];
                }
            }
            else
            {
                myl = myl & fruits_after[ma[ri] - 1];
            }
        }
        else if (ope == "|")
        {
            inout >> ri;
            if (ri == "(")
            {
                inout >> now;
                openow = ope;//保存括号前的符号
                if (ma[now] == 0)
                {
                    cout << now << " is not happen in the ten article." << endl;
                    temp = myl;
                    myl = blank;//空链表
                }
                else
                {
                    temp = myl;
                    myl = fruits_after[ma[now] - 1];
                }
            }
            else
            {
                myl = myl | fruits_after[ma[ri] - 1];
            }
        }
        else if (ope == ")")
        {
            if (openow == "&")
            {
                myl = temp & myl;
            }
            else if (openow == "|")
            {
                myl = temp | myl;
            }
        }
    }
    return myl;
}
string files[11] = { " ","apple.txt","cherry.txt","grape.txt","mangosteen.txt","orange.txt","peach.txt","pear.txt","pineapple.txt","pomelo.txt","watermelon.txt" };
string files1[11] = { " ","apple.bin","cherry.bin","grape.bin","mangosteen.bin","orange.bin","peach.bin","pear.bin","pineapple.bin","pomelo.bin","watermelon.bin" };