//author:chenlin
#include <stdio.h>
int user_operation;
BT HuffTree , NewHuffTree;
void menu() {
    printf("==============================================\n");
    printf("          输入对应的数字执行程序功能：\n");
    printf("1) 查看哈夫曼树\n");
    printf("2) 打印字符对应的哈夫曼编码\n");
    printf("3) 打印 'THIS PROGRAM IS MY FAVPRITE'的编码 \n");
    printf("4) 根据(3)的编码,输入01字符串进行验证编码\n");
    printf("4) 根据(3)的编码,输入01字符串进行解码\n");
    printf("6) 退出程序\n");
    printf("==============================================\n");
    printf("请输入选项前的数字：\n");
    scanf("%d", &user_operation);
    switch (user_operation)
    {
    case 1:
        system("cls");
        DrawTheTree(HuffTree);
        menu();
        break;
    case 2:
        system("cls");
        Encode(HuffTree);
        menu();
        break;
    case 3:
        system("cls");
        DrawTheTree(NewHuffTree);
        Encode(NewHuffTree);
        menu();
        break;
    case 6:
        return ;
    default:
        printf("输入有误，请检查\n");
        system("cls");
        menu();
        break;
    }
}