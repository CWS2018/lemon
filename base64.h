#ifndef _BASE64_H_
#define _BASE64_H_

#include <iostream>
#include <string>

/*
 * 标准的base64映射表
 */
const char mapping_table[] = {'A','B','C','D','E','F','G','H','I','J',
                              'K','L','M','N','O','P','Q','R','S','T',
                              'U','V','W','X','Y','Z','a','b','c','d',
                              'e','f','g','h','i','j','k','l','m','n',
                              'o','p','q','r','s','t','u','v','w','x',
                              'y','z','0','1','2','3','4','5','6','7',
                              '8','9','+','/'};

/*
 * 用于URL 的url_base64映射表
 
const char mapping_table_url[] = {'A','B','C','D','E','F','G','H','I','J',
                              'K','L','M','N','O','P','Q','R','S','T',
                              'U','V','W','X','Y','Z','a','b','c','d',
                              'e','f','g','h','i','j','k','l','m','n',
                              'o','p','q','r','s','t','u','v','w','x',
                              'y','z','0','1','2','3','4','5','6','7',
                              '8','9','-','_'};
*/

class Base64
{
public:
    Base64() = default;
    ~Base64() = default;

    std::string encode(const std::string &in);
    std::string encode(const char *in) {
        std::string s = in;
        return encode(s);
    }

    std::string decode(const std::string &in);
    std::string decode(const char *in) {
        std::string s = in;
        return decode(s);
    }
private:
    unsigned char buf3[3];
    unsigned char buf4[4];

    // 将3字节的转换成4个字节
    void buf3_to_buf4(const unsigned char *b3, unsigned char *b4);
    // 将4个字节转换成3个字节的
    void buf4_to_buf3(const unsigned char *b4, unsigned char *b3);

    unsigned char tranform(const char &c);
};

#endif