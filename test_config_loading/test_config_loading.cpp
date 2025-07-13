#include "log_analyzer.hpp"

int main() //compile with no -DNDEBUG
{
    bool res = true;

    BmcLog::LogAnalyzer log_analayzer1("./config.json");

    //folder
    if(log_analayzer1.GetLogFolder() != ".")
    {
        res = false;
        std::cout << "test1: GetLogFolder error: " << log_analayzer1.GetLogFolder() << std::endl;
    }

    //top N
    if(log_analayzer1.GetTopN() != 3)
    {
        res = false;
        std::cout << "test1: GetTopN error: " << log_analayzer1.GetTopN() << std::endl;
    }

    //levels
    std::vector<std::string> levelVec = log_analayzer1.GetLevels();
    if(levelVec.size() != 3)
    {
        res = false;
        std::cout << "test1: size GetLevels error: " << levelVec.size() << std::endl;
    }

    auto it = std::find(levelVec.begin(), levelVec.end(), "ERROR");
    if(*it != "ERROR")
    {
        res = false;
        std::cout << "test1: GetLevels not exist ERROR " << std::endl;
    }

    it = std::find(levelVec.begin(), levelVec.end(), "WARN");
    if(*it != "WARN")
    {
        res = false;
        std::cout << "test1: GetLevels not exist WARN " << std::endl;
    }

    it = std::find(levelVec.begin(), levelVec.end(), "INFO");
    if(*it != "INFO")
    {
        res = false;
        std::cout << "test1: GetLevels not exist INFO " << std::endl;
    }


    //total tests
    std::cout << "test config loading : " << (res ? "success" : "fail") << std::endl;
}