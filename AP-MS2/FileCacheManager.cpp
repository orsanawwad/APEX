#include <sstream>
#include "FileCacheManager.h"

bool FileCacheManager::doesExist(std::string key) {
    cache_mutex.lock();
    bool result = solutionsMap.count(key) > 0;
    cache_mutex.unlock();
    return result;
}

std::string FileCacheManager::get(std::string key) {
    std::string result;
    cache_mutex.lock();
//    if (doesExist(key)) {
    result = solutionsMap[key];
//    } else {
//        result = "-1";
//    }
    cache_mutex.unlock();
    return result;
}

void FileCacheManager::set(std::string key, std::string value) {

    cache_mutex.lock();
    this->solutionsMap[key] = value;
    saveToFile(solutionsMap);
    cache_mutex.unlock();

}

FileCacheManager::FileCacheManager() : FileCacheManager(DEFAULT_CACHE) {}

FileCacheManager::FileCacheManager(std::string fileName) {
    this->fileName = fileName;
    this->solutionsMap = loadFromFile();
}

std::unordered_map<std::string, std::string> FileCacheManager::loadFromFile() {
    string line;
    std::unordered_map<string, string> tempMap;

    ifstream myfile(fileName);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            vector<string> splitResult;
            splitResult = parseCSVLine(line);
            tempMap[base64Codec.decodeValue(splitResult[0])] = base64Codec.decodeValue(splitResult[1]);
        }
        myfile.close();
    } else cout << "Unable to open file2";
    return tempMap;
}

void FileCacheManager::saveToFile(unordered_map<string, string> problemSoultion) {

    ofstream myfile(this->fileName);
    if (myfile.is_open()) {
        for (auto const &pair: problemSoultion) {
            myfile << base64Codec.encodeValue(pair.first) + "," + base64Codec.encodeValue(pair.second) + "\n";
        }
        myfile.close();
    } else cout << "Unable to open file1";

}

std::vector<std::string> FileCacheManager::parseCSVLine(std::string line) {
    std::stringstream rowStream(line);
    std::vector<char> cellValue;
    std::vector<std::string> rowValues;
    char i;
    while (rowStream >> i) {
        cellValue.push_back(i);
        if (rowStream.peek() == ',') {
            rowValues.push_back(std::string(cellValue.begin(), cellValue.end()));
            cellValue.clear();
            rowStream.ignore();
        }
    }
    rowValues.push_back(std::string(cellValue.begin(), cellValue.end()));
    cellValue.clear();
    return rowValues;
}

FileCacheManager::~FileCacheManager() {}
