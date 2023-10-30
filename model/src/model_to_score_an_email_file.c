#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "model_to_score_an_email_file.h"
#define ALPHABET_SIZE 26
#define QUARTILE_1 0.000433
#define QUARTILE_3 0.001133

void insertTrieMap(TrieMap *TrieMapNode, const char *word, double weightage)
{
    int len = strlen(word);
    TrieMap *currNode = TrieMapNode;
    for (int i = 0; i < len; i++)
    {
        // check if null
        if (isalpha(word[i]))
        {
            if (!currNode->children[word[i] - 'a'])
            {
                currNode->children[word[i] - 'a'] = initTrieMap(currNode);
            }
            currNode = currNode->children[word[i] - 'a'];
        }
    }
    currNode->weightage = weightage;
}
double searchTrieMap(TrieMap *TrieMapNode, const char *word)
{
    int len = strlen(word);
    TrieMap *currNode = TrieMapNode;
    for (int i = 0; i < len; i++)
    {
        // check if null
        if (isalpha(word[i]))
        {
            if (!currNode->children[word[i] - 'a'])
            {
                return 0;
            }
            currNode = currNode->children[word[i] - 'a'];
        }
    }
    return currNode->weightage;
}
TrieMap *initTrieMap(TrieMap *TrieMapNode)
{
    TrieMapNode = (TrieMap *)malloc(sizeof(TrieMap));
    TrieMapNode->weightage = 0.0;
}