# log-analyzer
The program analyzes .log files from a given filder.

# Input
The program receives a .json file that that contains:

{
    "log_folder":         #path to the folder containing ./log files.
    "top_n":              #number of top recuring error to report.
    "include_levels":     #list of log level to include.
}

The folder should contain log files with the extension .log

The format of the log files should be:
[timestamp] "log level": "message" , file: "file_name" , line: "num_line"

The format can be changed in class Line.


# Output
the program outputs a data.json file containing:
- total log lines processed
- count of each include level
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

g++ -std=c++17 log_analyzer.cpp -I<path to log_analyzer.hpp> main.cpp -o main

Run the program
./main

# tests
To compile the tests, run: make

To run the tests without using the Makefile:
- Do not compile with the -DNDEBUG flag, as this may disable assertions or debug-related code.
- Each test is located in its own dedicated folder.
- The folder contains the main test file along with any files associated with that specific test.
- Please compile and create the executable within the same folder as the test.

- test_log_parsing
- test_config_loading
- test_error_grouping
- testlines_not_valid
- test_N+1_same_recurring
- test_final

you can run the executable test.out in each test folder: ./test.out

# Using AI
chatgpt is used.

- read .log file
https://chatgpt.com/share/6872c2f1-e290-8008-9cef-58c70ec59d18

https://chatgpt.com/share/6872c393-f61c-8008-bcda-6f64ba99e546


- working with json c++
https://chatgpt.com/share/6872c33f-5edc-8008-a68c-e8ab138fc88d


- map vs unordered_map c++
https://chatgpt.com/share/6872c371-8630-8008-b3af-f6d5b516cd3e



