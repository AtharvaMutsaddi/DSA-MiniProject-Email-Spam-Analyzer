#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    FILE *input_file, *output_file;
    // printf("%s:%s",argv[1],argv[2]);

    input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("cannot Open the reading file");
        return 1;
    }
    output_file = fopen(argv[2], "w");
    if (output_file == NULL)
    {
        printf("cannot open writing file");
        fclose(input_file);
        return 1;
    }
    char ch;
    while ((ch = fgetc(input_file)) != EOF)
    {
        if (isalpha(ch) || ch==' ')
        {
            ch = tolower(ch);
            fputc(ch, output_file);
        }
    }
    fclose(input_file);
    fclose(output_file);

    printf("Advanced Preprocessing of file done!!!");

    return 0;
}

// int main() {
//     FILE *input_file, *output_file;
// char input_filename[] = "output1.txt";
// char output_filename[] = "newFile.txt";

// input_file = fopen(input_filename, "r");
// if (input_file == NULL) {
//     printf("cannot Open the reading file");
//     return 1;
// }
// output_file = fopen(output_filename, "w");
// if (output_file == NULL) {
//     printf("cannot open writing file");
//     fclose(input_file);
//     return 1;
// }
// char ch;
// while ((ch = fgetc(input_file)) != EOF) {
//     if (!isdigit(ch)) {
//         ch = tolower(ch);
//         fputc(ch, output_file);
//     }
// }
// fclose(input_file);
// fclose(output_file);

// printf("haa bhai hogaya kaam");

//     return 0;
// }
