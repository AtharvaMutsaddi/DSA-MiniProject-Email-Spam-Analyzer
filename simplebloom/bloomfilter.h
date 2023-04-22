#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BLOOM_LEN 1000 // you can modulate this. Maximum size is 1800
#define ll long long

typedef struct bloomfilter
{
    int *bitarray;
} bloomfilter;

bloomfilter *init(bloomfilter *bf)
{
    bf = (bloomfilter *)malloc(sizeof(bloomfilter));
    bf->bitarray = (int *)calloc(BLOOM_LEN, sizeof(int));
}
void printbloom(bloomfilter *bf)
{
    for (int i = 0; i < BLOOM_LEN; i++)
    {
        printf("%d ", bf->bitarray[i]);
    }
    printf("\n");
}
float howMuchFilled(bloomfilter * bf){
    float filledcount=0;
    for (int i = 0; i < BLOOM_LEN; i++)
    {
        if (bf->bitarray[i]==1)
        {
            filledcount++;
        }
        
    }
    return (filledcount/((float)BLOOM_LEN));
}
void feed( int arr[], int bit1, int bit2, int bit3){
    arr[bit1]=1;
    arr[bit2]=1;
    arr[bit3]=1;
}

/*+++++++++++++++++++++++++++FUNCTIONS YOU HAVE TO CODE+++++++++++++++++++++++++++++++++++++++++*/

/*
1) Your encryption Method:(feel free to use any data structures as long as they are not memory intensive)
2) be aware of time complexity
3) Model should be at least 80% accurate
*/

// example:
#define Ch_s(x, y, z) ((x & y) ^ (~x & z))
#define Maj_s(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define MAX_WORD_LEN 50

ll encrypt(char *str)
{
    int len = strlen(str);
    int i=0;
    ll ans=0;
    while (i<len-2)
    {
        if(i%2==0){
            ans+=Ch_s(str[i],str[i+1],str[i+2]);
        }
        else{
            ans+=Maj_s(str[i],str[i+1],str[i+2]);
        }
        i+=3;
    }
    while (i<len)
    {
        if(str[i]=='a' || str[i]=='e' || str[i]=='i'|| str[i]=='o' || str[i]=='u'){
            ans+=(((int)str[i] << 5 || 57)^37);
        }
        else{
            ans+=((int)str[i] >>2 || 57)^36;
        }
        i++;
    }
    return ans;
}
int hash1(ll encryptedstr){
    // int dig1=encryptedstr%10;
    // int dig2=(encryptedstr%100)/10;
    // int dig3=(encryptedstr%1000)/100;

    return (abs(67 + (encryptedstr>>1)*34))%BLOOM_LEN;
}
int hash2(ll encryptedstr){
    int dig1=encryptedstr%10;
    int dig2=(encryptedstr%100)/10;
    int dig3=(encryptedstr%1000)/100;

    return ((dig1<<dig2)|dig3*112)%(BLOOM_LEN);
}
int hash3(ll encryptedstr){
    return ((encryptedstr*2)>>1)%(BLOOM_LEN);
}


int isSpam(char * str, bloomfilter * bf){
    ll encryptedstr=encrypt(str);
    int bit1=hash1(encryptedstr);
    int bit2=hash2(encryptedstr);
    int bit3=hash3(encryptedstr);
    return (bf->bitarray[bit1] && bf->bitarray[bit2] && bf->bitarray[bit3]);
}