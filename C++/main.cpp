#include <iostream>
#include "des.cpp"
using namespace std;

//测试函数
int main() {
    string input = "TAKERS Championship";
    string key = "kobe mvp";
    string encryptText = "";
    string decryptText = "";
    
    if (input == "") {
        cout << "null input error!" << endl;
        exit(1);
    }
    if (key.length() != 8) {
        cout << "key length must be 8!" << endl;
        exit(2);
    }

    cout << "加密前:" + input << endl;
    encrypt(input, encryptText, key);
    cout << "加密后:" + encryptText << endl;
    decrypt(encryptText, decryptText, key);
    cout << "解密后:" + decryptText << endl;
    return 0;
}