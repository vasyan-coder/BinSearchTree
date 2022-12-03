#pragma once
#include <stdio.h>
#pragma warning(disable : 4996)

class Railway {
public:
    int num_train;
    char start_place[20];
    char end_place[20];
    char time[20];

    //bool operator < (const Node& str) const {
    //    return (num_lic < str.num_lic);
    //}
};