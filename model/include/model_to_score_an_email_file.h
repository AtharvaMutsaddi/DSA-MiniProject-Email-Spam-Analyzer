#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
#define QUARTILE_1 0.000433
#define QUARTILE_3 0.001133
typedef struct TrieMap
{
    // array of children
    struct TrieMap *children[ALPHABET_SIZE];
    double weightage;

} TrieMap;
double searchTrieMap(TrieMap *TrieMapNode, const char *word);
TrieMap *initTrieMap(TrieMap *TrieMapNode);
void insertTrieMap(TrieMap *TrieMapNode, const char *word, double weightage);