#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/* This will only work if the entire array is currently in scope! */
/* If it's decayed to a pointer, you'll just get the size of the pointer. */
#define ArrayLength(arr) sizeof(arr) / sizeof(arr[0])
#define OUT_DIR "./generated/"

typedef struct {
    char *filename;
    int bitsize;
    bool is_signed;
} binary_numbers;

binary_numbers num_list[] = {
    { .filename = "unsigned_test.txt",  .bitsize = 4,   .is_signed = false  },
    { .filename = "signed_test.txt",    .bitsize = 4,   .is_signed = true   },
    // { .filename = OUT_DIR"unsigned_2bit.txt",     .bitsize = 2,   .is_signed = false  },
    // { .filename = OUT_DIR"unsigned_4bit.txt",     .bitsize = 4,   .is_signed = false  },
    // { .filename = OUT_DIR"unsigned_8bit.txt",     .bitsize = 8,   .is_signed = false  },
    // { .filename = OUT_DIR"unsigned_16bit.txt",    .bitsize = 16,  .is_signed = false  },
    // { .filename = OUT_DIR"signed_2bit.txt",       .bitsize = 2,   .is_signed = true   },
    // { .filename = OUT_DIR"signed_4bit.txt",       .bitsize = 4,   .is_signed = true   },
    // { .filename = OUT_DIR"signed_8bit.txt",       .bitsize = 8,   .is_signed = true   },
    // { .filename = OUT_DIR"signed_16bit.txt",      .bitsize = 16,  .is_signed = true   },
    /* Generating the full range of 32-bit numbers likely won't work due to Notepad's line limitations */
    /* ...it only goes up to 65536 lines. */
};

const int NUMS_TO_WRITE = ArrayLength(num_list);

char *MakeBinaryNumber(int dec_num, int most_sig_bit);

/* Represent signed integers using Two's Complement and write them to a file. */
int main(void)
{
    for (int i = 0; i < NUMS_TO_WRITE; i++)
    {
        /* Create/open the specified file, overwrite it */
        FILE *current_file = fopen(num_list[i].filename, "w");

        int num_bits = num_list[i].bitsize;
        int lower, upper;
        if (num_list[i].is_signed)
        {
            /* Lowest value for unsigned integers is -2^(num_bits - 1) */
            lower = (int) pow(-2, num_bits - 1);
            /* Highest value for unsigned integers is (2^(num_bits - 1)) - 1 */
            upper = (int) pow(2, num_bits - 1) - 1;
        }
        else
        {
            /* The lowest value for Unsigned Integers is 0 */
            lower = 0;
            /* Effective range is 2^(num_bits) - 1 */
            upper = (int) pow(2, num_bits) - 1;
        }
        /* Inclusive of upper. */
        for (int dec = lower; dec <= upper; dec++)
        {
            char *bin_str = MakeBinaryNumber(dec, num_bits);            
            fprintf(current_file, "%s\t=\t%i\n", bin_str, dec);
            free(bin_str);
        }
        fclose(current_file);
    }
    return 0;
}

/* Given a specified number of bits (e.g. 4-bit, 8-bit, 16-bit) */
/* "Make" a binary number out of the given decimal number. */
char *MakeBinaryNumber(int dec_num, int sig_bits)
{
    /* Add 1 for the nul character. */
    int buff = (sig_bits + 1) * sizeof(char);
    char *binary_string = malloc(buff);
    /* The last 0-based index should be the number that sig_bits holds. */
    binary_string[sig_bits] = '\0';
    
    int cur_bit, idx;
    /* Run through the bits from the leftmost going rightmost */
    /* Subtract sig_bits by 1 to get the 0-based index. */
    for (sig_bits -= 1, idx = 0; sig_bits >= 0; sig_bits--, idx++) 
    {
        /* Bit shift pads (to the left for >>, to the right for >> ) with zeroes. */
        /* This effectively gets the current digit at the sig-bits(th) place. */
        cur_bit = dec_num >> sig_bits;
        /* Ternary operators/shorthand if-else is so cryptic*/
        // (cur_bit & 1) ? printf("1") : printf("0");
        if (cur_bit & 1)
            binary_string[idx] = '1';
        else
            binary_string[idx] = '0';
    }
    return binary_string;
}