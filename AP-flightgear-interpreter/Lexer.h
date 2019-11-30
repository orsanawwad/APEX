
#ifndef APEX_LEXER_H
#define APEX_LEXER_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Lexer {
private:
    Lexer();

public:
    Lexer(Lexer const &) = delete;

    void operator=(Lexer const &) = delete;

    static std::shared_ptr<Lexer> getInstance() {
        static std::shared_ptr<Lexer> s{new Lexer};
        return s;
    }

    /**
     * This method read a line a process it to a vector of strings.
     * @param s line given.
     * @return a vector of strings after proccessing.
     */
    ::vector<string> process(string s);

    /**
     * this method cuts a sting given by space.
     * @param s the string given.
     * @return a vector of stings that was spilt by space.
     */
    ::vector<string> spaceCutter(string s);

    /**
     * this method adds space between strings.
     * @param input the string to add space in.
     * @return the new string after adding space.
     */
    string addSpaces(string input);
};


#endif //APEX_LEXER_H
