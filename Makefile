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

# cli
$(CLI_BIN): $(CLISEL)
	$(CXX) $(CXXFLAGS) -I $(INCDIR) $< -o $@

# тесты
$(TEST_BIN): $(TESTSRC)
	$(CXX) $(CXXFLAGS) -I $(INCDIR) \
		$< -o $@ \
		-lgtest -lgtest_main -pthread

clean:
	rm -f $(CLI_BIN) $(TEST_BIN)
