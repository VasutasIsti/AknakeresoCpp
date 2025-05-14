#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <iostream>
#include <limits>

template <typename T>
void askQuestion(T& ret, const char* question, T defaultVal) {
    std::string answer;
    std::cout << question << " [" << defaultVal << "]: ";
    std::getline(std::cin, answer);
    if (answer.empty()) return;
    if (answer.length() >=1)
        ret = answer;
    // Hogy ne vegye be az elozo kerdes enteret mint ervenyes igen valasz
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// Nem sikerult az a kiserlet, hogy belul a valtozo tipusatol fuggoen menjen a konvertalas...
template <>
void askQuestion(int& ret, const char* question, int defaultVal) {
    std::string answer;
    std::cout << question << " [" << defaultVal << "]: ";
    std::getline(std::cin, answer);
    if (answer.empty()) return;
    if (answer.length() >=1)
        ret = std::stoi(answer);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
template <>
void askQuestion(double& ret, const char* question, double defaultVal) {
    std::string answer;
    std::cout << question << " [" << defaultVal << "]: ";
    std::getline(std::cin, answer);
    if (answer.empty()) return;
    if (answer.length() >=1)
        ret = std::stod(answer);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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