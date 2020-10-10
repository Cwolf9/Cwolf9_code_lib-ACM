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
    L.elem = (char*)malloc(sizeof(char)*n);//����ռ�
    for(i = 0; i < n; ++i) {
        L.elem[i] = s[i];//��ֵ
    }
    L.length = n;
    return OK;
}
Status InsertList(SqList &L, int p, char v) {
    //�Ϸ��Ĳ���λ����[1, L.length + 1]
    if(p < 1 || p > L.length + 1) return ERROR;//����λ�ò��Ϸ�
    int i;
    char *newBase = (char*)malloc(sizeof(char)*(L.length + 1));//�µĿռ�
    for(i = 0; i < L.length; ++i) newBase[i] = L.elem[i];
    free(L.elem);//�ͷžɵĿռ�
    L.elem = newBase;
    L.length ++;
    for(i = L.length - 1; i >= p; --i) {//��λ��[p,L.length-1]��Ԫ�غ���һλ
        L.elem[i] = L.elem[i - 1];
    }
    L.elem[p - 1] = v;
    return OK;
}
Status DelList(SqList &L, int p) {
    if(p < 1 || p > L.length) return ERROR;
    int i;
    for(i = p - 1; i < L.length; ++i) {//��λ��[p,L.length]��Ԫ��ǰ��һλ
        L.elem[i] = L.elem[i + 1];
    }
    L.length --;
    return OK;
}

Status MergeList(SqList &L) {
    if(L.length < 9) return ERROR;//ȷ�����Ա��ȴ��ڵ���9����merge
    int id1[5] = {1, 3, 5, 7, 9};//��Ҫ�ϲ����±�1
    int id2[3] = {2, 3, 6};//��Ҫ�ϲ����±�2
    char *newBase3 = (char*)malloc(sizeof(char)*(8));
    int i, j;
    for(i = 0; i < 5; ++i) newBase3[i] = L.elem[id1[i] - 1];
    for(i = 0; i < 3; ++i) newBase3[5 + i] = L.elem[id2[i] - 1];
    free(L.elem);
    L.elem = newBase3;
    L.length = 8;
    for(j = 0; j < L.length; ++j) {//�ϲ�������
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
void OutputList(SqList &L) {//������Ա�
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
    printf("�������Ա����£�\n");
    CreateList(L, str, 8);//����
    OutputList(L);//���
    printf("������λ�ò���p��\n");
    InsertList(L, 3, 'p');//����
    OutputList(L);//���
    printf("ɾ��������λ��Ԫ�أ�\n");
    DelList(L, 3);//ɾ��
    OutputList(L);//���
    printf("������λ�ò���p��\n");
    InsertList(L, 3, 'p');//����
    OutputList(L);//���
    printf("�����Ա�1��3��5��7��9��2��3��6�ϲ����ϲ���Ϊ�ǵݼ����Ա�\n");
    MergeList(L);//�ϲ�
    OutputList(L);//���
    return 0;
}