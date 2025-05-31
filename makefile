# Makefile

# Компилятор и флаги
CXX := g++
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra

# Пути
INCDIR := lab_work           
CLISEL := lab_work/cli.cpp   
TESTSRC := tests/test.cpp    

# Имена итоговых бинарников
CLI_BIN := cli
TEST_BIN := test

.PHONY: all clean

all: $(CLI_BIN) $(TEST_BIN)

# 1) Собираем cli
$(CLI_BIN): $(CLISEL)
	$(CXX) $(CXXFLAGS) -I $(INCDIR) $< -o $@

# 2) Собираем тесты
$(TEST_BIN): $(TESTSRC)
	$(CXX) $(CXXFLAGS) -I $(INCDIR) $< -o $@

clean:
	rm -f $(CLI_BIN) $(TEST_BIN)
