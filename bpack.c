/* * * *
    Tyler Pease
    Fall 2022 FSU
* * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encore(unsigned char *, const unsigned char *, const int, const int, const int);
void applyMask(unsigned long long *, const int, const int);

int main(int argc, char *argv[]) {
    FILE *inputFile, *outputFile;
    char *inputFileName, *outputFileName, *mode;
    unsigned char *buffer, *o_buffer;
    int fileSize, newSize;

    // need to make sure that input and output file names are provided
    if (argc != 4) {
        printf("Missing arguments, <mode> <input file> <output file>\n");
        exit(1);
    }

    mode = argv[1];
    inputFileName = argv[2];
    outputFileName = argv[3];

    if(strcmp(mode, "-c") && strcmp(mode, "-d")) {
        printf("Error: Invalid mode, must be -c or -d\n");
        exit(1);
    }

    // check to see if input file is valid
    inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL) {
        printf("Error: Cannot open input file %s\n", inputFileName);
        exit(1);
    }

    // open output with write priviliges, if it doesn't exist, create it
    outputFile = fopen(outputFileName, "wb");
    if (outputFile == NULL) {
        printf("Error: Cannot open output file %s\n", outputFileName);
        exit(1);
    }

    // need to get the size of the input file
    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    rewind(inputFile);

    buffer = (unsigned char *)malloc(sizeof(unsigned char) * fileSize);
    if (buffer == NULL) {
        printf("Error: Cannot allocate memory for input buffer\n");
        exit(1);
    }

    // going to need another buffer to store the decompressed file
    newSize = (strcmp(mode, "-c") == 0) ? (fileSize * 7)/8 : (fileSize * 8)/7;
    o_buffer = (unsigned char *)malloc(sizeof(unsigned char) * newSize);
    if (o_buffer == NULL) { // verify that the memory was allocated
        printf("Error: Cannot allocate memory for output buffer\n");
        exit(1);
    }

    fread(buffer, 1, fileSize, inputFile);

    (strcmp(mode, "-c") == 0) ? encore(o_buffer, buffer, fileSize, 8, 7) : 
                                encore(o_buffer, buffer, fileSize, 7, 8);

    // write the decompressed file to the output file
    fwrite(o_buffer, 1, newSize, outputFile);

    // close the files and free the memory
    fclose(inputFile); fclose(outputFile);
    free(buffer); free(o_buffer);

    return 0;
}

void applyMask(unsigned long long * buffer, const int c, const int o) { // goes through the entire buffer and applies the mask
    *buffer = (*buffer & 0x7F) | ((*buffer >> c) & 0x7F) << o |
    ((*buffer >> (c*2)) & 0x7F) << (o*2) | ((*buffer >> (c*3)) & 0x7F) << (o*3) |
    ((*buffer >> (c*4)) & 0x7F) << (o*4) | ((*buffer >> (c*5)) & 0x7F) << (o*5) |
    ((*buffer >> (c*6)) & 0x7F) << (o*6) | ((*buffer >> (c*7)) & 0x7F) << (o*7);
}

void encore(unsigned char *output, const unsigned char *input, const int size, const int c, const int o) {
    // c is the number of bits per byte for the input buffer, o is the same for the output
    // 8 bits for compression or 7 bits for decompression are the expected values of c, o will be the opposite to c
    for(int i = size, memsize = (i > c) ? c : i; i > 0; i -= memsize, memsize = (i > c) ? c : i) {
        unsigned long long buffer = 0;
        memcpy(&buffer, input, memsize * sizeof(unsigned char));
        input += memsize;
        applyMask(&buffer, c, o);
        memcpy(output, &buffer, o * sizeof(unsigned char));
        output += o;
    }
}
