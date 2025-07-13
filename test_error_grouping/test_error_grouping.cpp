#include "log_analyzer.hpp"


//compile with no -DNDEBUG
//execute should be saved in the same folder of test_error_grouping
int main()
{
    bool res = true;

    BmcLog::LogAnalyzer log_analayzer1("./test_error_grouping.json");
    log_analayzer1.ReadLogs();

    std::unordered_map<std::string,int> ErrMap = log_analayzer1.GetErrMessageCounter();

    if(ErrMap.count("Connection failed"))
    {
        if(ErrMap["Connection failed"] != 6)
        {
            res = false;
            std::cout << "test failed - num of Connection failed is " << ErrMap["Connection failed"] << std::endl;
        }
    }
    else
    {
        res = false;
        std::cout << "test failed - not found Connection failed" << std::endl;
    }


    if(ErrMap.count("Failed Open File"))
    {
        if(ErrMap["Failed Open File"] != 7)
        {
            res = false;
            std::cout << "test failed - num of Failed Open File is " << ErrMap["Filed Open File"] << std::endl;
        }
    }
    else
    {
        res = false;
        std::cout << "test failed - not found Failed Open File" << std::endl;
    }


    if(ErrMap.count("Alloc Failed"))
    {
        if(ErrMap["Alloc Failed"] != 5)
        {
            res = false;
            std::cout << "test failed - num of Alloc Failed is " << ErrMap["Alloc Failed"] << std::endl;
        }
    }
    else
    {
        res = false;
        std::cout << "test failed - not found Alloc Failed" << std::endl;
    }


    if(ErrMap.count("Not Valid"))
    {
        if(ErrMap["Not Valid"] != 3)
        {
            res = false;
            std::cout << "test failed - num of Not Valid is " << ErrMap["Not Valid"] << std::endl;
        }
    }
    else
    {
        res = false;
        std::cout << "test failed - not found Not Valid" << std::endl;
    }

    //===========================================================================


    //total tests
    std::cout << "test Error grouping : " << (res ? "success" : "fail") << std::endl;
}