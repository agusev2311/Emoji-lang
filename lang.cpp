#include <iostream>
#include <fstream>
#include <string>

void processLine(const std::string& line) {
    std::cout << ">> " << line << std::endl;
}

int main(int argc, char* argv[]) {
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));
    std::wcin.imbue(std::locale(""));

    if (argc == 1) {
        std::cout << "Консольный режим. Введите текст (Ctrl+D для выхода):" << std::endl;
        std::string line;
        while (std::getline(std::cin, line)) {
            processLine(line);
        }
    } else {
        std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "Ошибка: не удалось открыть файл " << argv[1] << std::endl;
            return 1;
        }

        std::string line;
        while (std::getline(file, line)) {
            processLine(line);
        }
    }

    return 0;
}
