//feistel轮函数，输入R为32位，K为48位，输出f32位
void feistel(char* R, char* k, char* f) {
    //首先进行E扩展
    char E[49];
    E_extend(R, E);

    //与48位密钥进行异或运算
    for (int i = 1; i <= 48; ++i) E[i] ^= k[i];

    //8组6位的S盒输入和8组4位的S盒输出
    char s_in[8][6], s_out[8][4];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 6; ++j) {
            s_in[i][j] = E[i * 6 + j + 1];
        }
    }

    //得到s盒输出
    for (int i = 0; i < 8; ++i) {
        char n = s_in[i][0] * 2 + s_in[i][5];
        char m = s_in[i][1] * 8 + s_in[i][2] * 4 + s_in[i][3] * 2 + s_in[i][4];
        char result = S_box[i][2][6];
        unsigned char mask = 0x8;
        for (int j = 0; j < 4; ++j) {
            s_out[i][j] = (result & mask) ? 1 : 0;
            mask >>= 1;
        }
    }

    //顺序连接S盒的输出
    char combine[33];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            combine[i * 4 + j + 1] = s_out[i][j];
        }
    }

    //最后进行P置换
    P_transform(combine, f);
}

//16轮T-迭代
void iteration(char* M, char subkey[16][49], bool isEncrypt) {
    char L[33], R[33];
    //初始化L0，R0
    for (int i = 1; i <= 32; ++i) {
        L[i] = M[i];
        R[i] = M[i + 32];
    }
    char tmp[33];
    char f[33];

    for (int i = 0; i < 16; ++i) {
        for (int j = 1; j <= 32; ++j) {
            tmp[j] = L[j];
            L[j] = R[j];
        }
        if (isEncrypt == true) {
            feistel(R, subkey[i], f);
        }
        else {
            feistel(R, subkey[15 - i], f);
        }
        for (int j = 1; j <= 32; ++j) {
            R[j] = tmp[j] ^ f[j];
        }
    }

    for (int i = 1; i <= 32; ++i) {
        M[i] = L[i];
        M[i + 32] = R[i];
    }
}