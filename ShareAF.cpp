#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>


void additiveSecretSharing(const std::vector<int>& AF, std::vector<int>& AF1, std::vector<int>& AF2) {
    size_t size = AF.size();
    AF1.resize(size);
    AF2.resize(size);
    
    std::srand(std::time(nullptr));
    
       for (size_t i = 0; i < size; ++i) {
        int r1 = std::rand() % (AF[i] + 1);
        AF1[i] = r1;
        AF2[i] = AF[i] - r1;
    }
}

int main() {
    // 测试
    std::vector<int> AF = {5, 10, 15, 20};
    std::vector<int> AF1;
    std::vector<int> AF2;
    
    additiveSecretSharing(AF, AF1, AF2);
    
    std::cout << "AF: ";
    for (int val : AF) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "AF1: ";
    for (int val : AF1) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "AF2: ";
    for (int val : AF2) std::cout << val << " ";
    std::cout << std::endl;

    return 0;
}
