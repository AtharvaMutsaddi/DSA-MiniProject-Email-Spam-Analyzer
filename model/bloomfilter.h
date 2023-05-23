#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BLOOM_LEN 1200 // you can modulate this. Maximum size is 1800
#define BLOOM_ROWS 300
#define BLOOM_COLS 4
#define ll long long

// typedef struct bloomfilter
// {
//     int *bitarray;
// } bloomfilter;
typedef struct matrixbloomfilter
{
    int ** matrix;
}matrixbf;

// bloomfilter *init(bloomfilter *bf)
// {
//     bf = (bloomfilter *)malloc(sizeof(bloomfilter));
//     bf->bitarray = (int *)calloc(BLOOM_LEN, sizeof(int));
// }

matrixbf *init(matrixbf *mbf)
{
    mbf=(matrixbf *)malloc(sizeof(matrixbf));
    mbf->matrix=(int **)malloc(sizeof(int *)*BLOOM_ROWS);
    int bloomcols=BLOOM_LEN/BLOOM_ROWS;
    for(int i=0;i<BLOOM_ROWS;i+=1)
    {
        mbf->matrix[i]=(int *)calloc(bloomcols,sizeof(int));
    }
    return mbf;
}

// void printbloom(bloomfilter *bf)
// {
//     for (int i = 0; i < BLOOM_LEN; i++)
//     {
//         printf("%d ", bf->bitarray[i]);
//     }
//     printf("\n");
// }
void printmbf(matrixbf * mbf){
    int bloomcols=BLOOM_LEN/BLOOM_ROWS;
    for (int row = 0; row < BLOOM_ROWS; row++)
    {
        for (int col = 0; col < bloomcols; col++)
        {
            printf("%d ", mbf->matrix[row][col]);
        }
        printf("\n");
    }
    
}
// float howMuchFilled(bloomfilter * bf){
//     float filledcount=0;
//     for (int i = 0; i < BLOOM_LEN; i++)
//     {
//         if (bf->bitarray[i]==1)
//         {
//             filledcount++;
//         }
        
//     }
//     return (filledcount/((float)BLOOM_LEN));
// }
float howMuchFilled(matrixbf * mbf){
    float filledcount=0;
    int bloomcols=BLOOM_LEN/BLOOM_ROWS;
    for (int row = 0; row < BLOOM_ROWS; row++)
    {
        for (int col = 0; col< bloomcols; col++)
        {
            if(mbf->matrix[row][col]){
                filledcount++;
            }
        }
    }
    return (filledcount/((float)BLOOM_LEN));
}

void feed( int** matrix, int bit1, int bit2, int bit3, int bit4, int bit5, int bit6){
    matrix[bit1][bit2]=1;
    matrix[bit3][bit4]=1;
    matrix[bit5][bit6]=1;
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
// void tostring(char str[], int num)
// {
//     int i, rem, len = 0, n;
//     n = num;
//     while (n != 0)
//     {

//         len++;
//         n /= 10;
//     }
//     for (i = 0; i < len; i++) 
//     {
//         rem = num % 10;
//         num = num / 10;
//         str[len - (i + 1)] = rem + '0';
//     }
// }

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
    return (abs(67 + (encryptedstr>>1)*34))%BLOOM_ROWS;
}
int hash2(ll encryptedstr){
    int dig1=encryptedstr%10;
    int dig2=(encryptedstr%100)/10;
    int dig3=(encryptedstr%1000)/100;

    return ((dig1<<dig2)|dig3*112)%BLOOM_COLS;
}

int hash3(ll encryptedstr){
    return ((encryptedstr*2)>>1)%BLOOM_ROWS;
}
int hash4(ll encryptedstr){
    // int dig1=encryptedstr%10;
    // int dig2=(encryptedstr%100)/10;
    // int dig3=(encryptedstr%1000)/100;

    return (abs(69 + (encryptedstr>>1)*14))%BLOOM_COLS;
}
int hash5(ll encryptedstr){
    int dig1=encryptedstr%10;
    int dig2=(encryptedstr%100)/10;
    int dig3=(encryptedstr%1000)/100;

    return ((dig1<<dig2)|dig3*12)%BLOOM_ROWS;
}

int hash6(ll encryptedstr){
    return ((encryptedstr*5)>>1)%(BLOOM_COLS);
}
// int isSpam(char * str, bloomfilter * bf){
//     ll encryptedstr=encrypt(str);
//     int bit1=hash1(encryptedstr);
//     int bit2=hash2(encryptedstr);
//     int bit3=hash3(encryptedstr);
//     return (bf->bitarray[bit1] && bf->bitarray[bit2] && bf->bitarray[bit3]);
// }
int isSpam(char * str, matrixbf * mbf){
    ll encryptedstr=encrypt(str);
    int bit1=hash1(encryptedstr);
    int bit2=hash2(encryptedstr);
    int bit3=hash3(encryptedstr);
    int bit4=hash4(encryptedstr);
    int bit5=hash5(encryptedstr);
    int bit6=hash6(encryptedstr);
    return (mbf->matrix[bit1][bit2] && mbf->matrix[bit3][bit4] && mbf->matrix[bit5][bit6]);
}