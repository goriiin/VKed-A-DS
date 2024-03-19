#include <iostream>

unsigned int evenUnits(unsigned int num){
    unsigned int count = 0;
    int i = 0;
    while (num){
        if (num & 1)
            ++count;
        num >>=2;
        std::cout <<i++ << " " << num << " " << count << std::endl;
    }
    return count;
}

int main(){
    unsigned int n = 0;
    std::cin >> n;
    std::cout << evenUnits(n);
}