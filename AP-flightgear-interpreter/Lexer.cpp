#include <sstream>
#include <iostream>
#include <algorithm>
#include "Lexer.h"

/**
 * Split and return vector
 * @param s string
 * @return vector of words
 */
vector<string> Lexer::process(string s) {
    vector<string> vector1;
    vector<string> vector2;
    vector<string> vector3;
    vector<string> finalVector;
    vector<string> temp;
    vector<string> result;

    unsigned int i, j;
    vector1 = spaceCutter(s);

    for (i = 0; i < vector1.size(); ++i) {
        string str;

        for (j = 0; j < vector1[i].length(); ++j) {
            str += vector1[i].at(j);
        }
        vector2.push_back(str);
    }

    for (i = 0; i < vector2.size(); ++i) {
        std::string str;
        string s;
        str = addSpaces(vector2[i]);
        vector3.push_back(str);
    }


    for (i = 0; i < vector3.size(); i++) {
        temp = spaceCutter(vector3[i]);
        for (unsigned int j = 0; j < temp.size(); j++) {
            result.push_back(temp[j]);
        }
    }

    for (unsigned int k = 0; k < result.size(); ++k) {
        if (result[k] != "") {
            if (*result[k].begin() == '\"') {
                std::stringstream stream;
                stream << result[k];
                while (result[k].back() != '\"') {
                    k++;
                    stream << ' ';
                    stream << result[k];
                }
                finalVector.push_back(stream.str());
                continue;
            }
            finalVector.push_back(result[k]);
        }
    }
    return finalVector;

}


vector<string> Lexer::spaceCutter(string s) {


    std::replace(s.begin(), s.end(), '\n', ' ');

    vector<string> spilt;
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, ' ')) {
        spilt.push_back(token);
    }
    return spilt;
}


string Lexer::addSpaces(string input) {
    string output;

    bool isQuote = false;

    for (char ch : input) {
        if (ch == '\"') {
            isQuote = !isQuote;
            output += ch;
            continue;
        }

        if (isQuote) {
            output += ch;
            continue;
        }

        switch (ch) {
            case '(':
            case ')':
            case '*':
            case '+':
            case '/':
            case '-':
                output += ' ';
                output += ch;
                output += ' ';

                continue;
            default:
                output += ch;
                break;
        }
    }

    return output;
}

Lexer::Lexer() {}
