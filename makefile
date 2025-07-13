CC = g++ --std=c++17

#flags
CFLAGS = -Werror -Wall -Wextra -g -I.

.PHONY: all clean

all:./test_log_parsing/test.out ./test_config_loading/test.out ./test_final/test.out \
./test_lines_not_valid/test.out ./test_N+1_same_recurring/test.out ./test_error_grouping/test.out

log_analyzer.o: log_analyzer.cpp log_analyzer.hpp
	$(CC) $(CFLAGS) $< -c -o $@

./test_log_parsing/test.out: log_analyzer.o test_log_parsing/test_log_parsing.cpp
	$(CC) $(CFLAGS) $^ -o $@

./test_config_loading/test.out: log_analyzer.o test_config_loading/test_config_loading.cpp
	$(CC) $(CFLAGS) $^ -o $@

./test_error_grouping/test.out: log_analyzer.o test_error_grouping/test_error_grouping.cpp
	$(CC) $(CFLAGS) $^ -o $@

./test_final/test.out: log_analyzer.o test_final/test_final.cpp
	$(CC) $(CFLAGS) $^ -o $@

./test_lines_not_valid/test.out: log_analyzer.o test_lines_not_valid/test_lines_not_valid.cpp
	$(CC) $(CFLAGS) $^ -o $@

./test_N+1_same_recurring/test.out: log_analyzer.o test_N+1_same_recurring/test_N+1_same_recurring.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) ./test_log_parsing/test.out ./test_config_loading/test.out ./test_final/test.out \
./test_lines_not_valid/test.out ./test_N+1_same_recurring/test.out ./test_error_grouping/test.out *.o