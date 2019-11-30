#ifndef AP_MS2_BASE64CODEC_H
#define AP_MS2_BASE64CODEC_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#include <vector>

namespace server_side {
    class Base64Codec {
    private:
        const std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        bool isBase64(unsigned char c);

    public:
        std::string encodeValue(const std::string &value);

        std::string decodeValue(const std::string &value);
    };
}

#endif //AP_MS2_BASE64CODEC_H
