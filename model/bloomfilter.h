#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BLOOM_LEN 1200 // you can modulate this. Maximum size is 1800
#define BLOOM_ROWS 300
#define BLOOM_COLS 4
#define ll long long
#define Ch_s(x, y, z) ((x & y) ^ (~x & z))
#define Maj_s(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define MAX_WORD_LEN 50
#define MAX_DOMAIN_SIZE 100

typedef struct matrixbloomfilter
{
    int **matrix;
} matrixbf;
void feed(int **matrix, int bit1, int bit2, int bit3, int bit4, int bit5, int bit6)
{
    matrix[bit1][bit2] = 1;
    matrix[bit3][bit4] = 1;
    matrix[bit5][bit6] = 1;
}
void printmbf(matrixbf *mbf)
{
    int bloomcols = BLOOM_LEN / BLOOM_ROWS;
    for (int row = 0; row < BLOOM_ROWS; row++)
    {
        for (int col = 0; col < bloomcols; col++)
        {
            printf("%d ", mbf->matrix[row][col]);
        }
        printf("\n");
    }
}
float howMuchFilled(matrixbf *mbf)
{
    float filledcount = 0;
    int bloomcols = BLOOM_LEN / BLOOM_ROWS;
    for (int row = 0; row < BLOOM_ROWS; row++)
    {
        for (int col = 0; col < bloomcols; col++)
        {
            if (mbf->matrix[row][col])
            {
                filledcount++;
            }
        }
    }
    return (filledcount / ((float)BLOOM_LEN));
}
matrixbf *init(matrixbf *mbf)
{
    mbf = (matrixbf *)malloc(sizeof(matrixbf));
    mbf->matrix = (int **)malloc(sizeof(int *) * BLOOM_ROWS);
    int bloomcols = BLOOM_LEN / BLOOM_ROWS;
    for (int i = 0; i < BLOOM_ROWS; i += 1)
    {
        mbf->matrix[i] = (int *)calloc(bloomcols, sizeof(int));
    }
    return mbf;
}

long long int encrypt(char *str)
{
    int len = strlen(str);
    int i = 0;
    ll ans = 0;
    while (i < len - 2)
    {
        if (i % 2 == 0)
        {
            ans += Ch_s(str[i], str[i + 1], str[i + 2]);
        }
        else
        {
            ans += Maj_s(str[i], str[i + 1], str[i + 2]);
        }
        i += 3;
    }
    while (i < len)
    {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
        {
            ans += (((int)str[i] << 5 || 57) ^ 37);
        }
        else
        {
            ans += ((int)str[i] >> 2 || 57) ^ 36;
        }
        i++;
    }
    return ans;
}
int hash1(ll encryptedstr)
{
    // int dig1=encryptedstr%10;
    // int dig2=(encryptedstr%100)/10;
    // int dig3=(encryptedstr%1000)/100;
    return (abs(67 + (encryptedstr >> 1) * 34)) % BLOOM_ROWS;
}
int hash2(ll encryptedstr)
{
    int dig1 = encryptedstr % 10;
    int dig2 = (encryptedstr % 100) / 10;
    int dig3 = (encryptedstr % 1000) / 100;

    return ((dig1 << dig2) | dig3 * 112) % BLOOM_COLS;
}

int hash3(ll encryptedstr)
{
    return ((encryptedstr * 2) >> 1) % BLOOM_ROWS;
}
int hash4(ll encryptedstr)
{
    // int dig1=encryptedstr%10;
    // int dig2=(encryptedstr%100)/10;
    // int dig3=(encryptedstr%1000)/100;

    return (abs(69 + (encryptedstr >> 1) * 14)) % BLOOM_COLS;
}
int hash5(ll encryptedstr)
{
    int dig1 = encryptedstr % 10;
    int dig2 = (encryptedstr % 100) / 10;
    int dig3 = (encryptedstr % 1000) / 100;

    return ((dig1 << dig2) | dig3 * 12) % BLOOM_ROWS;
}

int hash6(ll encryptedstr)
{
    return ((encryptedstr * 5) >> 1) % (BLOOM_COLS);
}
// int isSpam(char * str, bloomfilter * bf){
//     ll encryptedstr=encrypt(str);
//     int bit1=hash1(encryptedstr);
//     int bit2=hash2(encryptedstr);
//     int bit3=hash3(encryptedstr);
//     return (bf->bitarray[bit1] && bf->bitarray[bit2] && bf->bitarray[bit3]);
// }
int isSpam(char *str, matrixbf *mbf)
{
    ll encryptedstr = encrypt(str);
    int bit1 = hash1(encryptedstr);
    int bit2 = hash2(encryptedstr);
    int bit3 = hash3(encryptedstr);
    int bit4 = hash4(encryptedstr);
    int bit5 = hash5(encryptedstr);
    int bit6 = hash6(encryptedstr);
    return (mbf->matrix[bit1][bit2] && mbf->matrix[bit3][bit4] && mbf->matrix[bit5][bit6]);
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
        if (!strcmp(username, "gmail.com") || strstr(username, "coep") !=NULL || strstr(username, "yahoo") != NULL)
        {
            ans = 0;
        }
        return ans;
    }
    else
    {
        ans = isSpam(domain, mbf);
        if (!strcmp(domain, "gmail.com") || strstr(domain, "coep") != NULL || strstr(domain, "yahoo") != NULL)
        {
            ans = 0;
        }
        return ans;
    }
}
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
// bloomfilter *init(bloomfilter *bf)
// {
//     bf = (bloomfilter *)malloc(sizeof(bloomfilter));
//     bf->bitarray = (int *)calloc(BLOOM_LEN, sizeof(int));
// }



// void printbloom(bloomfilter *bf)
// {
//     for (int i = 0; i < BLOOM_LEN; i++)
//     {
//         printf("%d ", bf->bitarray[i]);
//     }
//     printf("\n");
// }

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




/*+++++++++++++++++++++++++++FUNCTIONS YOU HAVE TO CODE+++++++++++++++++++++++++++++++++++++++++*/

/*
1) Your encryption Method:(feel free to use any data structures as long as they are not memory intensive)
2) be aware of time complexity
3) Model should be at least 80% accurate
*/

// example:

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

