#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
int main() {
    std::ifstream file("graph_sensor_locations.csv"); 
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    std::vector<float> thirdColumn;  
    std::vector<float> fourthColumn;  
    std::string line;
    
    std::getline(file, line);

    while (std::getline(file, line)) {  
        std::stringstream ss(line);  
        std::string item;
        int columnIndex = 0;

        while (std::getline(ss, item, ',')) {
            if (columnIndex == 2) {  
                try {
                    float value = std::stof(item);  // 将字符串转换为浮点数
                    thirdColumn.push_back(value);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "无效的浮点数：" << item << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "浮点数超出范围：" << item << std::endl;
                }
            } else if (columnIndex == 3) {  
                try {
                    float valuee = std::stof(item);  
                    fourthColumn.push_back(valuee);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "无效的浮点数：" << item << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "浮点数超出范围：" << item << std::endl;
                }
            }
            columnIndex++;
        }
    }

    file.close();
   // auto begin = std::chrono::high_resolution_clock::now();
    // 
   // for (float& value : thirdColumn) {
  //      value = (value-34)*100;
  //  }
//
  //  for (float& value : fourthColumn) {
  //      value = (value+118)*100;
 //   }

    // 生成向量数组
    std::vector<std::vector<float>> vectors;
    for (size_t i = 0; i < thirdColumn.size(); ++i) {
        std::vector<float> vector;
        float x = thirdColumn[i];
        float y = fourthColumn[i];
        vector.push_back(1);
        vector.push_back(x);
        vector.push_back(y);
        vector.push_back(x * x + y * y);
        vector.push_back(-1);
        vectors.push_back(vector);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed =end - begin;
    std::cout << elapsed.count() << " ms" << std::endl;
    printf("Time measured: %.3f ms.\n", elapsed.count());
    // 输出向量数组
    std::cout << "生成的向量数组:" << std::endl;
    for (const auto& vec : vectors) {
        for (float val : vec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

