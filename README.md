# ASCII-Bit-Packer

This is a simple ASCII bit packer program, expanded upon from an extra credit assignment involving only its decompression. It works by taking account that ASCII is usually 7 bits while a byte is 8 bits, compressing every 8 bytes down to 7 and vice versa with decompression. 

```console
--example decompressed:
00110000 00110001 00110010 00110011 00110100 00110101  012345
00110110 00110111 00111000 00111001 00110000 00110001  678901
00110010 00110011 00110100 00110101 00110110 00110111  234567
00111000 00111001 00110000 00110001 00110010 00110011  890123
00110100 00110101 00110110 00110111 00111000 00111001  456789
00110000 00110001 00110010 00110011 00110100 00110101  012345
00110110 00110111 00111000 00111001 00110000 00110001  678901
00110010 00110011 00110100 00110101 00110110 00110111  234567
00111000 00111001 00110000 00110001 00110010 00110011  890123
00110100 00110101                                      45
--example compressed:
10110000 10011000 01101100 01000110 10101011 11011001  ..lF..
01101110 10111000 00011100 00101100 00100110 10011011  n..,&.
11010001 01101010 10110110 00011011 00101110 00000111  .j....
10001011 11001001 01100110 10110100 10011010 11101101  ..f...
10000110 11001011 11000001 01100010 10110010 00011001  ...b..
10101101 01100110 10111011 11100001 01110010 10110000  .f..r.
10011000 01101100 01000110 10101011 11011001 01101110  .lF..n
10111000 00011100 00101100 00100110 10011011 11010001  ..,&..
01101010                                               j
```

## Instructions

Simply run the `makefile` and it'll compile the program.

If you wish to try out the test cases included, you can use `make tests` to call them all or `make test1`, `make test2`, and `make test3` to call them individually.

Any created files from the makefile use can be cleared via `make clean`.

Running the program itself is as simple as `./bpack -c <input file> <output file>` for compression or `./bpack -d <input file> <output file>` for decompression.

```console
foo@bar:~$ make
gcc -std=c99 -Wall -pedantic -o bpack bpack.c
foo@bar:~$ ./bpack -c Test-Cases/ascii-compress-size56-test test1
foo@bar:~$ xxd -d test1 && xxd -d Test-Cases/ascii-compress-size56-test--COMPRESSED
00000000: b098 6c46 abd9 6eb8 1c2c 269b d16a b61b  ..lF..n..,&..j..
00000016: 2e07 8bc9 66b4 9aed 86cb c162 b219 ad66  ....f......b...f
00000032: bbe1 72b0 986c 46ab d96e b81c 2c26 9bd1  ..r..lF..n..,&..
00000048: 6a                                       j
00000000: b098 6c46 abd9 6eb8 1c2c 269b d16a b61b  ..lF..n..,&..j..
00000016: 2e07 8bc9 66b4 9aed 86cb c162 b219 ad66  ....f......b...f
00000032: bbe1 72b0 986c 46ab d96e b81c 2c26 9bd1  ..r..lF..n..,&..
00000048: 6a                                       j
foo@bar:~$ ./bpack -d Test-Cases/ascii-compress-size56-test--COMPRESSED test2
foo@bar:~$ xxd -d test2 && xxd -d Test-Cases/ascii-compress-size56-test
00000000: 3031 3233 3435 3637 3839 3031 3233 3435  0123456789012345
00000016: 3637 3839 3031 3233 3435 3637 3839 3031  6789012345678901
00000032: 3233 3435 3637 3839 3031 3233 3435 3637  2345678901234567
00000048: 3839 3031 3233 3435                      89012345
00000000: 3031 3233 3435 3637 3839 3031 3233 3435  0123456789012345
00000016: 3637 3839 3031 3233 3435 3637 3839 3031  6789012345678901
00000032: 3233 3435 3637 3839 3031 3233 3435 3637  2345678901234567
00000048: 3839 3031 3233 3435                      89012345
```

### Time Complexity

The time complexity of this program is O(n) where n is the size of the input file. This is because the program iterates through the input file once, copying it to the output file after the buffer is masked.

## Functions

### applyMask()

* Brief: applies a mask to the given buffer, compressing or decompressing based on the values of c and o
* Parameters: unsigned long long * buffer, const int c, const int o
* Return Type: void

### encore()

* Brief: the main function that iterates through a given input an memcpy it to an output after being masked.
* Parameters: unsigned char *output, const unsigned char *input, const int size, const int c, const int o
* Return Type: void
