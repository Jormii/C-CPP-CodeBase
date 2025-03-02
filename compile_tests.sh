python ./compile_tests.py
if [ $? -eq 0 ]; then
    FLAGS="-I . -Wall -Wpedantic -Wextra"
    CPP_FLAGS="$FLAGS -std=gnu++2b"

    clang -c ./cb.c $FLAGS
    clang -c ./tests/test.c -o ./tests/test.c.o $FLAGS
    clang++ -c ./tests/test.cpp -o ./tests/test.cpp.o $CPP_FLAGS

    clang++ -c test.cpp $CPP_FLAGS
    clang++ -o test ./test.o ./cb.o ./tests/test.c.o ./tests/test.cpp.o
fi