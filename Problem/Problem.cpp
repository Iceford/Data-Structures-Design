#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<sstream>
#include<fstream>
#include<map>
#include<vector>
#include <windows.h>
#include"LinkedList.h"
#include"function.h"
#include"variable.h"
using namespace std;


#define STD_OUTPUT_HANDLE ((DWORD)-11)
int xyz[3];//用于保存location函数计算的字符串ch在fruit-befor中xyz值，

//定位字符串在fruits_before中的位置
void location(string ch, int index)    
{
    for (int i = 0; i < fruits_before[index - 1].size(); i++)
    {
        for (int j = 0; j < fruits_before[index - 1][i].size(); j++)
        {
            if (fruits_before[index - 1][i][j] == ch)
            {
                xyz[0] = index - 1;
                xyz[1] = i;
                xyz[2] = j;
                return;
            }
        }
    }
}

//数据库初始化
void initialization()
{
    ifstream in1;   //文件读取流
    ofstream out;   //文件写入流
    string ch;
    vector<string>temp;     
    for (int i = 1; i <= 10; i++)//打开fruits-brfore文件夹,将其内容保存在三维数组fruits_before内
    {
        in1.open("fruits/fruits-before/" + files[i]);//遍历打开每一个txt文件
        string sh, s;
        vector<vector<string> >str1;
        stringstream ss1;   //字符串流
        while (getline(in1, sh))
        {
            vector<string>str2;
            ss1.clear();    //先清空
            ss1 << sh;
            while (ss1 >> s)
            {
                str2.push_back(s);
            }
            str1.push_back(str2);
        }
        fruits_before.push_back(str1);
        in1.close();    //关闭输入流
    }


    int index = 0;
    for (int i = 1; i <= 10; i++) //数据输入并进行倒排索引
    {
        in1.open("fruits/fruits-after/" + files[i]);//遍历打开每一个txt文件
        temp.clear();       //先清空再存储
        while (in1 >> ch)   //输入直到结束
        {
            if (ma[ch] == 0)        //如果第一次遇到该字符
            {
                location(ch, i);                     //计算ch字符在fruit_before中出现的位置并保存在数组xyz中
                MyLinkedList myL(ch);        //当该字符第一次出现时，为其建立一个链表和链表内数字的标记
                myL.addAtTail(i, xyz[0], xyz[1], xyz[2]);

                book b1;
                b1.setBook(i);
                fruits_after.push_back(myL); 
                book1.push_back(b1);
                ma[ch] = index + 1;            
                index++;
            }
            else//如果再次遇到该字符
            {
                if (book1[ma[ch] - 1].whether_appear(i))
                {
                    location(ch, i);
                    fruits_after[ma[ch] - 1].addAtTail(i, xyz[0], xyz[1], xyz[2]);
                    book1[ma[ch] - 1].setBook(i);//标记表示第i篇文章已经出现过ch了
                }
            }
        }
        in1.close();    //关闭输入流
    }
}


//查看数据库文章
void Show_Article()
{
    ifstream in1;   //打开输入流
    string ch;
    //打开fruits-brfore文件夹，将其内容在三维数组fruits_before内
    for (int i = 1; i <= 10; i++)   
    {
        in1.open("fruits/fruits-before/" + files[i]);   //遍历打开每一个txt文件
        cout << files[i] << endl << endl;
        while (in1 >> ch)   //输出文章内容
        {
            cout << ch << " ";
        }
        cout << endl << endl;
        in1.close();        //关闭输入流
    }
}

//查看建立的倒排索引资料
void Show_Indexes()
{
    ifstream in1;   //打开输入流
    string ch;
    //打开fruits-brfore文件夹,将其内容保存在三维数组fruits_before内
    for (int i = 1; i <= 10; i++)
    {
        in1.open("fruits/fruits-after/" + files[i]);//打开文件
        cout << files[i] << endl;
        while (getline(in1, ch))
        {
            cout << ch;
        }
        cout << endl << endl;
        in1.close();    //关闭输入流
    }
}

//查看数据库内的词条信息
void Show_Entry()
{
    for (int i = 0; i < fruits_after.size(); i++)
    {
        fruits_after[i].Show_Entry();
        cout << endl;
    }
}

//实现布尔检索功能
void Boolean_Retrieval()
{
    cout << R"(
测试样例
样例输入
2
cherry & peach
apple | ( tree & central )
样例输出
文档集合数量：2
文档编号:doc2 doc6
doc2 :cherry.txt
cherry  Prunus ilicifolia, hollyleaf cherry (a cherry laurel species)
peach   van Tienlioven that he had found 12 apple, 40 peach, 73 cherry trees, 26 sage plants..,
doc6 :peach.txt
cherry  international consortium, the International Peach Genome Initiative, which include researchers from the United States, Italy, Chile,
peach   The peach (Prunus persica) is a deciduous tree native

文档集合数量：4
文档编号:doc1 doc2 doc4 doc7
doc1 :apple.txt
apple   An apple is an edible fruit produced by an
tree    is an edible fruit produced by an apple tree (Malus domestica). Apple trees are cultivated worldwide
central Most new apple cultivars originate as seedlings, which either arise by chance
doc2 :cherry.txt
apple   of Corielis van Tienlioven that he had found 12 apple, 40 peach, 73 cherry trees, 26
tree    wood" redirect here. For other uses, see Cherry tree (disambiguation) and Cherrywood (disambiguation)
doc4 :mangosteen.txt
apple   The journalist and gourmet R. W. Apple, Jr. once said of
tree    as the purple mangosteen, is a tropical evergreen tree with edible fruit native to tropical lands
central deliver to her the fresh fruit.Although this legend can be traced to a 1930 publication by
doc7 :pear.txt
apple   similar to the wood of its relative, the apple tree (Malus domestica) and used for many
tree    and consumed around the world, growing on a tree and harvested in the Northern Hemisphere in
central the foothills of the Tian Shan, a mountain range of Central Asia, and to have spread

)" << endl;
    string ch, ch1;
    int m;//查询次数
    cout << "请输入查询次数" << endl;
    cin >> m;
    getchar();  //吞掉换行
    stringstream ss;
    MyLinkedList myl;

    while (m--)
    {
        int index = 0;
        opeStr->clear();
        ss.clear();
        getline(cin, ch);//获取序列
        ss << ch;
        while (ss >> ch1)
        {
            if (ch1 == "&" || ch1 == "|" || ch1 == "(" || ch1 == ")")continue;
            opeStr[index++] = ch1;//将操作序列里面的字符串保存进操作字符串数组，方便输出
        }
        if (index == 1)
        {
            if (ma[ch1] - 1 != -1) myl = fruits_after[ma[ch1] - 1];
            else cout << "未找到该词条" << endl;
        }
        else
        {

            myl = findBool(ch);//获取返回的列表
        }
        myl.show();//打印返回的链表
        for (int i = 0; i < myl.size; i++)
        {
            int num = myl.get(i);
            cout<<"doc" << num << " :" << files[num] << endl;
            for (int j = 0; j < index; j++)
            {
                if (!book1[ma[opeStr[j]] - 1].whether_appear(num))
                {
                    //打印将操作序列的字符串
                    fruits_after[ma[opeStr[j]] - 1].printNearbyWord(num);
                }
            }
        }
        cout << endl;
    }
}



struct head
{
    int b;                 //字符
    long count;            //统计文件中字符出现的次数
    long parent, lch, rch; //构造树
    char bits[256];        //哈夫曼编码
};

struct head header[512], tmp; //节点树

//打印输出操作进度
void show_progress(int per)
{
    int i = 0;
    cout << "|";
    for (i = 0; i < 10; i++)
    {
        if (i < per / 10)
        {
            cout << ">";
        }
        else
        {
            cout << "-";
        }
            
    }
    cout << "|已完成" << per << endl;
}

// 压缩函数：读取原文件后将其压缩写入另一个文件夹
int compress(const char* filename, const char* output_folder)
{
    char buf[512];
    unsigned char c;
    long i, j, m, n, f;
    long min1, pt1, flength;
    FILE* ifp, * ofp;
    int per = 10;
    ifp = fopen(filename, "rb"); //打开原文件
    if (ifp == NULL)             //如果打开失败，则输出错误信息
    {
        cout << "打开文件失败:" << filename << endl;
        return 0;
    }
    ofp = fopen(output_folder, "wb"); //打开压缩后存储信息的文件
    if (ofp == NULL)
    {
        cout << "打开文件失败:" << output_folder << endl;
        return 0;
    }
    flength = 0;
    while (!feof(ifp))
    {
        fread(&c, 1, 1, ifp);
        header[c].count++; //读取文件，统计字符出现次数
        flength++;         //记录文件的字符总数
    }
    flength--;
    header[c].count--;
    // 哈夫曼算法中初始节点的设置
    for (i = 0; i < 512; i++)
    {
        if (header[i].count != 0)
        {
            header[i].b = (unsigned char)i;
        }
        else
        {
            header[i].b = -1;
        }
        header[i].parent = -1;
        header[i].lch = header[i].rch = -1;
    }
    //将节点按出现次数进行排序
    for (i = 0; i < 256; i++)
    {
        for (j = i + 1; j < 256; j++)
        {
            if (header[i].count < header[j].count)
            {
                tmp = header[i];
                header[i] = header[j];
                header[j] = tmp;
            }
        }
    }
    //统计不同字符的数量
    for (i = 0; i < 256; i++)
    {
        if (header[i].count == 0)
        {
            break;
        }
    }

    n = i;
    m = 2 * n - 1;
    for (i = n; i < m; i++)
    {
        min1 = 999999999;
        for (j = 0; j < i; j++)
        {
            if (header[j].parent != -1)
            {
                continue;
            }
            if (min1 > header[j].count)
            {
                pt1 = j;
                min1 = header[j].count;
                continue;
            }
        }
        header[i].count = header[pt1].count;
        header[pt1].parent = i;
        header[i].lch = pt1;
        min1 = 999999999;
        for (j = 0; j < i; j++)
        {
            if (header[j].parent != -1)
            {
                continue;
            }
            if (min1 > header[j].count)
            {
                pt1 = j;
                min1 = header[j].count;
                continue;
            }
        }
        header[i].count += header[pt1].count;
        header[i].rch = pt1;
        header[pt1].parent = i;
    }
    //构造哈夫曼树，设置字符编码
    for (i = 0; i < n; i++)
    {
        f = i;
        header[i].bits[0] = 0;
        while (header[f].parent != -1)
        {
            j = f;
            f = header[f].parent;
            if (header[f].lch == j)
            {
                j = strlen(header[i].bits);
                memmove(header[i].bits + 1, header[i].bits, j + 1);
                header[i].bits[0] = '0';
            }
            else
            {
                j = strlen(header[i].bits);
                memmove(header[i].bits + 1, header[i].bits, j + 1);
                header[i].bits[0] = '1';
            }
        }
    }

    //读取原文件字符，按照设置的编码替换文件中的字符
    fseek(ifp, 0, SEEK_SET); //将指针定在文件起始位置
    fseek(ofp, 8, SEEK_SET); //以8位二进制数为单位进行读取
    buf[0] = 0;
    f = 0;
    pt1 = 8;

    cout << "读取将要压缩的文件:" << filename << endl;
    cout << "当前文件有:" << flength << endl;
    cout << "正在压缩" << endl;

    while (!feof(ifp))
    {
        c = fgetc(ifp);
        f++;
        for (i = 0; i < n; i++)
        {
            if (c == header[i].b)
                break;
        }
        strcat(buf, header[i].bits);
        j = strlen(buf);
        c = 0;
        while (j >= 8) //当剩余字符数量不小于8个时
        {
            for (i = 0; i < 8; i++) //按照八位二进制数转化成十进制ASCII码写入文件一次进行压缩
            {
                if (buf[i] == '1')
                {
                    c = (c << 1) | 1;
                }
                else
                {
                    c = c << 1;
                }
            }
            fwrite(&c, 1, 1, ofp);
            pt1++;
            strcpy(buf, buf + 8);
            j = strlen(buf);
        }
        if (100 * f / flength > per)
        {
            show_progress(per);
            per += 10;
        }
        if (f == flength)
            break;
    }
    show_progress(100);

    if (j > 0) //当剩余字符数量少于8个时
    {
        strcat(buf, "00000000");
        for (i = 0; i < 8; i++)
        {
            if (buf[i] == '1')
            {
                c = (c << 1) | 1;
            }
            else
            {
                c = c << 1; //对不足的位数进行补零
            }
        }
        fwrite(&c, 1, 1, ofp);
        pt1++;
    }
    fseek(ofp, 0, SEEK_SET); //将编码信息写入存储文件
    fwrite(&flength, 1, sizeof(flength), ofp);
    fwrite(&pt1, sizeof(long), 1, ofp);
    fseek(ofp, pt1, SEEK_SET);
    fwrite(&n, sizeof(long), 1, ofp);
    for (i = 0; i < n; i++)
    {
        tmp = header[i];

        fwrite(&(header[i].b), 1, 1, ofp);
        pt1++;
        c = strlen(header[i].bits);
        fwrite(&c, 1, 1, ofp);
        pt1++;
        j = strlen(header[i].bits);

        if (j % 8 != 0) //当位数不满8时，对该数进行补零操作
        {
            for (f = j % 8; f < 8; f++)
            {
                strcat(header[i].bits, "0");
            }
        }

        while (header[i].bits[0] != 0)
        {
            c = 0;
            for (j = 0; j < 8; j++)
            {
                if (header[i].bits[j] == '1')
                {
                    c = (c << 1) | 1;
                }
                else
                {
                    c = c << 1;
                }
            }
            strcpy(header[i].bits, header[i].bits + 8);
            fwrite(&c, 1, 1, ofp); //将所得的编码信息写入文件
            pt1++;
        }

        header[i] = tmp;
    }
    fclose(ifp);
    fclose(ofp); //关闭文件

    cout << "压缩后文件为:" << output_folder;
    cout << "压缩后文件有:" << pt1 + 4 << "字符" << endl;

    return 1; //返回压缩成功信息
}

// 解压函数：解压文件并将解生成的文件写入新文件夹
int unpack(const char* filename, const char* output_folder)
{
    char buf[255], bx[255];
    unsigned char c;
    char out_filename[512];
    long i, j, m, n, f, p, l;
    long flength;
    int per = 10;
    int len = 0;
    FILE* ifp, * ofp;
    char c_name[512] = { 0 };
    ifp = fopen(filename, "rb"); //打开文件
    if (ifp == NULL)
    {
        return 0; //若打开失败，则输出错误信息
    }

    //读取原文件
    if (output_folder)
    {
        strcpy(out_filename, output_folder);
    }
    else
    {
        strcpy(out_filename, c_name);
    }

    ofp = fopen(out_filename, "wb");
    if (ofp == NULL)
    {
        return 0;
    }

    fseek(ifp, 0, SEEK_END);
    len = ftell(ifp);
    fseek(ifp, 0, SEEK_SET);
    cout << "将要读取解压的文件:" << filename << endl;
    cout << "当前文件有:" << len << endl;
    cout << "正在解压" << endl;
    fread(&flength, sizeof(long), 1, ifp);
    fread(&f, sizeof(long), 1, ifp);
    fseek(ifp, f, SEEK_SET);
    fread(&n, sizeof(long), 1, ifp); //读取原文件各参数
    //读取压缩文件内容并转换成二进制码
    for (i = 0; i < n; i++)
    {
        fread(&header[i].b, 1, 1, ifp);
        fread(&c, 1, 1, ifp);
        p = (long)c;
        header[i].count = p;
        header[i].bits[0] = 0;
        if (p % 8 > 0)
        {
            m = p / 8 + 1;
        }
        else
        {
            m = p / 8;
        }
        for (j = 0; j < m; j++)
        {
            fread(&c, 1, 1, ifp);
            f = c;
            _itoa(f, buf, 2);
            f = strlen(buf);
            for (l = 8; l > f; l--)
            {
                strcat(header[i].bits, "0"); //位数不足，执行补零操作
            }
            strcat(header[i].bits, buf);
        }
        header[i].bits[p] = 0;
    }
    //按码求对应字符
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (strlen(header[i].bits) > strlen(header[j].bits))
            {
                tmp = header[i];
                header[i] = header[j];
                header[j] = tmp;
            }
        }
    }

    p = strlen(header[n - 1].bits);
    fseek(ifp, 8, SEEK_SET);
    m = 0;
    bx[0] = 0;

    while (1)
    {
        while (strlen(bx) < (unsigned int)p)
        {
            fread(&c, 1, 1, ifp);
            f = c;
            _itoa(f, buf, 2);
            f = strlen(buf);
            for (l = 8; l > f; l--)
            {
                strcat(bx, "0");
            }
            strcat(bx, buf);
        }
        for (i = 0; i < n; i++)
        {
            if (memcmp(header[i].bits, bx, header[i].count) == 0)
            {
                break;
            }
        }
        strcpy(bx, bx + header[i].count);
        c = header[i].b;
        fwrite(&c, 1, 1, ofp);
        m++;
        if (100 * m / flength > per)
        {
            show_progress(per);
            per += 10;
        }
        if (m == flength)
        {
            break;
        }
    }
    show_progress(100);

    fclose(ifp);
    fclose(ofp);

    cout << "解压后文件为:" << out_filename << endl;
    cout << "解压后文件有:" << flength << endl;

    return 1; //输出成功信息
}

int Huffman()
{
    //定义操作文件数组
    string files[11] = { " ", "apple.txt", "cherry.txt", "grape.txt", "mangosteen.txt", "orange.txt", "peach.txt", "pear.txt", "pineapple.txt", "pomelo.txt", "watermelon.txt" };
    memset(&header, 0, sizeof(header));
    memset(&tmp, 0, sizeof(tmp));



    cout << "----------正在压缩文件------------" << endl;
    //压缩文件
    for (int i = 1; i <= 10; i++)
    {
        memset(&header, 0, sizeof(header));
        memset(&tmp, 0, sizeof(tmp));
        cout << "正在将原文件" << files[i] << "压缩到 ./fruits_compress/fruits-before/" << files[i] << endl;
        compress(("./fruits/fruits-before/" + files[i]).c_str(), ("./fruits_compress/fruits-before/" + files[i]).c_str());
        cout << "正在将原文件" << files[i] << "压缩到 ./fruits_compress/fruits-after/" << files[i] << endl;
        compress(("./fruits/fruits-after/" + files[i]).c_str(), ("./fruits_compress/fruits-after/" + files[i]).c_str());
    }

    cout << endl
        << endl
        << "----------正在解压文件------------" << endl;
    //解压文件
    for (int i = 1; i <= 10; i++)
    {
        cout << "正在将压缩后的" << files[i] << "解压到 ./fruits_unzip/fruits-before/" << files[i] << endl;
        unpack(("./fruits_compress/fruits-before/" + files[i]).c_str(), ("./fruits_unzip/fruits-before/" + files[i]).c_str());
        cout << "正在将压缩后的" << files[i] << "解压到 ./fruits_unzip/fruits-after/" << files[i] << endl;
        unpack(("./fruits_compress/fruits-after/" + files[i]).c_str(), ("./fruits_unzip/fruits-after/" + files[i]).c_str());
    }
    system("pause");
    return 0;
}


const int INF = 999999999; //模拟无穷大（表示图的两个顶点没有直接相连）

//弗洛伊德算法求解最短路径
void Floyd_Warshall(double** arr, int n)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);
            }
        }
    }
}
//读取跳转的概率矩阵
void read_matrix(int num, double** arr)
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            double probability;
            cin >> probability;
            //进行数据处理，取倒数
            if (probability > 0)
            {
                arr[i][j] = 1.0 / probability;
            }
            else
            {
                arr[i][j] = INF;
            }
        }
    }
}
//打印输出所有网页之间最短跳转距离矩阵
void show_arr(double** arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl<<endl;
    }
}

int Shortest_path()
{
    cout << R"(
样例输入:
10
1.0000  0.8530  0.8636  0.1771  0.2546  0.1262  0.2162  0.0488  0.2061 0.1165
0.8530  1.0000  0.2819  0.4287  0.3330  0.3598  0.8237  0.7063  0.9565 0.4772
0.8636  0.2819  1.0000  0.0429  0.8887  0.0297  0.5160  0.7141  0.7820 0.9492
0.1771  0.4287  0.0429  1.0000  0.4003  0.0611  0.7951  0.2877  0.2106 0.5884
0.2546  0.3330  0.8887  0.4003  1.0000  0.9987  0.0640  0.5897  0.8763 0.6273
0.1262  0.3598  0.0297  0.0611  0.9987  1.0000  0.9034  0.9996  0.2579 0.2076
0.2162  0.8237  0.5160  0.7951  0.0640  0.9034  1.0000  0.3385  0.2499 0.6091
0.0488  0.7063  0.7141  0.2877  0.5897  0.9996  0.3385  1.0000  0.4253 0.8842
0.2061  0.9565  0.7820  0.2106  0.8763  0.2579  0.2499  0.4253  1.0000 0.0953
0.1165  0.4772  0.9492  0.5884  0.6273  0.2076  0.6091  0.8842  0.0953 1.0000

样例输出：
1       1.17233 1.15794 3.50497 2.28318 3.28448 2.38637 2.55831 2.21781 2.21146
1.17233 1       2.32425 2.33263 2.18664 2.32096 1.21403 1.41583 1.04548 2.09556
1.15794 2.32425 1       2.75304 1.12524 2.12654 1.93798 1.40036 1.27877 1.05352
3.50497 2.33263 2.75304 1       2.49813 2.36463 1.2577  2.83049 3.37811 1.69952
2.28318 2.18664 1.12524 2.49813 1       1.0013  2.10823 1.69578 1.14116 1.59413
3.28448 2.32096 2.12654 2.36463 1.0013  1       1.10693 1.0004  2.14246 2.13137
2.38637 1.21403 1.93798 1.2577  2.10823 1.10693 1       2.10733 2.25951 1.64177
2.55831 1.41583 1.40036 2.83049 1.69578 1.0004  2.10733 1       2.35128 1.13097
2.21781 1.04548 1.27877 3.37811 1.14116 2.14246 2.25951 2.35128 1       2.33229
2.21146 2.09556 1.05352 1.69952 1.59413 2.13137 1.64177 1.13097 2.33229 1)" << endl;

    int num;
    cout << endl << "请输入网页数量:";
    cin >> num;
    double** arr = new double* [num]; //生成一个n*n的矩阵用来保存概率
    for (int i = 0; i < num; i++)
    {
        arr[i] = new double[num];
    }
    cout << endl
        << "请输入这" << num << "个网页的跳转概率矩阵:" << endl;
    read_matrix(num, arr);
    Floyd_Warshall(arr, num);
    cout << endl
        << "所有网页之间最短跳转距离矩阵如下：" << endl;
    show_arr(arr, num);
    return 0;
}


//读取操作输入
void setXY(int x, int y)
{
    HANDLE hout;
    COORD coord;
    coord.X = x;
    coord.Y = y;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, coord);
}

//操作面板
void operator_panel()
{
    setXY(0, 10);
    cout << R"(
                        请输入阿拉伯数字执行相应操作
                        问题一：
                        1、统计数据库的词条数量
                        2、查看建立的倒排索引
                        3、查看数据库内的词条信息
                        问题二：
                        4、使用布尔检索功能
                        问题三：
                        5、哈夫曼实现文件的压缩和解压缩
                        问题四：
                        6、弗洛伊德算法求解多源最短路径)" << endl;
}


int main()
{
    initialization();//数据库初始化
    while (true)
    {
        //清除上一次显示的输出结果，只显示本次输出的结果
        system("CLS");  
        operator_panel();
        int num;
        cin >> num;
        switch (num)
        {
        case 1:
            cout << "数据库的词条数量为：" << fruits_after.size() << endl; break;
        case 2:
            Show_Indexes(); break;
        case 3:
            Show_Entry(); break;
        case 4:
            Boolean_Retrieval(); break;
        case 5:
            Huffman(); break;
        case 6:
            Shortest_path(); break;
        default:
            cout << "请输入正确的数字" << endl;
            break;
        }
        system("pause");
    }
    return 0;
}