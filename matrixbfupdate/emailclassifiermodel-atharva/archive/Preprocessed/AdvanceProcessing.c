#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *input_file, *output_file;
    char input_filename[] = "output1.txt";
    char output_filename[] = "newFile.txt";

    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("cannot Open the reading file, fuck off");
        return 1;
    }
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("cannot open writing file, suck my dick");
        fclose(input_file);
        return 1;
    }
    char ch;
    while ((ch = fgetc(input_file)) != EOF) {
        if (!isdigit(ch)) {
            ch = tolower(ch);
            fputc(ch, output_file);
        }
    }
    fclose(input_file);
    fclose(output_file);

    printf("haa bhai hogaya kaam, gaand maraiye!!");

    return 0;
}
