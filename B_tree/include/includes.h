#pragma once
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define m 4                     //B树的阶
#define MAX_NUM m               //关键字上限
#define MIN_NUM (m-1)/2         //除头结点外关键字下限
#define SPLIT_INDEX (m+1)/2     //分裂处下标
#define dataType int            //关键字数据类型

typedef struct{
    dataType data;      
}record, *Record;       //关键字类型

typedef struct BTNode{
    int keynum;                 //结点当前的关键字个数
    int key[m+1];               //索引数组,key[0]不用
    struct BTNode* parent;      //双亲结点指针
    struct BTNode* ptr[m+1];    //孩子结点指针数组
    Record recptr[m+1];         //记录指针向量，recptr[0]不用
}BTNode, *BTree;

typedef struct{
    int index;          //1<=index<=m,在结点中的关键字位序
    int tag;            //1:查找成功，0：查找失败
    BTNode* node;         //指向找到的结点
}result;

//insert
void InitBTNode(BTree &p);      //初始化结点
int InsertBTree(BTree &T, int k, Record rcd);   //插入结点
void split(BTree &q, BTree &ap);    //分裂饱和结点
void newRoot(BTree &T, BTree p, BTree ap, int k, Record rcd);   //创建新根结点
void Insert(BTree &q, int k, int index, BTree ap, Record rcd);  //插入关键字及指针ap


//delete
int DeleteBTree(BTree &T, int key);         //删除索引为key的记录
void Successor(BTree &node, int &index);    //若不是终端结点，将直接前驱的索引和值覆盖掉当前结点
int Remove(BTree& node, int i);     //从结点p中删除key[i]
int InsertRecord(BTree& node, int key,int i, Record rcd);   //向父结点插入关键字
void Restore(BTree& node, int index);   //调整树
void CombineBTNode(BTree& l_node, BTree& r_node);   //合并结点
void DeleteRoot(BTree& root);   //将合并后结点中所有记录插入到父节点中

//print
void Traverse(BTree t, int k); //遍历B树
void PrintBTree(BTree t);   //打印B树


//search
void SearchBTree(BTree T, int k, result &r);    //在m阶B树t上查找索引k，用r返回(pt,i,tag)
int Search(BTree p, int k); //在p->key[1..p->keynum]中查找p->key[i-1]<k<=p->key[i]

//销毁
void DestroyBTree(BTree &t);    //释放树