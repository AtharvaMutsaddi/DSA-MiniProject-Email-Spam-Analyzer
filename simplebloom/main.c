#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"bloomfilter.h"
#define ll long long
#define MAX_DOMAIN_SIZE 40

bloomfilter * trainfilter(){
    bloomfilter * bf;
    bf=init(bf);
    FILE * spamEmailIDs=fopen("./archive/spamemailIDs.txt","r");
    char mailID[MAX_DOMAIN_SIZE];
    int i=1;
    while (!feof(spamEmailIDs) && !ferror(spamEmailIDs))
    {
        if (fgets(mailID, MAX_DOMAIN_SIZE, spamEmailIDs) !=NULL)
        {
            
            ll encryptedstr=encrypt(mailID);
            int bit1=hash1(encryptedstr);
            int bit2=hash2(encryptedstr);
            int bit3=hash3(encryptedstr);
            feed(bf->bitarray, bit1, bit2, bit3);
            i++;
        }
    }
    return bf;
}
float modelAccuracy(bloomfilter * bf){
    int answerkey[81];
    FILE * answers=fopen("./archive/answers.csv","r");
    char garbage[6];
    fgets(garbage,5,answers);
    int i=0;
    char buffer[3];
    while (!feof(answers) && !ferror(answers))
    {
        if (fgets(buffer, 3, answers) !=NULL)
        {
            answerkey[i]=atoi(buffer);
            i++;
        }
    }
    
    FILE * testEmailIDs=fopen("./archive/testemailIDs.csv","r");
    char mailID[MAX_DOMAIN_SIZE];
    float score=0;
    fgets(garbage,5,testEmailIDs);
    i=0;
    while (!feof(testEmailIDs) && !ferror(testEmailIDs))
    {
        if (fgets(mailID, MAX_DOMAIN_SIZE, testEmailIDs) !=NULL)
        {
            int ans=isSpam(mailID,bf);
            if (ans==answerkey[i])
            {
                score++;
            }
            else
            {
                printf("model failed at %s as test input\n",mailID);
            }
            
            i++;
            
        }
    }
    float finalscore= ((score)/(81.00))*100;
    return finalscore;
}

int main(){
    printf("Loading Bloom...\n");
    bloomfilter * bf=NULL;
    bf=trainfilter();
    // printbloom(bf);
    printf("\n-------------------------------------------------------\n");
    printf("Your model is %f percent accurate\n",modelAccuracy(bf));
    return 0;
}