
#include <iostream>
#include <nlohmann/json.hpp>

#include "log_analyzer.hpp"

int main()
{
    BmcLog::LogAnalyzer log_analyzer("./config.json");
    log_analyzer.DocReport();

    std::ifstream file("./data.json");
    if(!file.is_open())
    {
        std::cerr << "open ./data.json failed" << std::endl;
    }

    nlohmann::json j;
    file >> j;

    //size should contain 4 kind of errors, even though N is 3 , because they have same recurring number
    if (j["top_error_messages"].size() != 4)
    {
        std::cout << "test faild" << std::endl;
    }
    std::cout << "test success" << std::endl;

    return 0;

}