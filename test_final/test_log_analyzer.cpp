

#include "log_analyzer.hpp"

int main()
{
    BmcLog::LogAnalyzer log_analyzer("./config.json");
    log_analyzer.DocReport();

    return 0;

}