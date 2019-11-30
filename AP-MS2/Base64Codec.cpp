#include "Base64Codec.h"

std::string server_side::Base64Codec::encodeValue(const std::string &value) {

    unsigned char const *bytesToEncode = (unsigned char const *) value.c_str();

    unsigned int valueLength = (unsigned int) value.size();

    std::string encodedValue;
    int i = 0;
    int j = 0;
    unsigned char charArr3[3];
    unsigned char charArr4[4];

    while (valueLength--) {
        charArr3[i++] = *(bytesToEncode++);
        if (i == 3) {
            charArr4[0] = (unsigned char) ((charArr3[0] & 0xfc) >> 2);
            charArr4[1] = (unsigned char) (((charArr3[0] & 0x03) << 4) + ((charArr3[1] & 0xf0) >> 4));
            charArr4[2] = (unsigned char) (((charArr3[1] & 0x0f) << 2) + ((charArr3[2] & 0xc0) >> 6));
            charArr4[3] = (unsigned char) (charArr3[2] & 0x3f);

            for (i = 0; (i < 4); i++)
                encodedValue += base64Chars[charArr4[i]];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++)
            charArr3[j] = '\0';

        charArr4[0] = (unsigned char) (charArr3[0] & 0xfc) >> 2;
        charArr4[1] = (unsigned char) (((charArr3[0] & 0x03) << 4) + ((charArr3[1] & 0xf0) >> 4));
        charArr4[2] = (unsigned char) (((charArr3[1] & 0x0f) << 2) + ((charArr3[2] & 0xc0) >> 6));

        for (j = 0; (j < i + 1); j++)
            encodedValue += base64Chars[charArr4[j]];

        while ((i++ < 3))
            encodedValue += '=';

    }

    return encodedValue;

}

std::string server_side::Base64Codec::decodeValue(const std::string &value) {
    int valueLen = (int) value.size();
    int i = 0;
    int j = 0;
    int endlCheck = 0;
    unsigned char charArr4[4], charArr3[3];
    std::string ret;

    while (valueLen-- && (value[endlCheck] != '=') && isBase64((unsigned char) value[endlCheck])) {
        charArr4[i++] = (unsigned char) value[endlCheck];
        endlCheck++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                charArr4[i] = (unsigned char) (base64Chars.find(charArr4[i]));

            charArr3[0] = (unsigned char) ((charArr4[0] << 2) + ((charArr4[1] & 0x30) >> 4));
            charArr3[1] = (unsigned char) (((charArr4[1] & 0xf) << 4) + ((charArr4[2] & 0x3c) >> 2));
            charArr3[2] = (unsigned char) (((charArr4[2] & 0x3) << 6) + charArr4[3]);

            for (i = 0; (i < 3); i++)
                ret += charArr3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = 0; j < i; j++)
            charArr4[j] = (unsigned char) (base64Chars.find(charArr4[j]));

        charArr3[0] = (unsigned char) ((charArr4[0] << 2) + ((charArr4[1] & 0x30) >> 4));
        charArr3[1] = (unsigned char) (((charArr4[1] & 0xf) << 4) + ((charArr4[2] & 0x3c) >> 2));

        for (j = 0; (j < i - 1); j++) ret += charArr3[j];
    }

    return ret;
}

bool server_side::Base64Codec::isBase64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}
