#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <iostream>
#include <sstream>

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