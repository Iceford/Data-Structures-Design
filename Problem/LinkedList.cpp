#include "LinkedList.h"
#include "variable.h"
#include <iostream>
using namespace std;

node::node(int val, int x1, int y1, int z1) : val(val), x(x1), y(y1), z(z1), next(NULL) {}
node::node(int val) : val(val), x(-1), y(-1), z(-1), next(NULL) {}
node::node() : val(-1), x(-1), y(-1), z(-1), next(NULL) {}

//带参构造函数
MyLinkedList::MyLinkedList(string ch)
{
    size = 0;
    frequenNum = 0;
    nearbyNum = 8;
    str = ch;
    head = new node(0);
}
//默认构造函数
MyLinkedList::MyLinkedList()
{
    size = 0;
    frequenNum = 0;
    nearbyNum = 8;
    str = "";
    head = new node(0);
}

void MyLinkedList::addFrequenNum()
{
    frequenNum++;
}

int MyLinkedList::get(int index)
{
    if (index < 0 || index > size - 1)
        return -1;          //约束条件
     //初始化临时cur为head->next,
    node* cur = head->next;
    while (index-- && cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur->val;
}
void MyLinkedList::show()
{

    if (size == 0)
    {
        cout << str << ": ";
        cout << "该链表为空。" << endl;
        return;
    }
    cout << endl<< "文档集合数量：" << size << endl;
    cout << "文档编号:";
    for (int i = 0; i < size; i++)
        cout<<"doc" << get(i) << " ";
    cout << endl;
}

//统计词条信息
void MyLinkedList::Show_Entry()
{

    if (size == 0)
    {
        cout << str << ": ";
        cout << "该链表为空。" << endl;
        return;
    }
    cout << endl<< "文档集合数量：" << size << " 文档编号:";
    for (int i = 0; i < size; i++)
        cout << "doc" << get(i) << " ";
    cout << endl;
}

void MyLinkedList::addAtHead(int val)
{
    node* q = new node(val);
    q->next = head->next; //新建一个节点
    //将该节点插入头节点
    head->next = q; 
    size++;
}

void MyLinkedList::addAtTail(int val, int x, int y, int z)
{
    node* q = new node(val, x, y, z); //新建节点
    //新建一个临时变量保存head，确保递归不会改变head
    node* cur = head; 
    while (cur->next)
        cur = cur->next; 
    cur->next = q; 
    size++;
}

void MyLinkedList::addAtTail(int val)
{
    node* q = new node(val); //新建节点
    //新建一个临时变量保存head，确保递归不会改变head
    node* cur = head; 
    while (cur->next)
        cur = cur->next; 
    cur->next = q;
    size++;
}

void MyLinkedList::addAtIndex(int index, int val)
{
    if (index <= 0)
        addAtHead(val);

    else if (index < size)
    {
        node* q = new node(val);
        node* cur = head;

        while (index-- && cur->next)
            cur = cur->next; //寻找到合适的位置
        q->next = cur->next; //插入节点
        cur->next = q;

        size++;
    }
    else if (index == size)
        addAtTail(val);
}

void MyLinkedList::deleteAtIndex(int index)
{
    if (index < 0 || index > size - 1)
        return;
    node* temp = head;
    while (index--)
        temp = temp->next;

    if (temp != NULL && temp->next != NULL)
        temp->next = temp->next->next;
    size--;
}

void MyLinkedList::setStr(string ch)
{
    str = ch;
}

//重载运算符&
MyLinkedList operator&(MyLinkedList& a, MyLinkedList& b)
{
    node* head1 = b.head->next;
    node* head2 = a.head->next;
    MyLinkedList myl;
    myl.str = a.str + "&" + b.str;
    while (head1 && head2)
    {
        //该链表节点值不为0且两个链表的值相等
        if (head1->val && head1->val == head2->val) 
        {
            myl.addAtTail(head1->val);
            head2 = head2->next;
            head1 = head1->next;
        }
        else if (head1 && head2 && head1->val > head2->val)
            head2 = head2->next;
        else if (head1 && head2 && head1->val < head2->val)
            head1 = head1->next;
    }
    return myl;
}

//重载运算符|
MyLinkedList operator|(MyLinkedList& a, MyLinkedList& b)
{
    node* head1 = b.head->next;
    node* head2 = a.head->next;
    MyLinkedList myl;
    myl.str = a.str + "|" + b.str;
    while (head1 && head2)
    {
        //该链表节点值不为0且两个链表的值相等
        if (head1->val && head1->val == head2->val) 
        {
            myl.addAtTail(head1->val);
            head2 = head2->next;
            head1 = head1->next;
        }
        else if (head1->val > head2->val)
        {
            myl.addAtTail(head2->val);
            head2 = head2->next;
        }
        else if (head1->val < head2->val)
        {
            myl.addAtTail(head1->val);
            head1 = head1->next;
        }
    }
    while (head1)
    {
        myl.addAtTail(head1->val);
        head1 = head1->next;
    }
    while (head2)
    {
        myl.addAtTail(head2->val);
        head2 = head2->next;
    }
    return myl;
}

//打印输出附近的字符
void MyLinkedList::printNearbyWord(int num)
{
    node* cur = head->next;

    while (cur)
    {
        if (cur->val == num)
        {

            int le = max(cur->z - nearbyNum, 0);
            int num1 = fruits_before[cur->x][cur->y].size();
            int rc = min(cur->z + nearbyNum, num1);
            cout << str << "\t";
            for (int i = le; i < rc; i++)
            {
                cout << fruits_before[cur->x][cur->y][i] << " ";
            }
            cout << endl;
            return;
        }
        else
            cur = cur->next;
    }
    cout << "该链表不存在" << num << endl;
}


//全部将arr赋值为0
book::book()
{
    fill(arr, arr + 11, 0); 
}

//判断链表内是否出现过数字x
bool book::whether_appear(int x) 
{
    if (!arr[x])
        return true;
    else
        return false;
}
//将数字x设为1，表示链表内已存在
void book::setBook(int x) 
{
    if (x < 1 || x > 10)
        return;
    arr[x] = 1;
}
