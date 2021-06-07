#include <stddef.h> /*для работы NULL*/
#include <assert.h> /*работа assert */
#include <stdlib.h> /*malloc*/
#include <stdbool.h> /*в С89 нет bool */
#include <stdio.h> /*printf*/

typedef struct treeNode
{
    char *word; /*Само слово*/
    int vovelsNumber; /*гласные*/

    struct treeNode *left; /*указатели на следующие узлы*/
    struct treeNode *right;

} treeNode;

/*Вставка узла, true - удалось*/
bool InsertNode(treeNode **head, char *newWord, int vovels);

/*освобождение памяти перед выходом*/
void TreeFree(treeNode **head);

/*Считает количество гласных в слове*/
int CountVovels(char *word, int wordSize);

/*Проверка на то, лежит ли в папке нужный файл с текстом*/
bool CheckFileExists(char *filename);

/*считывание + заполнение дерева*/
int Input(char *filename, treeNode **head);

/*Вывод согласно варианту*/
void ResultOutput(treeNode *head);



