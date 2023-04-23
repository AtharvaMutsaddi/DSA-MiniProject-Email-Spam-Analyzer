#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 10000
#define MAX_WORD_LENGTH 100
#define MAX_ARRAY_SIZE 315

int main() {
    FILE *input_file = fopen("test.csv", "r");
    if (input_file==NULL )
    {
        perror("File not found!\n");
        exit(1);
    }
    
    // FILE *output_file = fopen("keyword.csv", "w");

    char *words_to_remove[312] = {"really", "sometimes", "go", "since", "whither", "they", "its", "them", "well", "meanwhile", "seems", "and", "latterly", "regarding", "somehow", "sixty", "whole", "anyway", "else", "few", "m", "beside", "to", "namely", "someone", "see", "moreover", "wherein", "for", "former", "bottom", "it", "next", "six", "along", "once", "might", "whenever", "below", "another", "yourself", "each", "just", "ourselves", "everyone", "any", "across", "get", "that", "eight", "we", "which", "therefore", "may", "keep", "among", "give", "such", "are", "indeed", "everywhere", "same", "herself", "yourselves", "alone", "were", "was", "take", "seem", "say", "why", "show", "between", "during", "elsewhere", "or", "though", "forty", "made", "used", "others", "whereafter", "formerly", "several", "via", "does", "please", "three", "also", "fifty", "afterwards", "s", "noone", "do", "perhaps", "further", "i", "beforehand", "myself", "empty","yet", "thereby", "been", "both", "never", "put", "without", "him", "a", "nothing", "thereafter", "make", "then", "whom", "must", "sometime", "against", "through", "being", "four", "back", "become", "our", "himself", "because", "anything","nor", "therein", "due", "until", "own","most", "now", "while", "of", "only", "am", "itself", "too", "m", "nobody", "if", "one", "whereas", "twelve", "together", "can", "who", "even", "be", "she", "besides", "herein", "off","last", "no", "whereupon", "the", "thru", "out", "hereupon", "by", "us", "already", "became", "here", "hers", "onto", "beyond", "down", "enough", "did", "some", "over", "serious", "quite", "move", "around", "nowhere", "amongst", "but", "so", "wherever", "twenty", "often", "part", "again", "where","within", "at", "yours", "front", "unless", "could", "anyone", "third", "whatever", "doing", "nevertheless", "before", "rather", "fifteen", "her", "me", "thereupon", "mostly", "throughout", "hence","mine", "ten", "hundred", "nine", "call", "when", "about", "will", "whereby", "this", "upon", "you", "should", "always", "themselves", "not", "has", "behind", "on", "anywhere", "side", "their", "hereby", "latter", "after","none", "these", "name","every", "although","however", "he", "becoming", "how", "whose", "still", "hereafter", "whether", "towards", "more", "everything", "whoever", "seemed", "cannot", "up", "otherwise", "in", "would", "under", "done", "thence", "whence", "seeming", "either", "other", "with", "into", "amount", "five", "much","except", "his", "thus","what", "almost", "becomes", "least", "ever", "above", "is", "first", "there", "somewhere", "top","than", "n", "have", "toward", "per", "all", "ours", "full","anyhow", "as","many", "various", "your", "had", "eleven", "from", "something", "less", "those", "using", "an", "two", "my", "very","neither","re","s","ll","n","t"};
    int num_words_to_remove = 312;
    char line[MAX_LINE_LENGTH];
    int count=0;
    while (fgets(line,sizeof(line),input_file))
    {
        char * token;
        token=strtok(line,",");
        while (token!=NULL)
        {
            // printf("%s\n",token);
            char * token2=strtok(token," ");
            while (token2!=NULL)
            {
                // printf("%s\n",token2);
                int flag=0;
                for (int i = 0; i < 312; i++)
                {
                    if(strcmp(token2,words_to_remove[i])==0){
                        flag=1;
                        break;
                    }
                }
                if(!flag){
                    printf("%s\n",token2);
                }
                token2=strtok(NULL," ");
            }
            
            token=strtok(NULL,",");
        }
        printf("\n---------------\n");
    }

    return 0;
}









// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_LINE_LENGTH 10000000

// int main() {
//     FILE* input_file = fopen("output.csv", "r");
//     FILE* output_file = fopen("keyword.csv", "w");
//     char* words_to_remove[] = {"a","to","of","we","are","an","the","in","on","at","be","have","do","say","get","make","go","take","see","come","know","give","find","think","tell","become","feel","leave","put","mean","keep","let","begin","seem","help","talk","turn","start","show","hear","play","run","move","like","live","believe","hold","bring","happen","write","provide","sit","stand","lose","pay","meet","include","continue","set","learn","change","lead","understand","watch","follow","stop","create","speak","read","allow","add","spend","grow","open","walk","win","offer","remember","love","consider","appear","buy","wait","serve","die","send","expect","build","stay","fall","cut","reach","kill","remain","suggest","raise","pass","sell","require","report","decide","pull","call","receive","agree","support","explain","check","develop","belong","cover","increase","move","return","divide","apply","marry","prepare","beat","pick","express","strike","wind","operate","touch","press","shoot","clean","contain","travel","raise","describe","deliver","exchange","fly","recover","push","wear","spread","overcome","advise","gather","enter","rain","care","carry","dream","imagine","smile","introduce","preserve","drink","climb","sing","refer","finish","visit","form","prove","drive","rely","sleep","smell","survive"};
//     int length_arr = 164;
//     if (input_file == NULL && output_file == NULL) {
//         printf("Failed to open input or output file\n");
//         return 1;
//     }

//     char line[MAX_LINE_LENGTH];
//     char* token;

//     // Loop through each line in the input file
//     while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
//         // Loop through each word in the line
//         token = strtok(line, ", ");
//         while (token != NULL) {
//             int count = 0;
//             for (int i = 0; i < length_arr; i++)
//             {
//                  if (strcmp(token, words_to_remove[i])==0){
//                     count = 1;
//                  }
//             }
            
//             
//             if (count==0) {
//                 // Write the updated word to the output file
//                 fprintf(output_file, "%s", token);
//             }
//             token = strtok(NULL, ", ");
//         }
//         // Add a newline character to the end of the line
//         fprintf(output_file, "\n");
//     }

//     // Close the input and output files
//     fclose(input_file);
//     fclose(output_file);

//     return 0;
// }
// #define MAX_LINE_LENGTH 1024

// int main() {
//     FILE* input_file = fopen("output.csv", "r");
//     FILE* output_file = fopen("keyword.csv", "w");
//     char* words_to_remove[] = {"a","to","of","we","are","an","the","in","on","at","be","have","do","say","get","make","go","take","see","come","know","give","find","think","tell","become","feel","leave","put","mean","keep","let","begin","seem","help","talk","turn","start","show","hear","play","run","move","like","live","believe","hold","bring","happen","write","provide","sit","stand","lose","pay","meet","include","continue","set","learn","change","lead","understand","watch","follow","stop","create","speak","read","allow","add","spend","grow","open","walk","win","offer","remember","love","consider","appear","buy","wait","serve","die","send","expect","build","stay","fall","cut","reach","kill","remain","suggest","raise","pass","sell","require","report","decide","pull","call","receive","agree","support","explain","check","develop","belong","cover","increase","move","return","divide","apply","marry","prepare","beat","pick","express","strike","wind","operate","touch","press","shoot","clean","contain","travel","raise","describe","deliver","exchange","fly","recover","push","wear","spread","overcome","advise","gather","enter","rain","care","carry","dream","imagine","smile","introduce","preserve","drink","climb","sing","refer","finish","visit","form","prove","drive","rely","sleep","smell","survive"};
//     int length_arr = 164;
//     if (input_file == NULL && output_file == NULL) {
//         printf("Failed to open input or output file\n");
//         return 1;
//     }

//     char line[MAX_LINE_LENGTH];
//     char* token;
//     char* token1;
//     while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
//         token = strtok(line, ",");
//         while (token != NULL) {
//             token1 = strtok(token," ");
//             while (token1 != NULL) {
//                 int count = 0;
//                 for (int i = 0; i < length_arr; i++)
//                 {
//                     if(strcmp(token1, words_to_remove[i]) == 0){
//                         count = 1;
//                         break;
//                     }

//                 }
//                 printf(token1);
//                 printf("\n");
//                 if (count == 0) {
//                     fprintf(output_file, "%s", token1);
//                 }
//                 token1 = strtok(NULL, ",");
//         }
//             token = strtok(NULL, ",");
//         }
//         // fprintf(output_file, "\n");
//     }
//     fclose(input_file);
//     fclose(output_file);

//     return 0;
// }
// int main() {
//     FILE* input_file = fopen("output.csv", "r");
//     FILE* output_file = fopen("keyword.csv", "w");
//     char* words_to_remove[] = {"a","to","of","we","are","an","the","in","on","at","be","have","do","say","get","make","go","take","see","come","know","give","find","think","tell","become","feel","leave","put","mean","keep","let","begin","seem","help","talk","turn","start","show","hear","play","run","move","like","live","believe","hold","bring","happen","write","provide","sit","stand","lose","pay","meet","include","continue","set","learn","change","lead","understand","watch","follow","stop","create","speak","read","allow","add","spend","grow","open","walk","win","offer","remember","love","consider","appear","buy","wait","serve","die","send","expect","build","stay","fall","cut","reach","kill","remain","suggest","raise","pass","sell","require","report","decide","pull","call","receive","agree","support","explain","check","develop","belong","cover","increase","move","return","divide","apply","marry","prepare","beat","pick","express","strike","wind","operate","touch","press","shoot","clean","contain","travel","raise","describe","deliver","exchange","fly","recover","push","wear","spread","overcome","advise","gather","enter","rain","care","carry","dream","imagine","smile","introduce","preserve","drink","climb","sing","refer","finish","visit","form","prove","drive","rely","sleep","smell","survive"};
//     int length_arr = 164;
//     if (input_file == NULL && output_file == NULL) {
//         printf("Failed to open input or output file\n");
//         return 1;
//     }

//     char line[MAX_LINE_LENGTH];
//     char* token;

//     
//     while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
//         token = strtok(line, ",");
//         while (token != NULL) {
//             int count = 0;
//             for (int i = 0; i < length_arr; i++)
//             {
//                  if (strcmp(token, words_to_remove[i])==0){
//                     count = 1;
//                  }
//             }
            
//           
//             if (count==0) {
//                 // Write the updated word to the output file
//                 fprintf(output_file, "%s", token);
//             }
//             token = strtok(NULL, ",");
//         }
//         fprintf(output_file, "\n");
//     }
//     fclose(input_file);
//     fclose(output_file);

//     return 0;
// }
