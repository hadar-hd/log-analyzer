# log-analyzer
The program analyzes .log files from a given filder.

# Input
The program receives a .json file that that contains:

{
    "log_folder":         #path to the folder containing ./log files.
    "top_n":              #number of top recuring error to report.
    "include_levels":     #list of log level to include.
}


# Output
the program outputs a data.json file containing:
- total log lines processed
- count of each log level
- top N recurring error message (level "ERROR")

# Example of using the program
#include "log_analyzer.hpp"
int main()
{
    BmcLog::LogAnalyzer log_analyzer("./config.json");
    log_analyzer.DocReport();

    return 0;
}

# Run the program
Compile the project:
You can add cpp flags as you wish.

g++ -std=c++17 log_analayzer.cpp -I(dir where log_analayzer.hpp) main.cpp -o main

Run the program
./main

# tests
To run the tests, do not compile with -DNDEBUG.
each test is located in a dedicated folder.
the folder that contains the file test and files associated with that test.
Please create the executable within the folder.

- test_log_parsing
- test_config_loading
- test_error_grouping
- testlines_not_valid
- test_final

# Using AI
chatgpt is used.

- read .log file
https://chatgpt.com/share/6872c2f1-e290-8008-9cef-58c70ec59d18

https://chatgpt.com/share/6872c393-f61c-8008-bcda-6f64ba99e546


- working with json c++
https://chatgpt.com/share/6872c33f-5edc-8008-a68c-e8ab138fc88d


- map vs unordered_map c++
https://chatgpt.com/share/6872c371-8630-8008-b3af-f6d5b516cd3e



