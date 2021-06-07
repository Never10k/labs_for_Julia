#include "main.h"

void TestCountVovels(char *word, int wordSize, int expectedResult);
int TestInsertFree(char *testWord, int vovels);
int TestCheckFileExists(char *testname, char *whatToPrint);
int TestInputOutput(char *filename, int expectedResult);

#undef main
int main()
{
    TestCountVovels("LongWord", 8, 2);
    TestCountVovels("ThRsNvVlS", 9, 0);
    TestCountVovels("SomeKindOFWEIRDOwordidkwhatsthat", 32,11);

    TestInsertFree("someKINDofWORD",14);

    TestCheckFileExists("test1.txt", "Some Words are here like precision and suspicious");
    TestCheckFileExists("test2.txt", "precisionless and suspiciousness");

    TestInputOutput("test1.txt", 2);
    TestInputOutput("test2.txt", 4); 

}

void TestCountVovels(char *word, int wordSize, int expectedResult)
{
    assert(CountVovels(word, wordSize) == expectedResult);
}

int TestInsertFree(char *testWord, int wordSize)
{
    treeNode *head;
    head = NULL;

    int vovels = CountVovels(testWord, wordSize);

    assert((InsertNode(&head,testWord,vovels)) == true);
    assert((head->right) == NULL);
    assert((head->left) == NULL);
    assert((head->vovelsNumber) == vovels);

    int i;
    for (i = 0; i<wordSize; i++)
    {
        assert(testWord[i] == (head->word)[i]);
    }

    TreeFree(&head);

    assert(head == NULL);
    return 0;
}

int TestCheckFileExists(char *testname, char *whatToPrint)
{
    FILE *file;
    file = fopen(testname, "w");
    fprintf(file, "%s", whatToPrint);
    fclose(file);

    assert(CheckFileExists(testname) == true);
    return 1;
}

int TestInputOutput(char *filename, int expectedResult)
{
    treeNode *head;
    head = NULL;
    Input(filename, &head);
    assert(ResultOutput(head) == expectedResult);
    return 0;
}