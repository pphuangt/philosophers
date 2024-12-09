#include "utils.h"

void ft_timeradd(struct timeval *a, struct timeval *b, struct timeval *res)
{
    res->tv_sec = a->tv_sec + b->tv_sec;
    res->tv_usec = a->tv_usec + b->tv_usec;
    if (res->tv_usec >= 1000000)
    {
        res->tv_sec++;
        res->tv_usec -= 1000000;
    }
}
