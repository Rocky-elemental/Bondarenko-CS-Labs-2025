#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <random>
#include <list>
#include <map>
#include <bits/stdc++.h>


int ShowMenu(){
    int n;
    std::cout<<"Выберите номер задания (1-9)\n";
    std::cin>>n;
    return n;
}

void Task1(){
    std::string s;
    std::cout<<"Введите текст содержащий символ: ; \n";
  //  std::cin.getline(s);
  std::cin.clear();
  std::cin.ignore();
    std::getline(std::cin, s);
    auto i= std::find(s.begin(), s.end(), ';');
    while (i!=s.end()){
        std::cout<< std::distance(s.begin(), i) <<" ";
        i= std::find(i+1, s.end(),';');
    }
    std::cout<<"\n";
}

void Task2(){
    std::string s;
    std::string s1;
    std::cin.clear();
    std::cin.ignore();
    std::cout<< "Введите последовательность символов:\n";
    getline(std::cin, s);
    for (int i=0; i<s.length(); i+=2){
        s1+= s[i];
    }
    std::cout<<s1 <<"\n";
}

void Task3(){
    std::cin.clear();
    std::cin.ignore();
    std::ifstream out("text.txt");
    std::ofstream in("newText.txt");
    if (!out.is_open() || !in.is_open()) {
        std::cout << "Ошибка открытия файла." << std::endl;
        return;
    }
    std::string line;
    char symbol, newSymbol;
    std::cout << "Введите старый символ: \n";
    std::cin >> symbol;
    std::cout << "Введите новый символ: \n";
    std::cin >> newSymbol;
    while (getline(out, line)){
        for (int i=0; i<line.size(); ++i){
            if (line[i]==symbol){
                line[i]=newSymbol;
            }
        }
        in << line <<"\n";
    }
    out.close();
    in.close();

}

float RandomFloat(){
    return (float)(rand()) / (float)(rand());
}

void printVector(std::vector<float> v){
    for (int i=0; i<v.size(); ++i){
        std::cout<<v[i]<<" ";
    }
    std::cout<<"\n";
}

void Task4(){
    std::cin.clear();
    std::cin.ignore();
    std::vector<float> v(25);
    for (int i = 0; i < v.size(); ++i) {
        v[i] = RandomFloat();
    }
    printVector(v);
    for (int i = 0; i < v.size(); ++i) {
        v[i] *= v[i];
    }
    printVector(v);
    v.erase(v.begin()+4);
    printVector(v);
}

class Card {
  std::string title;   // заглавие книги
  std::string author;  // автор
  int number;     // количество имеющихся экземпляров
public:
  Card() : title(""), author(""), number(0) {}
  Card(std::string t, std::string a, int n) : title(t), author(a), number(n) {}
  std::string getTitle() const {return title;}
  std::string getAuthor() const {return author;}
  int getNumber() const {return number;}
};
std::ostream& operator << (std::ostream& out, const Card& obj) {
    out << obj.getTitle() << ' ' << obj.getAuthor() << ' ' << obj.getNumber() << '\n';
    return out;
}
bool operator == (const Card& a, std::string b){
    return a.getAuthor()== b;
}

void Task5(){
    std::cin.clear();
    std::cin.ignore();
    std::string author, test1, test2;
    test1 = "Татьяна Мастрюкова";
    test2 = "Болотница";
    std::vector<Card> books (5);
    std::cout<<"Введите автора: \n";
    std::getline(std::cin, author);
    books[0]=Card(test2, test1, 5);
    int n=0;
    for (int i=0; i<books.size(); ++i){
        if (books[i]==author){
            std::cout<<books[i];
        }
        else{
            ++n;
        }
    }
    if (n==books.size()){
        std::cout<<"Нет такого автора\n";
    }
}

void findX(std::list<int> l, int x){
    int n=0;
    std::list<int>::iterator iter;
    for (iter = l.begin(); iter != l.end(); iter++){
        if (*iter==x){
            std::cout<<"YES\n";
            break;
        }
        else {
            ++n;
        }
    }
    if (n==l.size()){
        std::cout<<"NO\n";
    }
}

void Task6(){
    std::cin.clear();
    std::cin.ignore();
    std::list<int> list(4);
    int x;
    std::cout<<"Введите число x: \n";
    std::cin>>x;
    for (int i=0; i<4; ++i){
        list.push_back(i);
    }
    findX(list, x);
}

void Task7(){
    std::cin.clear();
    std::cin.ignore();
    std::string author, test1, test2;
    test1 = "Татьяна Мастрюкова";
    test2 = "Болотница";
    std::list<Card>::iterator iter;
    std::list<Card> books (4);
    std::cout<<"Введите автора: \n";
    std::getline(std::cin, author);
    books.push_back(Card(test2, test1, 5));
    int n=0;
    for (iter = books.begin(); iter != books.end(); iter++){
        if (*iter==author){
            std::cout<<*iter;
        }
        else{
            ++n;
        }
    }
    if (n==books.size()){
        std::cout<<"Нет такого автора\n";
    }
}

void Task8(){
    std::cin.clear();
    std::cin.ignore();
    std::map<int, int> m;
    std::map<int, int>::iterator i;
    for (int n = 1; n <=20; n++){
        m[n]=n*10;
        std::cout<< m[n] << " ";
    }
    std::cout<<"\n";
    int t = m.size();
    for (int j=1; j <= t ;j+=2){
        if (j%2!=0){
            m.erase(j);
        }
    }
    for (int n = 0; n <m.size(); ++n){
        std::cout<< m[n] << " ";
    }
    std::cout<<"\n";
}

void Task9(){
    std::cin.clear();
    std::cin.ignore();
    std::string mas[4] = { "1112233", "9871234", "5671234", "5556688" };
    std::map<std::string, char*> m;
    std::string s1, s2, s3;
    s1="5671234";
    s2="3214567";
    s3="9871234";
    m[s1]="Ivanov";
    m[s2]="Petrov";
    m[s3]="Sidorov";
    for (int i=0; i<4; ++i){
        if (m.count(mas[i])){
            std::cout<< m[mas[i]]<< "\n";
        }
    }
}

int main(int argc, char** argv){
    switch(ShowMenu()){
        case 1:
            Task1();
            break;
        case 2:
            Task2();
            break;
        case 3:
            Task3();
            break;
        case 4:
            Task4();
            break;
        case 5:
            Task5();
            break;
        case 6:
            Task6();
            break;
        case 7:
            Task7();
            break;
        case 8:
            Task8();
            break;
        case 9:
            Task9();
            break;
        default:
            return 0;
    }
    return 0;
}
