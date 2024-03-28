# Instructions
## Makefile targets
- `rebuild`: перекомпилировать программу
- `clang`: применить форматирование google для файлов с расширением .c, .h
- `clang_review`: проверить форматирование google для файлов с расширением .c, .h
- `clean`: удаление объектных и исполняемого файлов

## Build
- Перейдите в папку cat или grep
- Вызовите команду `make`

## Check tests
- cat:
  - Перейдите в папку cat
  - Вызовите команду `sh test_cat.sh`(только если сделали build)
- grep:
  - Перейдите в папку grep
  - Вызовите команду `sh functional_test_s21_grep.sh`(только если сделали build)

## Run
- Для запуска программы используйте следующие шаблоны ввода:
- cat:
  - "usage: ./s21_cat [-benstuv] [file ...]"
- grep:
  - "usage: ./s21_grep [-ivclnhso] [-e pattern] [-f file] [pattern] [file ...]"
