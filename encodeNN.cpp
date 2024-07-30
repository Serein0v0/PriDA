#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
int main() {
    std::ifstream file("graph_sensor_locations.csv");  // 打开CSV文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    std::vector<float> thirdColumn;  // 存储第三列的浮点数数据
    std::vector<float> fourthColumn;  // 存储第四列的浮点数数据
    std::string line;
    
    std::getline(file, line);

    while (std::getline(file, line)) {  
        std::stringstream ss(line); 
        std::string item;
        int columnIndex = 0;

        // 解析每一列
        while (std::getline(ss, item, ',')) {
            if (columnIndex == 2) {  // 第三列数据
                try {
                    float value = std::stof(item);  
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



    // 这一步骤是把经纬度转换成新的坐标系，但是，简单地去平移坐标没有太大意义。
  //  for (float& value : thirdColumn) {
  //      value = (value-34)*100;
  //  }

  //  for (float& value : fourthColumn) {
  //      value = (value+118)*100;
  //  }

    auto begin = std::chrono::high_resolution_clock::now();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<std::vector<float>> vectors;
  //  for (size_t i = 0; i < thirdColumn.size(); ++i) {
    for (size_t i = 0; i < 3; ++i) {
        std::vector<float> vector;
        float x = thirdColumn[i];
        float y = fourthColumn[i];
        float r = static_cast<float>(std::rand()) / RAND_MAX;  // 生成随机数 r
        vector.push_back(x * x + y * y);
        vector.push_back(-2 * x);
        vector.push_back(-2 * y);
        vector.push_back(1);
        vector.push_back(r);
        vectors.push_back(vector);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed =end - begin;
    std::cout << elapsed.count() << " ms" << std::endl;
    printf("Time measured: %.3f ms.\n", elapsed.count());
    // 输出向量数组
    std::cout << "生成的向量数组:" << std::endl;
  //  for (const auto& vec : vectors) {
     //   for (float val : vec) {
    //        std::cout << val << " ";
     //   }
     //   std::cout << std::endl;
  //  }

    return 0;
}


