#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "planet/planet.h"
#include "questionnaire/questionnaire.h"

namespace {
const int kBufferSize = 128;

template<typename T>
struct array {
    unsigned int size = 0;
    unsigned int capacity = 8;
    T* array = new T[capacity];
};

int GlobalMenu(){
    int choise=0;
    std::cout << "Выберите тему" << '\n';
    std::cout << "1 - Планеты" << '\n';
    std::cout << "2 - Анкета" << '\n';
    std::cin >> choise;
    return choise;
}

template<typename T>
void increaseArray(array<T>& s) {
    s.capacity = s.capacity << 1;
    T* buffer = new T[s.capacity];

    std::copy(s.array, s.array + s.size, buffer);

    T* oldSystem = s.array;
    s.array = buffer;

    delete[] oldSystem;
}

void ShowPlanetsMenu() {
    std::cout << "Выберете пункт меню" << '\n';
    std::cout << "1 - Добавить планету" << '\n';
    std::cout << "2 - Удалить планету" << '\n';
    std::cout << "3 - Изменить информацию о планете" << '\n';
    std::cout << "4 - Вывести на экран планету" << '\n';
    std::cout << "5 - Вывести на экран все планеты" << '\n';
    std::cout << "0 - Завершение работы" << '\n';
}

void ShowQuestionnaireMenu() {
    std::cout << "Выберете пункт меню" << '\n';
    std::cout << "1 - Добавить информацию об опрашиваемом" << '\n';
    std::cout << "2 - Удалить информацию об опрашиваемом" << '\n';
    std::cout << "3 - Изменить информацию об опрашиваемом" << '\n';
    std::cout << "4 - Вывести на экран информацию об опрашиваемом" << '\n';
    std::cout << "5 - Вывести на экран всю информацию" << '\n';
    std::cout << "0 - Завершение работы" << '\n';
}


int ReadSelectionFromStdin() {
    int selection = 0;
    std::cin >> selection;
    return selection;
}

planet::planet ReadPlanetFromStdin() {
    std::cout << "Введите имя планеты, диаметр, есть ли на ней жизнь (1/0), количество спутников : ";
    planet::planet p;
    std::cin >> p;
    return p;
}

questionnaire::questionnaire ReadQuestionnairetFromStdin() {
    std::cout << "Введите имя опрашиваемого, фамилию, возраст, ответ (1/0) : ";
    questionnaire::questionnaire p;
    std::cin >> p;
    return p;
}


template<typename T>
void Add(array<T>& s, const T e) {
    if (s.size == s.capacity) {
        increaseArray(s);
    }

    // int i = 0;
    // while (i < s.size && s.array[i] < e) {
    //     ++i;
    // }
    // for (int j = s.size; j > i; --j) {
    //     s.array[j] = s.array[j - 1];
    // }
    s.array[s.size] = e;
    ++s.size;
}

template<typename T>
void Remove(array<T>& s, int i) {
    if (i > s.size || i <= 0) {
        std::cout << "Нет такого пункта" << '\n';
        return;
    }

    --i;

    while (i < s.size-1) {
        s.array[i] = s.array[i + 1];
        ++i;
    }
    --s.size;
}

template<typename T>
void Clear(array<T>& s) {
    while (s.size > 0) {
        Remove(s, s.size);
    }
}

void Edit(array<planet::planet>& s, int i) {
    int selectedItem = i - 1;
    int action = -1;
    while (action != 0) {
        std::cout << "Выберите что нужно исправить: 1) Имя 2) Диаметр 3) Наличие жизни 4) Количество спутников  0) Ничего" << '\n';
        std::cin >> action;

        switch (action) {
            case 1:
                char buffer[kBufferSize];
                std::cout << "Введите имя планеты: ";
                std::cin >> buffer;
                s.array[selectedItem].setName(buffer);
                break;
            case 2:
                unsigned int diameter;
                std::cout << "Введите диаметр планеты: ";
                std::cin >> diameter;
                s.array[selectedItem].setDiameter(diameter);
                break;
            case 3:
                bool life;
                std::cout << "Есть ли жизнь на планете? (0/1): ";
                std::cin >> life;
                s.array[selectedItem].setLife(life == 1);
                break;
            case 4:
                unsigned int satellite;
                std::cout << "Введите количество спутников: ";
                std::cin >> satellite;
                s.array[selectedItem].setSatellite(satellite);
                break;
            default:
                break;
        }
    }
}

void Edit(array<questionnaire::questionnaire>& s, int i) {
    int selectedItem = i - 1;
    int action = -1;
    while (action != 0) {
        std::cout << "Выберите что нужно исправить: 1) Имя 2) Фамилию 3) Возраст 4) Ответ  0) Ничего" << '\n';
        std::cin >> action;

        switch (action) {
            case 1:
                char buffer[kBufferSize];
                std::cout << "Введите имя опрашиваемого: ";
                std::cin >> buffer;
                s.array[selectedItem].setName(buffer);
                break;
            case 2:
                char surname[kBufferSize];
                std::cout << "Введите Фамилию опрашиваемого: ";
                std::cin >> surname;
                s.array[selectedItem].setSurname(surname);
                break;
            case 3:
                int age;
                std::cout << "Введите возраст опрашиваемого: ";
                std::cin >> age;
                s.array[selectedItem].setAge(age);
                break;
            case 4:
                unsigned int answer;
                std::cout << "Введите ответ (1/0): ";
                std::cin >> answer;
                s.array[selectedItem].setAnswer(answer == 1);
                break;
            default:
                break;
        }
    }
}

template<typename T>
void LoadFromFile(array<T>& s, const char* fileName) {
    std::ifstream file;
    file.open(fileName, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл " << fileName << "\n";
        return;
    }

    // char buffer[kBufferSize];
    // if (file.getline(buffer, sizeof(buffer))) {
    //     int length = std::atoi(buffer);

     T e;
     while (file>>e) {
        Add(s,e);
     }
    //     for (int i = 0; i < length; ++i) {
       //     file >> e;
     //  T e();
           // Add(s, e);
    //     }
    // }

     file.close();
}

template<typename T>
void CloseFile(array<T>& s, const char* fileName) {
    std::ifstream file(fileName);
    file.close();
}

}  // namespace

void RunPlanet() {
    array<planet::planet> planets;
    LoadFromFile(planets, "Planets.txt");
    int i = 0;

    while (true) {
        ShowPlanetsMenu();
        switch (ReadSelectionFromStdin()) {
            case 1:
                Add(planets, ReadPlanetFromStdin());
                break;
            case 2:
                std::cout << "Введите номер планеты: ";
                Remove(planets, ReadSelectionFromStdin());
                break;
            case 3:
                std::cout << "Введите номер планеты: ";
                Edit(planets, ReadSelectionFromStdin());
                break;
            case 4:
                std::cout << "Введите номер планеты: ";
                std::cin >> i;
                std::cout << planets.array[i - 1];
                break;
            case 5:
                for (int i = 0; i < planets.size; ++i) {
                std::cout << i + 1 << ". ";
                std::cout << planets.array[i];
                }
                break;
            default:
                return;
        }
    }
}

void RunQuestionnaire() {
    array<questionnaire::questionnaire> questionnaires;
    LoadFromFile(questionnaires, "Questionnaire.txt");
    int i = 0;

    while (true) {
        ShowQuestionnaireMenu();
        switch (ReadSelectionFromStdin()) {
            case 1:
                Add(questionnaires, ReadQuestionnairetFromStdin());
                break;
            case 2:
                std::cout << "Введите номер опрашиваемого в списке: ";
                Remove(questionnaires, ReadSelectionFromStdin());
                break;
            case 3:
                std::cout << "Введите номер опрашиваемого в списке: ";
                Edit(questionnaires, ReadSelectionFromStdin());
                break;
            case 4:
                std::cout << "Введите номер опрашиваемого в списке: ";
                std::cin >> i;
                std::cout << questionnaires.array[i - 1];
                break;
            case 5:
                for (int i = 0; i < questionnaires.size; ++i) {
                std::cout << i + 1 << ". ";
                std::cout << questionnaires.array[i];
                }
                break;
            default:
                CloseFile(questionnaires, "Questionnaire.txt");
                return;
        }
    }
}


int main(int argc, char** argv) {
    if (GlobalMenu() == 1){
        RunPlanet();
    } else {
        RunQuestionnaire();
    }
    return 0;
}
