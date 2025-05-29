// author: chenlin

#define RESOLUTION_WEIGHT 1280
#define RESOLUTION_HEIGHT 720
#define R 15


typedef void module;
typedef struct BinaryTree
{
    int freq;
    char ch;
    struct BinaryTree *lchild;
    struct BinaryTree *rchild;

} *PtrToTree;
typedef PtrToTree BT;
typedef PtrToTree Leaf;

BT CreateHuffmanTree(List L)
{
    BT head;
    while (L->next->next)
    {        
        // 父亲节点的声明
        Leaf parent = (BT)malloc(sizeof(struct BinaryTree));
        parent->ch = '\0';
       // 保存关键数据到局部变量
        Position lftptr = GetPtrofTheMinFreq(L);
        int savedLftFreq = lftptr->freq;
        char savedLftChar = lftptr->data;
        BT savedLftTree = lftptr->HuffTree;
        DeleteList(L, lftptr);  // 立即删除并释放内存

        // 使用保存的数据创建新节点
        if (!savedLftTree) {
            Leaf lchild = (BT)malloc(sizeof(struct BinaryTree));
            lchild->freq = savedLftFreq;  // 使用局部变量
            lchild->ch = savedLftChar;    // 使用局部变量
            lchild->lchild=NULL;lchild->rchild=NULL;
            parent->lchild = lchild;
        } else {
            parent->lchild = savedLftTree;
        }
        
        // 保存关键数据到局部变量
        Position rgtptr = GetPtrofTheMinFreq(L);
        int savedRgtFreq = rgtptr->freq;
        char savedRgtChar = rgtptr->data;
        BT savedRgtTree = rgtptr->HuffTree;
        DeleteList(L, rgtptr);  // 立即删除并释放内存
        // 使用保存的数据创建新节点
        if (!savedRgtTree) {
            Leaf rchild = (BT)malloc(sizeof(struct BinaryTree));
            rchild->freq = savedRgtFreq;  // 使用局部变量
            rchild->ch = savedRgtChar;    // 使用局部变量
            rchild->lchild = NULL; rchild ->rchild =NULL;
            parent->rchild = rchild;
        } else {
            parent->rchild = savedRgtTree;
        }

        // 整合父亲节点，将其插回链表
        parent->freq = (savedLftFreq + savedRgtFreq);
        InsertList(L,'\0', parent->freq, parent,NULL);
        //重新调整头结点
        head=parent;
    }
    return head;
}

int CaculatetheLengthforchild(BT T,int whichchild){
    int llength = 0 ,rlength = 0;
    if(!T) return 0;
    if(T->lchild){
        llength = CaculatetheLengthforchild(T->lchild,whichchild)-(whichchild*1);
    }
    if(T->rchild){
        rlength = CaculatetheLengthforchild(T->rchild,whichchild)+(whichchild*1);
    }
    if(llength < 0 ) llength =0;
    if(rlength < 0) rlength =0;

    return llength > rlength ? llength : rlength;
}


void DrawTheLeaf(BT T,int x , int y,int level) {
    int textx = x - 15, texty = y - 7;
    int newxfloat;
    if (T) {
        if (level == 1){
            newxfloat = RESOLUTION_WEIGHT/4;
        }else{
            newxfloat = (CaculatetheLengthforchild(T->lchild,1)+CaculatetheLengthforchild(T->rchild,-1)+1)*1.5*R;
        }
        if (T->lchild) {
            line(x,y,x-newxfloat,y+45);
            DrawTheLeaf(T->lchild, x - newxfloat, y + 45,level+1);
        }
        if (T->rchild) {
            if(T->rchild->freq == 63){
                newxfloat = 2*R;
            }
            line(x,y,x+newxfloat,y+45);
            DrawTheLeaf(T->rchild, x + newxfloat, y + 45,level+1);
        }
        fillcircle(x, y, R);
        // 输出数值，先将数字格式化输出为字符串（MBCS 字符集）
        char s[16];
        if(T->ch == ' ') {  // 特定处理空格字符
            snprintf(s, sizeof(s), "%d:空格", T->freq);
        } else if(T->ch) {   // 其他字符正常显示
            snprintf(s, sizeof(s), "%d:%c", T->freq, T->ch);
        } else {            // 中间节点只显示频率
            snprintf(s, sizeof(s), "%d", T->freq);
        }
        outtextxy(textx, texty, s);
        
    }
}

// 绘制哈夫曼树
module DrawTheTree(BT T) {
    initgraph(RESOLUTION_WEIGHT,RESOLUTION_HEIGHT);
    setbkcolor(WHITE);
    cleardevice();
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    settextcolor(BLACK);
    setfont(18, 0, "微软雅黑Light");
    DrawTheLeaf(T, RESOLUTION_WEIGHT/2, 30,1);
    _getch();				// 按任意键继续
    closegraph();
}

void EncodeOutPut(BT T, char *code, List L) {
    if (!T) return;
    char RecursionCode[20];
    strcpy(RecursionCode, code);
    if (T->ch) {
        // 叶子节点时保存编码
        InsertList(L, T->ch, T->freq, NULL, RecursionCode);
        return;
    }

    if (T->lchild) {
        // 创建新的独立副本
        char leftCode[20];
        strcpy(leftCode, code);
        strcat(leftCode, "0");
        EncodeOutPut(T->lchild, leftCode,  L);
    }

    if (T->rchild) {
        // 创建新的独立副本
        char rightCode[20];
        strcpy(rightCode, code);
        strcat(rightCode, "1");
        EncodeOutPut(T->rchild, rightCode,  L);
    }
}

void Encode(BT T) {
    List Result;
    Result = InitializeList(Result);
    EncodeOutPut(T,"", Result);  // 初始编码为0，深度为0
    Result=Result->next;
    while(Result){
        if(Result->data == ' '){
            printf("字符'空格'编码结果：%s\n",Result->Code);
            Result=Result->next;
        }else{
            printf("字符'%c'编码结果：%s\n",Result->data,Result->Code);
            Result=Result->next;
        }
    }
}