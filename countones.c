#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int FP1 = 0;
    struct stat St1;
    unsigned char *File1 = NULL;

    if (argc != 2)
    {
        printf("COUNTONES: Count the number of binary ones in a file.\n");
        printf("\n");
        printf("For security purposes, a newly mapped file gets initialized with all zeroes.\n");
        printf("If you have two files that are supposed to be identical, where one might\n");
        printf("have been aborted in transit, the file with more ones has a higher liklihood\n");
        printf("of being correct.\n");
        printf("\n");
        printf("Syntax: %s file\n", argv[0]);
        exit(1);
    }

    FP1 = open(argv[1], O_RDONLY);
    if (FP1 == -1)
    {
        perror("Error opening file");
        exit(2);
    }

    if (fstat(FP1, &St1) == -1)
    {
        perror("Can't determine file size");
        exit(3);
    }

    File1 = (unsigned char*) mmap(NULL, St1.st_size, PROT_READ, MAP_SHARED, FP1, 0);
    if (File1 == MAP_FAILED)
    {
        perror("Can't map file1");
        exit(4);
    }

    ssize_t i;
    ssize_t ones = 0;
    unsigned char payload;

    for (i = 0; i < St1.st_size; ++i)
    {
        payload = File1[i];
        while (payload != 0)
        {
            if (payload & 1)
            {
                ++ones;
            }
            payload >>= 1;
        }
    }
    printf("%zu\n", ones);

    munmap(File1, St1.st_size);
    close(FP1);
    return 0;
}
