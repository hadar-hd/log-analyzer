

#include "log_analyzer.hpp"

int main()
{
    bool res = true;

    BmcLog::LogAnalyzer log_analyzer("./config.json");
    log_analyzer.DocReport();

    if(log_analyzer.GetLineNotValid() != 6)
    {
        res = false;
        std::cout << "test: line not valid: " << log_analyzer.GetLineNotValid() << std::endl;
    }

    //total tests
    std::cout << "test lines not valid : " << (res ? "success" : "fail") << std::endl;

    return 0;

}