python ./compile_tests.py ./tests
if [ $? -eq 0 ]; then
    FLAGS="-I . -Wall -Wpedantic -Wextra"
    CPP_FLAGS="$FLAGS -std=gnu++2b"

    clang -c ./c.c $FLAGS
    clang -c ./cb.c $FLAGS
    clang -c ./tests/c.c -o ./tests/c.c.o $FLAGS
    clang++ -c ./tests/cpp.cpp -o ./tests/cpp.cpp.o $CPP_FLAGS

    clang++ -c ./test.cpp $CPP_FLAGS
    clang++ -o ./test.out ./test.o ./c.o ./cb.o ./tests/c.c.o ./tests/cpp.cpp.o
fi