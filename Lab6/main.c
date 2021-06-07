#include "main.h"

int main()
{
    treeNode *head;
    head = NULL;
    
    Input("data.txt", &head);

    ResultOutput(head);

    TreeFree(&head);

    system("pause");
    return 0;
}

bool InsertNode(treeNode **head, char *newWord, int vovels)
{
    /*если дерево пусто - вставляем в корень*/
/*такое количество звёздочек, чтобы не создавались копии, а менялись значения аргументов*/
    if ((*head) == NULL)
    {
        /*выделяем память и сразу проверяем, что память выделилась*/
        assert(((*head) = (treeNode*)malloc(sizeof(treeNode))) != NULL);

        (*head)->left = NULL;
        (*head)->right = NULL;
        (*head)->word = newWord;
        (*head)->vovelsNumber = vovels;
    }
    else
    {
        /*пусть все нужные элементы в правых узлах, остальные - в левых*/
        /*Позже алгоритм поиска нужных слов сильно упростится*/
        if(vovels >= 3)
        {
            InsertNode(&((*head)->right),newWord,vovels);
        }
        else
        {
            InsertNode(&((*head)->left),newWord,vovels);
        }
    }
    return true;
}

int CountVovels(char *word, int wordSize)
{
    int i, result = 0;
    for (i = 0; i< wordSize; i++)
    {
        if (word[i] == 'a' || word[i] == 'A' ||
            word[i] == 'e' || word[i] == 'E' ||
            word[i] == 'y' || word[i] == 'Y' || /*6 гласных в латинице*/
            word[i] == 'u' || word[i] == 'U' ||
            word[i] == 'i' || word[i] == 'I' ||
            word[i] == 'o' || word[i] == 'O')
        {
            result++;
        }
    }
    return result;
}

bool CheckFileExists(char *filename)
{
    FILE *file;
    file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("There was an error opening %s\n", filename);
        return false;
    }
    fclose(file);
    return true;
}

int Input(char *filename, treeNode **head)
{
    FILE *file;
    char bufferWord[256]; /*временное хранилище слова*/

    assert(CheckFileExists(filename) == true);
    /*ошибка чтения может возникнуть и с существующим файлом*/
    assert((file = fopen(filename, "r")) != NULL);

    char c;
    char *wordToInsert;
    int size, i, vovels;
    while (!feof(file))
    {
        size = 0;
        /*cчитываем слово, закидываем в дерево, идём дальше*/
        while((c = fgetc(file)) != ' ' && !feof(file) && c != '.' && c != ',')
        {
            bufferWord[size] = c;
            size++;
        }
        
        assert((wordToInsert = (char*)malloc(size*sizeof(char))) != NULL);
        for (i = 0; i<size; i++)
        {
            wordToInsert[i] = bufferWord[i];
        }
        vovels = CountVovels(wordToInsert, size);
        InsertNode(head, wordToInsert, vovels);
        /*Теперь внутри дерева есть указатель на наше слово, нужно "открепить"*/
    /*указатель, то есть зануляем его, чтобы на след шаге снова выделить память*/
        wordToInsert = NULL;
        /*при необходимости можно добавить сюда счётчик слов и в return*/
    }

    fclose(file);
    return 1;
}

void TreeFree(treeNode **head)
{
    if ((*head) == NULL)
    {
        return;
    }
    TreeFree(&((*head)->right));
    TreeFree(&((*head)->left));
    free(*head);
}

void ResultOutput(treeNode *head)
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        if (head->vovelsNumber>=3)
        {
            printf("Word: %s, vovels here: %d\n",head->word, head->vovelsNumber);
        }
        ResultOutput(head->right);
    }
}

