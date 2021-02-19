#ifndef _BASE64_H_
#define _BASE64_H_

#include <iostream>
#include <string>

const char mapping_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                            "abcdefghijklmnopqrstuvwxyz"
                            "0123456789"
                            "+/";

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

    void buf3_to_buf4(const unsigned char *b3, unsigned char *b4);
    void buf4_to_buf3(const unsigned char *b4, unsigned char *b3);

    unsigned char tranform(unsigned char &c);
};

#endif