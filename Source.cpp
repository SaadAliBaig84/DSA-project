#include<iostream>
#include<vector>
#include<string>
#include"getWords.h"
#include"validateQuery.h"

int main() {
    
    std::string line;
    std::vector<std::string> v;

    while (std::getline(std::cin, line))
    {
        if (line.empty()) {
            break;
        }
        v.push_back(line);
    }
    getWords g1;
    vector<std::string> finalWords = g1.GetWords(v);
    validateQuery vq;
    //cout << vq.validate(finalWords);
    if (vq.validate(finalWords)) {
        if (vq.query.second.size() > 0) {
            std::cout << "table name: " << vq.query.first << std::endl;
            for (int i = 0; i < vq.query.second.size(); i++) {
                std::cout << "column " << i + 1 << " : " << vq.query.second[i].first << "\t" << vq.query.second[i].second << std::endl;

            }
        }
        int count = 0;
        if (vq.insertQuery.second.size() > 0) {
            std::cout << "table name: " << vq.insertQuery.first << std::endl;
            for (int i = 0; i < vq.insertQuery.second.size(); i++) {
                if (i % 6 == 0) {
                    count++;
                    std::cout << std::endl;
                }
                std::cout << " Row " << count << " : " << vq.insertQuery.second.at(i).first << " -> " << vq.insertQuery.second.at(i).second << std::endl;
            }
        }
        
    }
    return 0;



}
