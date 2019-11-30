#include <cstring>
#include <regex>
#include "interface.h"
#include "stdio.h"
#include "string.h"

Date::Date(string date) {

    regex e (R"([12]\d{3}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01]))");

    if (!regex_match(date, e)) {
        throw "Error, Wrong date format.";
    }

    this->date = date;
}

bool Date::operator<(const Date &d) const {
    return std::strcmp(this->date.c_str(),d.date.c_str()) < 0;
}

bool Date::operator>(const Date &d) const {
    return std::strcmp(this->date.c_str(),d.date.c_str()) > 0;
}

bool Date::operator==(const Date &d) const {
    return std::strcmp(this->date.c_str(),d.date.c_str()) == 0;
}

