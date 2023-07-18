#include "types.h"
#include "user.h"
#include "date.h"

int main(int argc, char *argv[])
{
    struct rtcdate r;
    if (mydate(&r))
    {
        printf(2, "date failed\n");
        exit();
    }
    // get_IST(&r);
    printf(1, "GMT time:\n");
    printf(1, "\tYear: %d\n", r.year);
    printf(1, "\tMonth: %d\n", r.month);
    printf(1, "\tDate: %d\n", r.day);
    printf(1, "\tHour: %d\n", r.hour);
    printf(1, "\tMinute: %d\n", r.minute);
    printf(1, "\tSecond: %d\n", r.second);
    exit();
}