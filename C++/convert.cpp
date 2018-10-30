//转换进制的函数

//把长度为8的字符串转换成64位二进制
//每一个字符对应8位二进制
//转成的64位下标从1开始
void to64(const char *src, char *dst) {
  for (int i = 0; i < 8; i++) {
    char tmp = src[i];
    unsigned char mask = 0x80;//保证右移不会补1
    for (int j = 1; j <= 8; j++) {
      dst[j + i * 8] = (mask & tmp) ? 1 : 0;
      mask >>= 1;
    }
  }
}

//把64位二进制转换成8位长的字符串
//转成的8位下标成0开始(方便输出)
void to8(const char* src, char* dst) {
    for (int i = 0; i < 8; i++) {
        unsigned char mask = 0;
        for (int j = 1; j <= 8; j++) {
            char tmp = src[j + i * 8];
            mask <<= 1;
            mask |= int(tmp);
        }
        dst[i] = mask;
    }
}