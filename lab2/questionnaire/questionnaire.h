#pragma once

#include <fstream>
#include <iostream>

namespace questionnaire {
class questionnaire {
 public:
    questionnaire();
    questionnaire(char* name, char* surname, int age, bool answer);
    questionnaire(const questionnaire& o);
    ~questionnaire();

    char* getName() const;
    char* getSurname() const;
    int getAge() const;
    bool getAnswer() const;

    void setName(char* n);
    void setSurname(char* s);
    void setAge(int i);
    void setAnswer(bool b);


    questionnaire& operator=(const questionnaire& p);
    friend bool operator==(const questionnaire& lhs, const questionnaire& rhs);
    friend bool operator!=(const questionnaire& lhs, const questionnaire& rhs);
    friend bool operator<(const questionnaire& lhs, const questionnaire& rhs);

 private:
    char* name = nullptr;
    char* surname = nullptr;
    int age = 0;
    bool answer = false;
};

std::istream& operator >>(std::istream& in, questionnaire& p);
std::ofstream& operator <<(std::ofstream& out, const questionnaire& p);
std::ostream& operator <<(std::ostream& out, const questionnaire& p);
}  // namespace questionnaire
