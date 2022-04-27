#include "include/includes.h"

void InitBTNode(BTree &p){
    p = (BTree)malloc(sizeof(BTNode));
    //对p的子节点初始化
    for(int i = 0;i<=m+1;i++){
        p->key[i] = -1;
        p->ptr[i] = NULL;
        p->recptr[i] = NULL;
    }
    p->keynum = 0;
    p->parent = NULL;
    return;
}

int InsertBTree(BTree &T, int k, Record rcd){
    result result;
    //查找是否已经存在
    SearchBTree(T, k, result);
    if(result.tag) return 0; //已存在则不执行插入
    Insert(result.node, k, result.index, NULL, rcd);
    BTree ap;
    while (result.node->keynum >= MAX_NUM  ){
		split(result.node, ap);
        k=result.node->key[SPLIT_INDEX]; 
		if (result.node->parent == NULL){
            //最顶层
            newRoot(T, result.node, ap, k, result.node->recptr[SPLIT_INDEX]);
            k = -1;
            result.node->recptr[SPLIT_INDEX] = NULL;
        }
		else {
			int index = Search(result.node->parent, k); //在双亲结点中查找k的插入位置
			Insert(result.node->parent, k, index, ap, result.node->recptr[SPLIT_INDEX]);
		}
        result.node = result.node->parent; //上移一层
        if(result.node==NULL) break;
    }
    return 1;
}

void split(BTree &q, BTree &ap){
    //将q结点分裂成两个结点，前一半保留在原节点，另一半移入ap所指向的新节点
    int i, j, n = q->keynum;
    ap = (BTNode*)malloc(sizeof(BTNode));   //生成新结点
    InitBTNode(ap);
    ap->ptr[0] = q->ptr[SPLIT_INDEX];
    for(i = SPLIT_INDEX + 1, j = 1; i<=n;i++,j++){  //后一半移入ap结点
        ap->key[j] = q->key[i];
        ap->ptr[j] = q->ptr[i];
        ap->recptr[j] = q->recptr[i];
        q->key[i] = -1;
        q->ptr[i] = NULL;
        q->recptr[i] = NULL;
    }
    ap->keynum = n-SPLIT_INDEX;
    ap->parent = q->parent;
    for(i=0;i<=n-SPLIT_INDEX;i++)   //修改新结点的子节点的parent域
        if(ap->ptr[i]!=NULL) ap->ptr[i]->parent = ap;
    q->keynum = SPLIT_INDEX - 1;    //q的前一半保留，修改keynum
    return;
}

void newRoot(BTree &t, BTree p, BTree ap, int k, Record rcd){      //生成新的根节点 p是左子树 ap是右子树
    t = (BTNode*)malloc(sizeof(BTNode));
    t->keynum = 1;
    t->ptr[0] = p;
    t->ptr[1] = ap;
    t->key[1] = k;
    t->recptr[1] = rcd;
    if(p!=NULL) p->parent = t;
    if(ap!=NULL) ap->parent = t;
    t->parent = NULL;   //新根的双亲是空指针
}

void Insert(BTree &q, int k, int index, BTree ap, Record rcd){
    //关键字k和新结点指针ap分别插入到q->key[i]和q->ptr[i]
    int i;
    //将待插入结点后的所有结点后移
    for(i = q->keynum; i>=index; i--){
        q->key[i+1] = q->key[i];
        q->ptr[i+1] = q->ptr[i];
        q->recptr[i+1] = q->recptr[i];
    }
    q->key[index] = k;
    q->ptr[index] = ap;
    q->recptr[index] = rcd;
    if(ap!=NULL) ap->parent = q;
    q->keynum++;
    return;
}


