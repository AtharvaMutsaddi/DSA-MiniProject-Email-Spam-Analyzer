#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bloomfilter.h"
#define ll long long
#define MAX_DOMAIN_SIZE 100

matrixbf *trainfilter()
{
    matrixbf *mbf;
    mbf = init(mbf);
    FILE *spamEmailIDs = fopen("./archive/spamemailIDs.txt", "r");
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
    int answerkeysize = 86;
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
        if (!strcmp(username, "gmail.com") || !strcmp(username, "coep.ac.in") || strstr(username, "yahoo") != NULL)
        {
            ans = 0;
        }
        return ans;
    }
    else
    {
        ans = isSpam(domain, mbf);
        if (!strcmp(domain, "gmail.com") || !strcmp(domain, "coep.ac.in") || strstr(domain, "yahoo") != NULL)
        {
            ans = 0;
        }
        return ans;
    }
}
int main()
{
    // printf("Loading Bloom...\n");
    matrixbf *mbf = NULL;
    mbf = trainfilter();
    printmbf(mbf);
    // printf("\n-------------------------------------------------------\n");
    // printf("Your model is %f percent accurate\n", modelAccuracy(mbf));
    // printf("%d,%d,%f\n",BLOOM_ROWS,BLOOM_COLS, modelAccuracy(mbf));

    char mailID[MAX_DOMAIN_SIZE];
    scanf("%s",mailID);
    printf("%d\n",evaluate(mailID, mbf));

    return 0;
}