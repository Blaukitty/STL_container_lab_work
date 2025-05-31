# STL_container_lab_work

Сборка осуществляется через Makefile, в терминале вводится команда " make ".
Появятся 2 файла: <папка проекта>/cli
                  <папка проекта>/test
                  
Запуск cli (файла с main): ./cli
Результат: числа.

Тесты: ./test
Результат: [==========] Running 6 tests from 4 test suites.
           [ RUN      ] Basic.IfEmpty
           [       OK ] Basic.IfEmpty (0 ms)

Для запуска необходимо иметь: g++

Для тестов : libgtest-dev
             cmake
             make
