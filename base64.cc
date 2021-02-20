#include "./base64.h"
#include <string.h>

void Base64::buf3_to_buf4(const unsigned char *b3, unsigned char *b4) {
    // 
    b4[0] = ((b3[0] & 0xFC) >> 2);
    b4[1] = ((b3[0] & 0x03) << 4) + ((b3[1] & 0xF0) >> 4);
    b4[2] = ((b3[1] & 0x0F) << 2) + ((b3[2] & 0xC0) >> 6);
    b4[3] = (b3[2] & 0x3F);
}

std::string Base64::encode(const std::string &in) {
    int len = in.length();
    if(len == 0)
        return nullptr;

    std::string result;
    int pos = 0;

    for(int i = 0; i < len; ++i) {
        this->buf3[pos++] = in[i];
        if(pos == 3) {
            this->buf3_to_buf4(this->buf3, this->buf4);
            for(int j = 0; j < 4; ++j) {
                result += mapping_table[this->buf4[j]];
            }
            pos = 0;
        }
    }

    if(pos != 0) {
        for(int i = pos; i < 3; ++i) {
            this->buf3[i] = '\0';
        }
        this->buf3_to_buf4(this->buf3, this->buf4);
        for(int j = 0; j <= pos; ++j) {
            result += mapping_table[this->buf4[j]];
        }

        // 
        while(pos++ < 3) {
            result += "=";
        }
    }

    return result;
}

void Base64::buf4_to_buf3(const unsigned char *b4, unsigned char *b3) {
    b3[0] = ((b4[0] << 2) + ((b4[1] & 0x30) >> 4));
    b3[1] = ((b4[1] & 0xF) << 4) + ((b4[2] & 0x3C)>> 2);
    b3[2] = ((b4[2] & 0x3) << 6) + b4[3];
}

std::string Base64::decode(const std::string &in) {
    int len = in.length();
    if(len < 2) {
        return nullptr;
    }

    std::string result;
    int pos = 0;

    for(int i = 0; i < len; ++i) {
        if(in[i] == '=') {
            break;
        }

        this->buf4[pos++] = this->tranform(in[i]);
        if(pos == 4) {
            this->buf4_to_buf3(this->buf4, this->buf3);
            for(int j = 0; j < 3; ++j) {
                result += this->buf3[j];
            }
            pos = 0;
        }
    }
    if(pos != 0) {
        for(int j = pos; j < 4; ++j) {
            this->buf4[j] = '\0';
        }
        this->buf4_to_buf3(this->buf4, this->buf3);
        for(int i = 0; i < pos; ++i) {
            result += this->buf3[i];
        }
    }
    return result;
}

unsigned char Base64::tranform(const char &c) {
    if(c >= 'A' && c <= 'Z') {
        return c - 'A';
    }

    if(c >= 'a' && c <= 'z') {
        return c - 'a' + 26;
    }

    if(c >= '0' && c <= '9') {
        return c - '0' + 26 +26;
    }

    if(c == '+') return 62;
    if(c == '/') return 63;
    return 255;
}