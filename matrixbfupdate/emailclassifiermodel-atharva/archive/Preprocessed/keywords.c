#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 10000
#define MAX_WORD_LENGTH 100
#define MAX_ARRAY_SIZE 315

int isIncluded(char * arr[], int k, char * str){
    for(int i=0; i<k; i++){
        if(strcmp(arr[i],str)==0){
            return 1;
        }
    }
    return 0;
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
            if (!flag && strlen(token2)>=2 && !isIncluded(words_printed,k,token2))
            {
                words_printed[k]=token2;
                k++;
                printf("%s\n", token2);
            }
            token2 = strtok(NULL, " ");
        }
    }

    return 0;
}
