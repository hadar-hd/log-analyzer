#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <regex>
#include <filesystem>
#include <vector>

#include "log_analyzer.hpp"

const std::string OUTPUT_PATH = "./data.json";

using namespace BmcLog;
//============================================================================
LogAnalyzer::LogAnalyzer(const std::string& configFilePath)
:m_levelCounter(),m_errMessageCounter(), m_notValidCounter{0}
{
    std::ifstream file(configFilePath);
    if(!file.is_open())
    {
        throw std::runtime_error("open config failed");
    }

    nlohmann::json j;
    file >> j;

    m_logFolder = j.value("log_folder", ".");
    m_topN = j.value("top_n", 2);

    size_t size = j["include_levels"].size();
    for(size_t i = 0; i < size ; ++i)
    {
        m_levelCounter.insert({j["include_levels"][i], 0});
    }

    file.close();
}

//==============================================================================
                            //ErrMessageCounter
//=============================================================================
void LogAnalyzer::ErrMessageCounter(std::string message) noexcept
{
    ++m_errMessageCounter[message];
}


//==============================================================================
                              //LevelCounter
//=============================================================================
void LogAnalyzer::LevelCounter(std::string level) noexcept
{
    ++m_levelCounter[level];
}

//==============================================================================
                              // ReadLogs
//=============================================================================
void LogAnalyzer::ReadLogs()
{
    Dir dir(m_logFolder);

    while (dir.HasMoreFiles())
    {
        File file(dir.GetFile());

        while (file.HasMoreLines())
        {
            Line line(file.BreakLine());
            line.DoTasks(*this);
        }
    }
}




//==============================================================================
                              // DocReport
//=============================================================================
void LogAnalyzer::DocReport()
{
    //===================open json file=======================================
    using json = nlohmann::json;

    ReadLogs();

    std::ofstream file(OUTPUT_PATH);
    if (!file.is_open())
    {
        throw std::runtime_error("open JSON failed");
    }

    json report;
    //===================count level and total lines===========================
    size_t totalLines = 0;
    json levelStats;

    for(const auto& [key, value] : m_levelCounter)
    {
        levelStats[key] = value;
        totalLines += value;
    }

    report["level_stats"] = levelStats;
    report["total_lines processed"] = totalLines;

    //===================top N message=======================================
    json topMessages;

    //sort m_messageCounter acordding to value
    std::vector<std::pair<std::string, int> > vec(m_errMessageCounter.begin(),
                                                  m_errMessageCounter.end());

    //sort
    std::sort(vec.begin(), vec.end(),
                                    [](const auto& a, const auto& b)
                                    {
                                        return a.second > b.second;
                                    });

    size_t count = 0;
    int last_value = -1;
    for (const auto& [key, value] : vec)
    {
        if (count >= m_topN && value != last_value)
        {
            break;
        }

        topMessages.push_back({{"message", key},{"count", value}});

        last_value = value;
        ++count;
    }

    report["top_error_messages"] = topMessages;

    file << report.dump(4);

    file.close();
}

//============================================================================
                                //Line
//============================================================================
LogAnalyzer::Line::Line(std::string line)
{
    std::regex logPattern(R"(\[(.*?)\] (\w+): (.*) , file: (.*) , line: (\d+))");
    std::smatch match;

    if (std::regex_match(line, match, logPattern))
    {
        m_timestamp = match[1];
        m_level     = match[2];
        m_message   = match[3];
        m_fileName  = match[4];
        m_lineNum   = match[5];
        m_valid = true;
    }
    else
    {
        m_valid = false;
    }

}


bool LogAnalyzer::Line::IsValid() const noexcept
{
    return m_valid;
}

void LogAnalyzer::Line::DoTasks(LogAnalyzer& log_analyzer) noexcept
{
    if (IsValid())
    {
        log_analyzer.LevelCounter(m_level);

        if (m_level == "ERROR")
        {
            log_analyzer.ErrMessageCounter(m_message);
        }
    }
    else
    {
        log_analyzer.m_notValidCounter++;
    }

}

//============================================================================
                                //Dir
//============================================================================
LogAnalyzer::Dir::Dir(const std::string& path):m_lastFileIdx(0)
{
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".log")
        {
            m_files.push_back(entry.path());
        }
    }
}


LogAnalyzer::File LogAnalyzer::Dir::GetFile()
{
    return File(m_files.at(m_lastFileIdx++));
}

bool LogAnalyzer::Dir::HasMoreFiles() const
{
    return m_lastFileIdx < m_files.size();
}

//============================================================================
                                //File
//============================================================================
LogAnalyzer::File::File(const std::string& filepath_)
{
    m_file.open(filepath_);

    if (!m_file.is_open())
    {
        std::cerr << "file not open: " << filepath_ << std::endl;
    }

}

LogAnalyzer::File::~File()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}

LogAnalyzer::Line LogAnalyzer::File::BreakLine()
{
    std::string line;
    if (std::getline(m_file, line))
    {
        return Line(line);
    }
    return Line("");
}

bool LogAnalyzer::File::HasMoreLines() const
{
    return m_file.good() && !m_file.eof();
}


//============================================================================
                    //for debug
//============================================================================
#ifndef NDEBUG
    std::string LogAnalyzer::Line::GetTimestamp() const
    {
        return m_timestamp;
    }

    std::string LogAnalyzer::Line::GetLevel()const
    {
        return m_level;
    }

    std::string LogAnalyzer::Line::GetMessage()const
    {
        return m_message;
    }

    std::string LogAnalyzer::Line::GetFileName()const
    {
        return m_fileName;
    }

    std::string LogAnalyzer::Line::GetLineNum()const
    {
        return m_lineNum;
    }

std::string LogAnalyzer::GetLogFolder() const
{
        return m_logFolder;
    }

    size_t LogAnalyzer::GetTopN() const
    {
        return m_topN;
    }

    std::vector<std::string> LogAnalyzer::GetLevels() const
    {
        std::vector<std::string> levelVec;
        for(const auto& [key, value] : m_levelCounter)
        {
            levelVec.push_back(key);
        }
        return levelVec;
    }

    std::unordered_map<std::string,int>  LogAnalyzer::GetErrMessageCounter() const
    {
        return m_errMessageCounter;
    }

    size_t LogAnalyzer::GetLineNotValid() const
    {
        return m_notValidCounter;
    }

#endif //NDEBUG
