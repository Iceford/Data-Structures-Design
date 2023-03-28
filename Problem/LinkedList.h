#pragma once
#include<iostream>
using namespace std;

class node
{
public:
    int val;//值
    int x;//定位该节点对应的文章
    int y;//定位该节点对应的字符串index
    int z;
    node* next;
    node(int val, int x, int y, int z);
    node(int x1);
    node();
};

class book
{
    int arr[11];
public:
    book();
    bool whether_appear(int x);//判断链表内是否出现过数字x
    void setBook(int x);    //将数字x设置成1表示，表示链表内已存在
};

class MyLinkedList
{
public:
    int size;
    int frequenNum;
    int nearbyNum;
    string str;
    node* head;
    MyLinkedList(string ch);
    MyLinkedList();
    int get(int index);
    void addAtHead(int val);
    void addAtTail(int val, int x, int y, int z);
    void addAtTail(int val);
    void addAtIndex(int index, int val);
    void deleteAtIndex(int index);
    void setStr(string ch);
    void show();
    void Show_Entry();
    void addFrequenNum();
    void printNearbyWord(int num);
    friend MyLinkedList operator &(MyLinkedList& a, MyLinkedList& b);
    friend MyLinkedList operator |(MyLinkedList& a, MyLinkedList& b);
};