#include "include/includes.h"


int main(int argc, const char** argv) {
    BTree T;
    InitBTNode(T);
    record rcd[7];
    rcd[0].data = 24;
    rcd[1].data = 10;
    rcd[2].data = 30;
    rcd[3].data = 4;
    rcd[4].data = 25;
    rcd[5].data = 44;
    rcd[6].data = 59;
    
    int k[7];
    for(int i = 0;i<7;i++) k[i] = i;
    for(int j = 0;j<7;j++){
        InsertBTree(T, k[j], &rcd[j]);
        }
    // TraverseBTree(T);
    // PrintBTree(T);
    // DeleteBTree(T, 2);
    // TraverseBTree(T);
    PrintBTree(T);
    // DeleteBTree(T, 2);
    // PrintBTree(T);
    // DeleteBTree(T, 5);
    PrintBTree(T);
    result r;
    SearchBTree(T,1,r);
    result r1;
    SearchBTree(T,6,r1);
    // DestroyBTree(T);
    getchar();
    return 0;
}

