#include "types.h"
#include "stat.h"
#include "user.h"
#define N 100000

// Umcomment the below line to experiment for global array memory allocation.
// int global[N];
int main(int argc, char *argv[])
{
    // Umcomment the below lines to experiment for local array memory allocation.
    /*
        int local[N];
        local[0] = 0;
        printf(1, "%d\n", local[0]);
    */
    mypgtPrint();
    exit();
}