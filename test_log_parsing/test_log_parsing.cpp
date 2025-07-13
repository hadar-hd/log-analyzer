#include "log_analyzer.hpp"

int main() //compile with no -DNDEBUG
{
    bool res = true;
    //pattern: (\[(.*?)\] (\w+): (.*) , file: (.*) , line: (\d+))

    //test: log written according to the expected format
    BmcLog::LogAnalyzer::Line line1("[2025-07-08 12:00:00] INFO: Application started , file: hadar.cpp , line: 42");
    if(line1.IsValid() != true)
    {
        res = false;
        std::cout << "test1: IsValid error: " << line1.IsValid() << std::endl;
    }
    if(line1.m_timestamp != "2025-07-08 12:00:00")
    {
        res = false;
        std::cout << "test1: Timestamp error: " << line1.m_timestamp << std::endl;
    }
    if(line1.m_level != "INFO")
    {
        res = false;
        std::cout << "test1: Level error: " << line1.m_level << std::endl;
    }
    if(line1.m_message != "Application started")
    {
        res = false;
        std::cout << "test1: Message error: " << line1.m_message << std::endl;
    }
    if(line1.m_fileName != "hadar.cpp")
    {
        res = false;
        std::cout << "test1: FileName error: " << line1.m_fileName << std::endl;
    }
    if(line1.m_lineNum != "42")
    {
        res = false;
        std::cout << "test1: LineNum error: " << line1.m_lineNum << std::endl;
    }

    //test: log that is not written according to partially expected format at all
    BmcLog::LogAnalyzer::Line line2("2025-07-08 12:00:00 INFO Application started");
    if(line2.IsValid() != false)
    {
        res = false;
        std::cout << "test2: IsValid error: " << line2.IsValid() << std::endl;
    }

    //test: A log whose message is longer than a line


    //test: Log missing message
    BmcLog::LogAnalyzer::Line line3("[2025-07-08 12:00:00] INFO: , file: hadar.cpp , line: 42");
    if(line3.IsValid() != false)
    {
        res = false;
        std::cout << "test3: IsValid error: " << line3.IsValid() << std::endl;
    }

    //total tests
    std::cout << "test log parsing : " << (res ? "success" : "fail") << std::endl;
}