#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define Status bool
#define ERROR false
#define OK true

typedef struct {
    char *elem;
    int length;
}SqList;
Status CreateList(SqList &L, char* s, int n) {
    int i;
    L.elem = (char*)malloc(sizeof(char)*n);//分配空间
    for(i = 0; i < n; ++i) {
        L.elem[i] = s[i];//赋值
    }
    L.length = n;
    return OK;
}
Status InsertList(SqList &L, int p, char v) {
    //合法的插入位置是[1, L.length + 1]
    if(p < 1 || p > L.length + 1) return ERROR;//插入位置不合法
    int i;
    char *newBase = (char*)malloc(sizeof(char)*(L.length + 1));//新的空间
    for(i = 0; i < L.length; ++i) newBase[i] = L.elem[i];
    free(L.elem);//释放旧的空间
    L.elem = newBase;
    L.length ++;
    for(i = L.length - 1; i >= p; --i) {//将位置[p,L.length-1]的元素后移一位
        L.elem[i] = L.elem[i - 1];
    }
    L.elem[p - 1] = v;
    return OK;
}
Status DelList(SqList &L, int p) {
    if(p < 1 || p > L.length) return ERROR;
    int i;
    for(i = p - 1; i < L.length; ++i) {//将位置[p,L.length]的元素前移一位
        L.elem[i] = L.elem[i + 1];
    }
    L.length --;
    return OK;
}

Status MergeList(SqList &L) {
    if(L.length < 9) return ERROR;//确保线性表长度大于等于9才能merge
    int id1[5] = {1, 3, 5, 7, 9};//需要合并的下标1
    int id2[3] = {2, 3, 6};//需要合并的下标2
    char *newBase3 = (char*)malloc(sizeof(char)*(8));
    int i, j;
    for(i = 0; i < 5; ++i) newBase3[i] = L.elem[id1[i] - 1];
    for(i = 0; i < 3; ++i) newBase3[5 + i] = L.elem[id2[i] - 1];
    free(L.elem);
    L.elem = newBase3;
    L.length = 8;
    for(j = 0; j < L.length; ++j) {//合并后排序
        for(i = 0; i < L.length - 1; ++i) {
            if(L.elem[i] > L.elem[i + 1]) {
                char tmp = L.elem[i];
                L.elem[i] = L.elem[i + 1];
                L.elem[i + 1] = tmp;
            }
        }
    }
    return OK;
}
void OutputList(SqList &L) {//输出线性表
    int i;
    for(i = 0; i < L.length; ++i) {
        printf("%c", L.elem[i]);
    }
    printf("\n");
}
int main() {
    SqList L;
    // char *str = "ajcniydu";
    char str[8] = {'a', 'j', 'c', 'n', 'i', 'y', 'd', 'u'};
    printf("创建线性表如下：\n");
    CreateList(L, str, 8);//创建
    OutputList(L);//输出
    printf("第三个位置插入p：\n");
    InsertList(L, 3, 'p');//插入
    OutputList(L);//输出
    printf("删除第三个位置元素：\n");
    DelList(L, 3);//删除
    OutputList(L);//输出
    printf("第三个位置插入p：\n");
    InsertList(L, 3, 'p');//插入
    OutputList(L);//输出
    printf("将线性表1，3，5，7，9和2，3，6合并，合并后为非递减线性表：\n");
    MergeList(L);//合并
    OutputList(L);//输出
    return 0;
}