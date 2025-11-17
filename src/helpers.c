#include <math.h>


int limit_value(int value, int highest, int lowest)
{
    if (value > highest)
        return lowest;
    else if (value < lowest)
        return highest;
    return value;
}

int getMinutes(float timePlayed)
{
    return (int) floor(round(timePlayed) / 60);
}

int getSeconds(float timePlayed)
{
    return ((int) round(timePlayed)) % 60;
}
