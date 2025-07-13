#ifndef __LOG_ANALYZER_HPP__ //__LOG_ANALYZER_HPP__
#define __LOG_ANALYZER_HPP__ //__LOG_ANALYZER_HPP__

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>


namespace BmcLog
{
class LogAnalyzer
{
public:
    explicit LogAnalyzer(const std::string& configFilePath);//throw runtime_err
    ~LogAnalyzer() = default;
    LogAnalyzer(const LogAnalyzer& other) = delete;
    LogAnalyzer& operator=(const LogAnalyzer& other) = delete;

    void DocReport();//throw runtime_err

    class Line;
    class File;
    class Dir;

    void ReadLogs();//throw runtime_err
    
    #ifndef NDEBUG
        std::string GetLogFolder() const;
        size_t GetTopN() const;
        std::vector<std::string> GetLevels() const;
        std::unordered_map<std::string,int> GetErrMessageCounter() const;
        size_t GetLineNotValid() const;
    #endif //NDEBUG

private:
    std::string m_logFolder;
    size_t m_topN;
    std::unordered_map<std::string,int> m_levelCounter;
    std::unordered_map<std::string,int> m_errMessageCounter;
    //for test
    size_t m_notValidCounter;

    void ErrMessageCounter(std::string message) noexcept;
    void LevelCounter(std::string level) noexcept;

};//class LogAnalyzer

class LogAnalyzer::Line
{
public:
    explicit Line(std::string line);//pattern: (\[(.*?)\] (\w+): (.*) , file: (.*) , line: (\d+))

    ~Line() = default;
    Line(const Line& other) = default;
    Line& operator=(const Line& other) = default;

    bool IsValid() const noexcept;
    void DoTasks(LogAnalyzer& log_analyzer) noexcept;

    #ifndef NDEBUG
        std::string GetTimestamp() const;
        std::string GetLevel() const;
        std::string GetMessage()const;
        std::string GetFileName()const;
        std::string GetLineNum()const;
    #endif //NDEBUG

private:
    std::string m_timestamp;
    std::string m_level;
    std::string m_message;
    std::string m_fileName;
    std::string m_lineNum;
    bool m_valid;

};//struct Line



class LogAnalyzer::File
{
public:
    explicit File(const std::string& filepath_);

    ~File();
    File(const File& other) = default;
    File& operator=(const File& other) = default;

    Line BreakLine();
    bool HasMoreLines() const;


private:
    std::string m_filepath;
    std::ifstream m_file;

};//class File



class LogAnalyzer::Dir
{
public:
    explicit Dir(const std::string& Path);

    ~Dir() = default;
    Dir(const Dir& other) = default;
    Dir& operator=(const Dir& other) = default;

    File GetFile();
    inline bool HasMoreFiles() const;

private:
    std::vector<std::filesystem::path> m_files;
    size_t m_lastFileIdx;

};//class Dir

}//namespace BmcLog



#endif //_LOG_ANALYZER_HPP__
