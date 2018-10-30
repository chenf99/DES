//置换函数
#include "globalVar.hpp"
#include <cstring>

//注意所有给tmp赋值的操作都不能用strncpy
//所有置换后的数组下标从1开始

//初始置换IP
void IP(char* M) {
    char tmp[65];
    memcpy(tmp, M, 65);
    for (int i = 1; i < 65; ++i) {
        M[i] = tmp[IP_table[i]];
    }
}

//IP逆置换
void IP_inverse(char* M) {
    char tmp[65];
    memcpy(tmp, M, 65);
    for (int i = 1; i < 65; ++i) {
        M[i] = tmp[IP_inverse_table[i]];
    }
}

//E扩展
void E_extend(char* R, char* E) {
    char tmp[33];
    memcpy(tmp, R, 33);
    for (int i = 1; i < 49; ++i) {
        E[i] = tmp[E_table[i]];
    }
}

//P置换
void P_transform(char* in, char* f) {
    char tmp[33];
    memcpy(tmp, in, 33);
    for (int i = 1; i < 33; ++i) {
        f[i] = tmp[P_table[i]];
    }
}

//PC_1置换
void PC_1(char* key64, char* key56) {
    char tmp[65];
    memcpy(tmp, key64, 65);
    for (int i = 1; i < 57; ++i) {
        key56[i] = tmp[PC_1_table[i]];
    }
}

//PC_2置换
void PC_2(char* key56, char* subkey) {
    char tmp[57];
    memcpy(tmp, key56, 57);
    for (int i = 1; i < 49; ++i) {
        subkey[i] = tmp[PC_2_table[i]];
    }
}