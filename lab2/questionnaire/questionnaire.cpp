#include "questionnaire.h"

#include <cstring>

const int kBufferSize = 128;

namespace questionnaire {
questionnaire::questionnaire() = default;

questionnaire::questionnaire(char* name, char* surname, int age, bool answer)
    : age(age), answer(answer) {
    setName(name);
    setSurname(surname);
}

questionnaire::questionnaire(const questionnaire& o) : age(o.age), answer(o.answer) {
    setName(o.name);
    setSurname(o.surname);
}

questionnaire::~questionnaire() {
    delete[] name;
    delete[] surname;
}

char* questionnaire::getName() const {
    return name;
}

char* questionnaire::getSurname() const {
    return surname;
}

int questionnaire::getAge() const {
    return age;
}

bool questionnaire::getAnswer() const {
    return answer;
}


void questionnaire::setName(char* n) {
    delete[] name;
    name = new char[std::strlen(n) + 1];
    std::memcpy(name, n, std::strlen(n));
    name[std::strlen(n)] = '\0';
}

void questionnaire::setSurname(char* s) {
    delete[] surname;
    surname = new char[std::strlen(s) + 1];
    std::memcpy(surname, s, std::strlen(s));
    surname[std::strlen(s)] = '\0';
}

void questionnaire::setAge(int i) {
    age = i;
}

void questionnaire::setAnswer(bool a) {
    answer = a;
}


questionnaire& questionnaire::operator=(const questionnaire& p) {
    if (this == &p) {
        return *this;
    }

    this->setName(p.name);
    this->setSurname(p.surname);
    this->answer = p.answer;
    this->age = p.age;
    return *this;
}

bool operator==(const questionnaire& lhs, const questionnaire& rhs) {
    return (std::strcmp(lhs.name, rhs.name) == 0);
}

bool operator!=(const questionnaire& lhs, const questionnaire& rhs) {
    return !(lhs == rhs);
}

bool operator<(const questionnaire& lhs, const questionnaire& rhs) {
    if (std::strcmp(lhs.name, rhs.name) == 0) {
        if (std::strcmp(lhs.surname, rhs.surname) == 0) {
            if (lhs.age == rhs.age) {
                return lhs.answer < rhs.answer;
            }
            return lhs.age < rhs.age;
        }
        return std::strcmp(lhs.surname, rhs.surname) < 0;
    }
    return std::strcmp(lhs.name, rhs.name) < 0;
}

std::istream& operator >>(std::istream& in, questionnaire& p) {
    char name[kBufferSize];
    char surname[kBufferSize];
    int age = 0;
    bool answer = false;

    in >> name >> surname >> age >> answer ;
    p.setName(name);
    p.setSurname(surname);
    p.setAge(age);
    p.setAnswer(answer == 1);

    return in;
}

std::ofstream& operator << (std::ofstream& out, const questionnaire& p) {
    out << p.getName() << ' ' << p.getSurname() << ' ' << p.getAge() << ' ' << p.getAnswer() << '\n';
    return out;
}
std::ostream& operator << (std::ostream& out, const questionnaire& p) {
    out << p.getName() << ' ' << p.getSurname() << ' ' << p.getAge() << ' ' << p.getAnswer() << '\n';
    return out;
}

}  // namespace questionnaire
