
#include <iostream>
#include <nlohmann/json.hpp>

#include "log_analyzer.hpp"

int main()
{
    BmcLog::LogAnalyzer log_analyzer("./config.json");
    log_analyzer.DocReport();

    std::cout << "file data.json open in directory" << std::endl;

    std::ifstream file("./data.json");
    if(!file.is_open())
    {
        std::cerr << "open ./data.json failed" << std::endl;
    }

    nlohmann::json j;
    file >> j;

    bool res = true;
    if (j["level_stats"]["ERROR"] != 10)
    {
        res = false;
        std::cout << "test level_stats ERROR faild" << std::endl;
    }
    if (j["level_stats"]["INFO"] != 6)
    {
        res = false;
        std::cout << "test level_stats INFO faild" << std::endl;
    }
    if (j["level_stats"]["WARN"] != 6)
    {
        res = false;
        std::cout << "test level_stats WARN faild" << std::endl;
    }
    if(j["top_error_messages"].size() != 3)
    {
        res = false;
        std::cout << "test top_error_messages faild" << std::endl;
    }
    if(j["total_lines processed"] != 22)
    {
        res = false;
        std::cout << "test total lines processed faild" << std::endl;
    }

        //total tests
    std::cout << "final test: " << (res ? "success" : "fail") << std::endl;

    return 0;

}