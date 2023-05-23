#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 10000
#define MAX_WORD_LENGTH 100
#define MAX_ARRAY_SIZE 315
typedef struct hashNode
{
    char * str;
    long long int freq;
    struct hashNode * next;
}hashNode;

// new Node
hashNode * newNode(hashNode * node, char * str){
    node=(hashNode*)malloc(sizeof(hashNode));
    // node->str=str;
    node->str=(char*)malloc(sizeof(char)*(strlen(str)+1));
    strcpy(node->str,str);
    node->freq=1;
    node->next=NULL;
    return node;
}
// hashmap=linked list of hashnodes
// insert at tail
hashNode * insertAtTail(hashNode * head, char * key){
    if(!head){
        hashNode * nn=newNode(nn,key);
        return nn;
    }
    hashNode * temp=head;
    while (temp->next)
    {
        temp=temp->next;
    }
    hashNode * nn=newNode(nn,key);
    temp->next=nn;
    return head;
}
// search
hashNode* search(hashNode * head, char * key){
    if(head==NULL){
        return NULL;
    }
    hashNode * temp=head;
    while (temp && strcmp(temp->str,key))
    {
        temp=temp->next;
    }
    return temp;
}
int main()
{
    FILE *input_file = fopen("output1.txt", "r");
    if (input_file == NULL)
    {
        perror("File not found!\n");
        exit(1);
    }

    int num_words_to_remove = 313;
    // FILE *output_file = fopen("keyword.csv", "w");
    char *words_to_remove[313] = {"really", "sometimes", "go", "since", "whither", "they", "its", "them", "well", "meanwhile", "seems", "and", "latterly", "regarding", "somehow", "sixty", "whole", "anyway", "else", "few", "m", "beside", "to", "namely", "someone", "see", "moreover", "wherein", "for", "former", "bottom", "it", "next", "six", "along", "once", "might", "whenever", "below", "another", "yourself", "each", "just", "ourselves", "everyone", "any", "across", "get", "that", "eight", "we", "which", "therefore", "may", "keep", "among", "give", "such", "are", "indeed", "everywhere", "same", "herself", "yourselves", "alone", "were", "was", "take", "seem", "say", "why", "show", "between", "during", "elsewhere", "or", "though", "forty", "made", "used", "others", "whereafter", "formerly", "several", "via", "does", "please", "three", "also", "fifty", "afterwards", "s", "noone", "do", "perhaps", "further", "i", "beforehand", "myself", "empty", "yet", "thereby", "been", "both", "never", "put", "without", "him", "a", "nothing", "thereafter", "make", "then", "whom", "must", "sometime", "against", "through", "being", "four", "back", "become", "our", "himself", "because", "anything", "nor", "therein", "due", "until", "own", "most", "now", "while", "of", "only", "am", "itself", "too", "m", "nobody", "if", "one", "whereas", "twelve", "together", "can", "who", "even", "be", "she", "besides", "herein", "off", "last", "no", "whereupon", "the", "thru", "out", "hereupon", "by", "us", "already", "became", "here", "hers", "onto", "beyond", "down", "enough", "did", "some", "over", "serious", "quite", "move", "around", "nowhere", "amongst", "but", "so", "wherever", "twenty", "often", "part", "again", "where", "within", "at", "yours", "front", "unless", "could", "anyone", "third", "whatever", "doing", "nevertheless", "before", "rather", "fifteen", "her", "me", "thereupon", "mostly", "throughout", "hence", "mine", "ten", "hundred", "nine", "call", "when", "about", "will", "whereby", "this", "upon", "you", "should", "always", "themselves", "not", "has", "behind", "on", "anywhere", "side", "their", "hereby", "latter", "after", "none", "these", "name", "every", "although", "however", "he", "becoming", "how", "whose", "still", "hereafter", "whether", "towards", "more", "everything", "whoever", "seemed", "cannot", "up", "otherwise", "in", "would", "under", "done", "thence", "whence", "seeming", "either", "other", "with", "into", "amount", "five", "much", "except", "his", "thus", "what", "almost", "becomes", "least", "ever", "above", "is", "first", "there", "somewhere", "top", "than", "n", "have", "toward", "per", "all", "ours", "full", "anyhow", "as", "many", "various", "your", "had", "eleven", "from", "something", "less", "those", "using", "an", "two", "my", "very", "neither", "re", "s", "ll", "n", "t", "\""};
    char line[MAX_LINE_LENGTH];
    char *words_printed[100000];
    int k=0;
    int count = 0;
    hashNode * head=NULL;
    while (fgets(line, sizeof(line), input_file))
    {

        char *token2 = strtok(line, " ");
        while (token2 != NULL)
        {
            // printf("%s\n",token2);
            int flag = 0;
            for (int i = 0; i < num_words_to_remove; i++)
            {
                if (strcmp(token2, words_to_remove[i]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (!flag && strlen(token2)>=2)
            {
                hashNode * result=search(head,token2);
                if (!result)
                {
                    head=insertAtTail(head,token2);
                }
                else{
                    result->freq++;
                }
            }
            token2 = strtok(NULL, " ");
        }
    }
    hashNode * temp=head;
    // while (temp)
    // {
    //     printf("%s,%lld\n",temp->str,temp->freq);
    //     temp=temp->next;
    // }
    while (temp)
    {
        printf("%s\n",temp->str);
        temp=temp->next;
    }
    
    return 0;
}
