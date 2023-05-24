#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "bloomfilter.h"
#define ll long long
#define MAX_DOMAIN_SIZE 100
#define ALPHABET_SIZE 26
#define QUARTILE_1 0.000433
#define QUARTILE_3 0.001133
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
matrixbf *trainfilter()
{
    matrixbf *mbf;
    mbf = init(mbf);
    FILE *spamEmailIDs = fopen("spamemailIDs.txt", "r");
    char mailID[MAX_DOMAIN_SIZE];
    int i = 1;
    while (!feof(spamEmailIDs) && !ferror(spamEmailIDs))
    {
        if (fgets(mailID, MAX_DOMAIN_SIZE, spamEmailIDs) != NULL)
        {

            ll encryptedstr;
            int bit1;
            int bit2;
            int bit3;
            int bit4;
            int bit5;
            int bit6;

            char username[MAX_DOMAIN_SIZE];
            char domain[MAX_DOMAIN_SIZE];

            bool isfound = false;
            int x = 0, y = 0;
            for (int j = 0; j < strlen(mailID); j += 1)
            {
                char ch = mailID[j];
                if (ch == '@')
                {
                    isfound = true;
                    continue;
                }
                if (isfound == false)
                {
                    username[x++] = ch;
                }
                else
                {
                    domain[y++] = ch;
                }
            }

            username[x] = '\0';
            domain[y] = '\0';
            // printf("Fed username: %s, domain: %s\n", username, domain);
            if (strlen(domain) == 0)
            {
                encryptedstr = encrypt(username);
                bit1 = hash1(encryptedstr);
                // printf("Bit1:%d\n",bit1);
                bit2 = hash2(encryptedstr);
                // printf("Bit2:%d\n",bit2);
                bit3 = hash3(encryptedstr);
                // printf("Bit3:%d\n",bit3);
                bit4 = hash4(encryptedstr);
                // printf("Bit4:%d\n",bit4);
                bit5 = hash5(encryptedstr);
                // printf("Bit5:%d\n",bit5);
                bit6 = hash6(encryptedstr);
                // printf("Bit6:%d\n",bit6);
                feed(mbf->matrix, bit1, bit2, bit3,bit4,bit5,bit6);
            }
            else
            {
                encryptedstr = encrypt(domain);
                bit1 = hash1(encryptedstr);
                // printf("Bit1:%d\n",bit1);
                bit2 = hash2(encryptedstr);
                // printf("Bit2:%d\n",bit2);
                bit3 = hash3(encryptedstr);
                // printf("Bit3:%d\n",bit3);
                bit4 = hash4(encryptedstr);
                // printf("Bit4:%d\n",bit4);
                bit5 = hash5(encryptedstr);
                // printf("Bit5:%d\n",bit5);
                bit6 = hash6(encryptedstr);
                // printf("Bit6:%d\n",bit6);
                feed(mbf->matrix, bit1, bit2, bit3,bit4,bit5,bit6);
            }

            i++;
        }
    }
    return mbf;
}
int evaluate(char *mailId, matrixbf *mbf);
float modelAccuracy(matrixbf *mbf)
{
    int answerkeysize = 70;
    int answerkey[answerkeysize];
    FILE *answers = fopen("./archive/answers.csv", "r");
    int i = 0;
    char buffer[3];
    while (!feof(answers) && !ferror(answers))
    {
        if (fgets(buffer, 3, answers) != NULL)
        {
            answerkey[i] = atoi(buffer);
            i++;
        }
    }

    FILE *testEmailIDs = fopen("./archive/testemailIDs.csv", "r");
    char mailID[MAX_DOMAIN_SIZE];
    float score = 0;
    i = 0;
    while (!feof(testEmailIDs) && !ferror(testEmailIDs))
    {
        if (fgets(mailID, MAX_DOMAIN_SIZE, testEmailIDs) != NULL)
        {
            int ans = evaluate(mailID, mbf);
            if (ans == answerkey[i])
            {
                score++;
            }
            i++;
        }
    }
    float finalscore = ((score) / ((float)answerkeysize)) * 100;
    return finalscore;
}
int evaluate(char *mailID, matrixbf*mbf)
{
    char username[MAX_DOMAIN_SIZE];
    char domain[MAX_DOMAIN_SIZE];

    bool isfound = false;
    int x = 0, y = 0;
    for (int j = 0; j < strlen(mailID); j += 1)
    {
        char ch = mailID[j];
        if (ch == '@')
        {
            isfound = true;
            continue;
        }
        if (isfound == false)
        {
            username[x++] = ch;
        }
        else
        {
            domain[y++] = ch;
        }
    }

    username[x] = '\0';
    domain[y] = '\0';
    // ans1
    int ans;
    if (strlen(domain) == 0)
    {
        ans = isSpam(username, mbf);
        if (strstr(username, "gmail.com")!=NULL || strstr(username, "coep") !=NULL || strstr(username, "yahoo") != NULL)
        {
            ans = 0;
        }
        return ans;
    }
    else
    {
        ans = isSpam(domain, mbf);
        if (strstr(domain, "gmail.com")!=NULL || strstr(domain, "coep") !=NULL || strstr(domain, "yahoo") != NULL)
        {
            ans = 0;
        }
        return ans;
    }
}

int main(int argc, char const *argv[])
{
    // +++++++++++++++++++++++++++++EMAIL ID ANALYZER+++++++++++++++++++++++++++
    printf("Loading Bloom...\n");
    printf("\n----------ANALYZING THE SENDER'S EMAIL ID:---------------\n");
    matrixbf *mbf = NULL;
    mbf = trainfilter();
    FILE *emails;
    emails = fopen(argv[1], "r");
    if(!emails){
        perror("Couldn't find file in current repo...");
        return 1;
    }
    char mailID[MAX_DOMAIN_SIZE];
    fgets(mailID,MAX_DOMAIN_SIZE,emails);
    if(evaluate(mailID, mbf)){
        printf("The senders domain: %s seems suspicious.\n",mailID);
    }
    else{
        printf("The senders domain: %s seems ok.\n",mailID);
    }
    // +++++++++++++++++++++++++++++EMAIL CONTENTS ANALYZER+++++++++++++++++++++++++++
    printf("\n----------ANALYZING THE EMAIL CONTENTS:---------------\n");
    TrieMap *tm = NULL;
    tm = initTrieMap(tm);
    int corpus_size = 0;
    // Open the file in read mode
    FILE *file;
    file = fopen("word_to_freq.csv", "r");
    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        return 0;
    }
    char ch;
    // Count the number of lines
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
            corpus_size++;
    }
    // printf("Corpus Size:%d\n",corpus_size);
    file = fopen("word_to_freq.csv", "r");
    char line[50];
    char *word;
    int freq;
    while (fgets(line, 50, file))
    {
        word = strtok(line, ",");
        freq = atoi(strtok(NULL, ","));
        double weightage = (freq / (double)corpus_size);
        insertTrieMap(tm, word, weightage);
    }
    printf("successfully loaded trie\n");
    char email[1000000];
    int i = 1;
    while (fgets(email, 1000000, emails))
    {
        double score = 0.0;
        long long size = 1ll;
        char *token = strtok(email, " ");
        while (token)
        {
            if (token != " \n")
            {
                score += searchTrieMap(tm, token);
            }
            token = strtok(NULL, " \n");
            size++;
        }
        printf("Email score: %f\n", (score / size));
        if ((score / size) < QUARTILE_1)
        {
            printf("Email may not be spam...\n");
        }
        else if ((score / size) >= QUARTILE_1 && (score / size) <= QUARTILE_3)
        {
            printf("Email has moderate chances of being spam...\n");
        }
        else{
            printf("Email is mostly spam...\n");
        }
        
    }

    return 0;
}

