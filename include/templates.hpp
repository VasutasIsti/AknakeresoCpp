#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <iostream>
#include <sstream>
#include "memtrace.h"

/// @brief A felhasznalotol kerdez egy kerdest, es elmenti a valaszt.
/// @tparam T A menteni kivant adat tipusa
/// @param ret A menteni kivant adat celja
/// @param question A kerdes szovege
/// @param defaultVal A menteni kivant adat alapertelmezett erteke
template <typename T>
void askQuestion(T& ret, const char* question, T defaultVal) {
    std::string answer;
    std::cout << question << " [" << defaultVal << "]: ";
    std::getline(std::cin, answer);
    std::stringstream ss(answer);
    if (answer.empty()) {
        ret = defaultVal;
        return;
    }
    ss >> ret;    
}
/// @brief A felhasznalotol kerdez egy kerdest, es elmenti a valaszt, Stringre specifikalva.
template <>
void askQuestion(std::string& ret, const char* question, std::string defaultVal) {
    std::string answer;
    std::cout << question << " [" << defaultVal << "]: ";
    std::getline(std::cin, answer);
    if (answer.empty()) {
        ret = std::move(defaultVal);
        return;
    }
    ret = std::move(answer);
}

/// @brief A felhasznalotol kerdez egy eldontendo kerdest, es visszaadja a valaszt.
/// @param question A kerdes szovege
/// @return true, ha a felhasznalo y Y vagy ures valaszt adott, false ha n vagy N valaszt.
bool askBoolean(const char* question) {
    std::string answer;
    while (true) {
        std::cout << question;
        std::getline(std::cin, answer);
        if (answer.empty()) return true;
        if (answer.length() == 1) {
            if (answer[0] == 'Y' || answer[0] == 'y')
                return true;
            if (answer[0] == 'N' || answer[0] == 'n')
                return false;
        }
        std::cout << "Invalid input. Please try again." << std::endl;
    }
}

#endif //TEMPLATES_HPP