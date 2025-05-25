#include <iostream>
#include "MyStack/MyStack.h"



void Print(int number, MyStack<int> &stack){
    MyStack<int> versa{};
    int n=0;
    std::cout<<number<<" =";
    while (!stack.empty()){
        n=stack.top_inf();
        std::cout<<" "<< n;
        stack.pop();
        versa.push(n);
    }
    std::cout<<"\n";
    std::cout<<number<<" =";
    while (!versa.empty()){
        std::cout<<" "<< versa.top_inf();
        versa.pop();
    }
    std::cout<<"\n";
}

void Multipliers(int n, MyStack<int> &stack){
    while (n % 2 == 0) {
        stack.push(2);
        n /= 2;
    }

    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            stack.push(i);
            n /= i;
        }
    }

    if (n > 1) {
        stack.push(n);
    }
}

int main(){
    MyStack<int> stack{};
    MyStack<int> stack2{};
    int n;
    std::cout<<"Введите число:";
    std::cin>>n;
    Multipliers(n, stack);
    MyStack<int> stack1(stack);
    stack2=stack;
    Print(n, stack);
}
