#include <string>
#include "globalVar.hpp"
#include "convert.cpp"
#include "transform.cpp"
#include "iteration.cpp"

using std::string;

void leftShift(char* key56) {
    char c_left = key56[1], d_left = key56[29];
    for (int i = 1; i < 28; ++i) {
        key56[i] = key56[i + 1];
        key56[i + 28] = key56[i + 29];
    }
    key56[28] = c_left;
    key56[56] = d_left;
}

void createKey(string key, char (*subkey)[49]) {
    //首先把输入的key转成64位
    char key64[65];
    to64(key.c_str(), key64);

    char key56[57];
    PC_1(key64, key56);

    //生成16个子密钥
    for (int i = 1; i <= 16; ++i) {
        if (i != 1 && i != 2 && i != 9 && i != 16) leftShift(key56);
        leftShift(key56);
        PC_2(key56, subkey[i - 1]);
    }
}

void des(string input, string& output, bool isEncrypt, string key) {
    //把输入明文分成8字符一组来加密
    int times = input.length() / 8;
    if (input.length() % 8 != 0) times++;

    //生成16个48位的子密钥
    char subkey[16][49];
    createKey(key, subkey);

    string message[times];
    char M[times][65];
    for (int i = 0; i < times; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (input[j + i * 8] == '\0') break;
            message[i] += input[j + i * 8];
        }
        //保证每组8个字符
        while (message[i].length() < 8) message[i] += '\0';
        to64(message[i].c_str(), M[i]);
        
        //M[i]就是des算法的64位输入明文
        //以下为des算法的总体结构

        IP(M[i]);

        iteration(M[i], subkey, isEncrypt);

        //交换置换W
        char tmp[65];
        memcpy(tmp, M[i], 65);
        for (int j = 1; j <= 32; ++j) {
            M[i][j] = tmp[j + 32];
            M[i][j + 32] = tmp[j];
        }

        IP_inverse(M[i]);
        
        char after[9] = {'\0'};
        to8(M[i], after);
        output += after;
    }
}

//加密过程，输出加密后的密文
void encrypt(string input, string& encryptText, string key) {
    des(input, encryptText, true, key);
}

//解密过程，输出解密后的明文
void decrypt(string input, string& decryptText, string key) {
    des(input, decryptText, false, key);
}