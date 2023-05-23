#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26

typedef struct TrieMap
{
    // array of children
    struct TrieMap *children[ALPHABET_SIZE];
    double weightage;
    
} TrieMap;

TrieMap *initTrieMap(TrieMap *TrieMapNode)
{
    TrieMapNode = (TrieMap *)malloc(sizeof(TrieMap));
    TrieMapNode->weightage = 0.0;
}
void insertTrieMap(TrieMap *TrieMapNode, const char *word, double weightage)
{
    int len = strlen(word);
    TrieMap *currNode = TrieMapNode;
    for (int i = 0; i < len; i++)
    {
        // check if null
        if (!currNode->children[word[i] - 'a'])
        {
            currNode->children[word[i] - 'a'] = initTrieMap(currNode);
        }
        currNode = currNode->children[word[i] - 'a'];
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
        if (!currNode->children[word[i] - 'a'])
        {
            return 0;
        }
        currNode = currNode->children[word[i] - 'a'];
    }
    return currNode->weightage;
}
int main()
{
    TrieMap * tm=NULL;
    tm=initTrieMap(tm);
    int corpus_size = 0;
    // Open the file in read mode
    FILE *file;
    file = fopen("word_to_freq.csv", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 0;
    }
    char ch;
    // Count the number of lines
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n')
            corpus_size++;
    }
    // printf("Corpus Size:%d\n",corpus_size);
    file = fopen("word_to_freq.csv", "r");
    char line[50];
    char * word;
    int freq;
    while (fgets(line,50,file))
    {
        word = strtok(line, ",");
        freq= atoi(strtok(NULL, ","));
        double weightage=(freq/(double)corpus_size);
        insertTrieMap(tm,word,weightage);
    }
    // printf("successfully loaded trie\n");
    FILE * emails;
    emails=fopen("preprocessed_emails.txt","r");
    char email[1000000];
    int i=1;
    while (fgets(email,1000000,emails))
    {
        double score=0.0;
        long long size=1ll;
        char * token=strtok(email," ");
        while (token)
        {
            if(token != " \n"){
                score+=searchTrieMap(tm,token);
            }
            token=strtok(NULL," \n");
            size++;
        }
        printf("Email %d,%f\n",i,(score/size));
        i++;
        
    }
    
    
    return 0;
}
