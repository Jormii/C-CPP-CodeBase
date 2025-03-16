import os
import re
import sys
from typing import Dict, List


# About C/C++ testing:
#   - The programs looks for *.c and *.cpp files inside {DIR} directory above
#   - Then it looks for functions with the signature 'int32_t a_function_test()'
#       - They must end with the '_test 'suffix
#       - They return 0 on failure and 1 on success (use ASSERTZ)
#       - They may return i32 instead and (void) argument is optional
#   - Tests are compiled into a 'tests.cpp' file. It defines three functions left for implementation:
#       - void testing_started_cb(void)
#       - void test_file_cb(const char *file)
#       - i32 test_function_cb(i32 (*f)(void), const char *fname): Must return 1 if f() returns 1, else 0
#       - void testing_finished_cb(i32 passed, i32 failed)


END_ESC = "\033[0m"
BOLD_ESC = "\033[1m"
ERROR_ESC = f"{BOLD_ESC}\033[91m"
WARNING_ESC = f"{BOLD_ESC}\033[93m"


def main() -> int:
    argv = sys.argv
    if len(argv) < 2:
        print(f'usage: {os.path.basename(__file__)} <dirs...>')
        return 1

    all_exist = True
    dirs: List[str] = []
    for i in range(1, len(argv)):
        dir = argv[i]
        assert isinstance(dir, str)

        if dir not in dirs:
            dirs.append(dir)
        
        if not os.path.isdir(dir):
            all_exist = False
            print(f"{WARNING_ESC}!{END_ESC} {dir}: Does not exist")

    if not all_exist:
        return 1

    signatures: Dict[str, List[str]] = {}
    for dir in dirs:
        files = get_source_files(dir)
        file_signatures = get_signatures(files)

        signatures.update(file_signatures)

    compiled_file = generate_file(signatures, os.getcwd())
    print(f"\nTests main saved to {compiled_file}")
    
    return 0

def get_source_files(dir: str) -> List[str]:
    dirs = [dir]
    files: List[str] = []
    while len(dirs) != 0:
        dir = dirs.pop(0)
        for filename in os.listdir(dir):
            path = os.path.join(dir, filename)

            if os.path.isdir(path):
                dirs.append(dir)
            elif os.path.isfile(path):
                _, ext = os.path.splitext(path)
                if ext in [".c", ".cpp"]:
                    files.append(path)

    return files


def get_signatures(files: List[str]) -> Dict[str, List[str]]:
    TYPO_REGEX = r"(?:int32_t|i32) ([_a-zA-Z][_a-zA-Z0-9]*)\((?:void)?\)"
    REGEX =      r"(?:int32_t|i32) ([_a-zA-Z][_a-zA-Z0-9]*_test)\((?:void)?\)"

    defined_in: Dict[str, str] = {}
    collisions: Dict[str, List[str]] = {}
    signatures: Dict[str, List[str]] = {}

    for file in files:
        with open(file, "r") as fd:
            lines = fd.readlines()

        signatures[file] = []
        for line in map(lambda ln: ln.strip(), lines):
            search = re.search(REGEX, line)
            if search is None:
                search = re.search(TYPO_REGEX, line)
                if search is None:
                    continue
                else:
                    print(f"{WARNING_ESC}!{END_ESC} {file}: {line}")

            signature = search.group(1)
            signatures[file].append(signature)

            if signature not in defined_in:
                defined_in[signature] = file
            else:
                if signature not in collisions:
                    collisions[signature] = [file]
                else:
                    collisions[signature].append(file)

        if len(signatures[file]) != 0:
            print(f"{file}: {len(signatures[file])} test(s)")
        else:
            print(f"{WARNING_ESC}!{END_ESC} {file}: No tests")

    if len(signatures) == 0:
        print(f"{WARNING_ESC}!{END_ESC} No tests found")

    if len(collisions) != 0:
        INDENT = 2 * " "

        print("{ERROR_ESC}X{END_ESC} Signature collisions found")

        for signature, collision_files in collisions.items():
            print(f"{INDENT}- {signature}")
            for file in collision_files:
                print(f"{2*INDENT}- {file}")

        exit(1)

    return signatures


def generate_file(signatures: Dict[str, List[str]], save_dir: str) -> str:
    FILENAME = "test.cpp"

    n_tests = 0
    for file_signatures in signatures.values():
        n_tests += len(file_signatures)

    tests_file = os.path.join(save_dir, FILENAME)
    with open(tests_file, "w") as fd:
        fd.write("#include <stdint.h>\n")

        fd.write("\ntypedef int32_t i32;\n")

        fd.write("\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n")
        fd.write("extern void testing_started_cb(void);\n")
        fd.write("extern void test_file_cb(const char *file);\n")
        fd.write("extern i32 test_function_cb(i32 (*f)(void), const char *fname);\n")
        fd.write("extern void testing_finished_cb(i32 passed, i32 failed);\n")
        fd.write("#ifdef __cplusplus\n}\n#endif\n")

        for file, file_signatures in signatures.items():
            _, ext = os.path.splitext(file)

            fd.write(f"\n// From {file}\n")
            if ext == ".c":
                fd.write("#ifdef __cplusplus\nextern \"C\" {\n#endif\n")
            for signature in file_signatures:
                fd.write(f"extern i32 {signature}(void);\n")
            if ext == ".c":
                fd.write("#ifdef __cplusplus\n}\n#endif\n")

        fd.write("\nint main(void) {\n")
        fd.write("\ti32 passed = 0;\n")
        fd.write(f"\tconst i32 N_TESTS = {n_tests};\n")

        fd.write("\n\ttesting_started_cb();\n")

        for file, file_signatures in signatures.items():
            fd.write(f'\n\ttest_file_cb("{file}");\n')
            for signature in file_signatures:
                fd.write(f'\tpassed += test_function_cb({signature}, "{signature}");\n')

        fd.write("\n\ttesting_finished_cb(passed, N_TESTS - passed);\n")

        fd.write("\n\treturn (passed == N_TESTS) ? 0 : 1;\n")
        fd.write("}\n")

    return tests_file


if __name__ == "__main__":
    sys.exit(main())
