#include "./base64.h"

#include <iostream>
#include <string>


int main() 
{
    std::string s = "ABCD";
    char c[] = "ABC";

    Base64 b;
    std::cout << b.encode(s) << "\n" << b.encode(c) << "\n";
    //std::cout << b.decode(b.encode(s)) << "\n" << b.decode(b.encode(c)) << "\n";
    std::cout << b.decode("QUJDRA==") << "\n";
}