#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int isLetter(char ch)
{
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

char shiftLetter(char ch, int shift) {
    int asciiVal = (int)ch;
    int caseOffset = (isupper(ch) ? 'A' : 'a');


    int shiftedChar = (asciiVal - caseOffset + shift) % 26 + caseOffset;


    return (char)shiftedChar;

}

void encrypt_text(const char *inputFileName, const char *outputFileName, int shift)
{
    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    
    // error handling for empty files
    if (inputFile == NULL)
    {
        FILE *errorFile = fopen("error.txt", "w");
        fprintf(stderr, "Invalid input data. File is Empty.\n");

        fclose(errorFile);
        fclose(inputFile);
        fclose(outputFile);
        
        exit(EXIT_FAILURE);
    
    }

    // will hold all fgetc characters as an unsigned char or EOF character
    int ch;

    // reads the next character in the inputFile
    // while ch (get character from inputFile) 
    // is not the End Of File (EOF) character . . .
    while ((ch = fgetc(inputFile)) != EOF) {

        // if ch is a letter
        if (isLetter(ch)) {

            // shift ch and put it into outputfile
            fputc(shiftLetter(ch, shift), outputFile);
        }
        else 
        {
            //otherwise, put ch directly into outputFile
            fputc(ch, outputFile);
        }
    }

    //close files
    fclose(inputFile);
    fclose(outputFile);


}

int main()
{
    const char *inputFile = "input.txt";
    const char *outputFile = "output.txt";

    int shiftNum = 3;

    encrypt_text(inputFile, outputFile, shiftNum);

    return 0;
}
