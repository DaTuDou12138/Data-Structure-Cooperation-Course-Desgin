// author: chenlin
#include <stdio.h>
#include <stdlib.h>
#include <easyx.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include "LNode.h"
#include "BinaryTree.h"
#include "menu.h"

using namespace std;

int main()
{
    /*
    此部分代码主要作用是将题目的数据存为数组，再依次构建成链表
    目的：方便在构建哈夫曼时删除节点，也便于在节点被删除后,依旧正确存储字母所对应的频率
    */
    char ch[1000] = {"THIS PROGRAM IS MY FAVORITE"};
    int arr[27] = {186, 64, 13, 22, 32, 103, 21, 15, 47, 57, 1, 5, 32, 20, 57, 63, 15, 1, 48, 51, 80, 23, 8, 18, 1, 16, 1};
    List QuestionOfferData,NewData;
    QuestionOfferData = InitializeList(QuestionOfferData); NewData = InitializeList(NewData);
    ImportFreqDataToList(arr, QuestionOfferData);
    ImportLetterDataToList(ch, NewData);
    /*
    此部分代码用于构建哈夫曼树
    */
    HuffTree = CreateHuffmanTree(QuestionOfferData);
    NewHuffTree = CreateHuffmanTree(NewData);
    
    menu();
    

return 0;
}
