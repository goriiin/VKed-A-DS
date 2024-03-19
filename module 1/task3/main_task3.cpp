#include <iostream>
#include "../DataStr/queue/queue.h"



void Ans(std::istream &in, std::ostream &out){
    int n;
    queue Q;
    int num, opCode;
    in >> n;
    bool flag = true;

    for (int i = 0; i < n; ++i){
        in >> opCode >> num;
        if (opCode == 2){
            if (Q.pop() != num){
                flag = false;
            }
        }
        else if (opCode == 3){
            Q.push(num);
        }
    }

    if (flag)
        out << "YES";
    else
        out << "NO";
}

int main(){
    Ans(std::cin, std::cout);
}