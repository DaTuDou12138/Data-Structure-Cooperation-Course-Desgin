//author: chenlin

#ifndef LNODE_H     
#define LNODE_H

typedef void module ;

struct BinaryTree;
typedef struct BinaryTree* BT;

typedef struct LNode {
    char data; 
    int freq; 
    BT HuffTree;
    char Code[20];
    struct LNode *next; 
}LNode , *PtrToNode; 
typedef PtrToNode List;
typedef PtrToNode Position; 

//初始、增删；

List InitializeList(List head) { 
    head = (List)malloc(sizeof(LNode)); 
    head->next = NULL; 
    return head; 
}

void InsertList(List L,char ch,int frq,BT T,const char *Code){
    if (frq == 0) return;
    Position p = L;
    while(p->next){
        p=p->next;
    }
    List q = (List)malloc(sizeof(LNode));
    q ->data = ch; q->freq=frq;q->HuffTree = T; q->next = NULL ; 
     if(Code) {
        strncpy(q->Code, Code, sizeof(q->Code)-1);
        q->Code[sizeof(q->Code)-1] = '\0';
    } else {
        q->Code[0] = '\0';  // 处理空编码的情况
    }   
    p->next = q;
}

void DeleteList(List L, Position ptr) {
    Position prev = L;
    while (prev->next && prev->next != ptr) {
        prev = prev->next;
    }
    if (prev->next) {
        prev->next = ptr->next;
        free(ptr);
    }
}

Position GetPtrofTheMinFreq(List L){
    int minfrq=999 ; Position ptr_min;
    Position p = L; p=p->next;
    while(p){
        if(p->freq<minfrq){
            minfrq = p->freq;
            ptr_min = p;
        }
        p=p->next;
    }
    return ptr_min;
}

module ImportFreqDataToList(int *arr,List L){
    // `将数组的元素插入链表
    int i = 0; InsertList(L, ' ', arr[i],NULL,"");
    for(i = 1; i<27 ; i++){
        InsertList(L, 'A'+i-1, arr[i],NULL,"");
    }
    return ;
}

module ImportLetterDataToList(char* ch,List L) {
    int cnt=0;
    int arr[27] = { 0 };
    while (ch[cnt]) {
        if(ch[cnt]==' '){
            arr[0] += 1;
            cnt++;
        }else{
            arr[(int)ch[cnt]-64] += 1;
            cnt++;
        }
    }
    ImportFreqDataToList(arr, L);
    
        
}
#endif