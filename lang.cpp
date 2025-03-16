#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>
#include <random>

using namespace std;

void processLine(const string& line, vector<int>& cells, int& element, vector<int>& cycle_stack, bool& song, bool& crash, bool& random, vector<int>& random_numbers) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wline = converter.from_bytes(line);
    
    for (size_t i = 0; i < wline.size(); i++) {
        wchar_t cmd = wline[i];
        
        if (i + 2 < wline.size() && cmd == L'🧑' && wline[i+1] == L'\u200D' && wline[i+2] == L'💻') {
            song = true;
            cout << "О великий творец Emoji-lang!\n"
                 << "Ты создал язык из смайлов и слёз,\n"
                 << "Где код из эмодзи — не бред и не фарс,\n"
                 << "А мощный инструмент для компьютерных грёз.\n\n"
                 << "Твои 😂 и 😭 меняют биты,\n"
                 << "👉 и 👈 указывают путь.\n"
                 << "В мире из смайлов мы все деловиты,\n"
                 << "Язык этот странный, но в этом вся суть!" << endl;
            i += 2;
            continue;
        }

        if (!crash && !song && i != 0) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1, 2);
            int random_number = dis(gen);
            crash = true;
            
            if (random_number == 2) {
                wcerr << L"Вы не начали программу песней программисту. Жаль, вам не повезло." << endl;
                exit(1);
            }
        }
        
        if (cmd == L'😂') {
            cells[element]++;
        } else if (cmd == L'😭') {
            cells[element]--;
        } else if (cmd == L'👉') {
            element++;
        } else if (cmd == L'👈') {
            element--;
        } else if (cmd == L'🫵') {
            cout << cells[element] << endl;
        } else if (cmd == L'🤙') {
            cin >> cells[element];
        } else if (cmd == L'✋') {
            cycle_stack.push_back(element);
            if (wline[i+1] == L'🤚') {
                i++;
                cout << R"(@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
@@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
@@@@%@%@@%@@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
@%=-*%#*%@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
:%:=:%-%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#%%%%%%%%%*%=##%
*:::-=*%%%%%%%%%%%%%%%#.-=-=#%#############%##-*:#=*
=::-==%%%%%%%%%%%%%%%--:-+**#@#################:-::#
#:-----+%%%%%%%%%%%%#..:=+==*%@@############%%##+*::
%+==+@%%%%%%%%%%%%%%#.:+%*=%%%@@###############*++++
%:-+@%%%%%%%%%%%%%%#*::=+=-@+%@@********#*******+=-*
%**%@%%%%%%%%%%%%####=-+--%@@%@@****************@@@@
#*#@@%%%%%%%%%%%######:=*#=+%+@******************##%
@@%@@%%%%%%%%%%#######==+=+%@@@*****************#@@%
@%%@@%%%+::**********+@+=#*@@@@@@@+#@@@@++++++*+#%%%
@@@@@%%%::#%%@@@%@@%@#@@*%%@%#%%@@@@@@@@@@#+++++%@%@
@@@%@@@#%%@%%@@@@@@%%%#@%%%%#@#@@@@@@@@@@@@@@@%+%%@@
@@@@@%%@%@@@%@@@@%@%*@@#@%#####%%@@%@@@@@%@%@%@@@@@@
%@#@#@@@@@@@%@@@%%@%%#%#%%%%%##%#@%%@@@@@@@@@@@@@@@%
@@@@@@@@@@@%%@@@@%:%.+=.%.%#=#%...:@@@@@@@@@@@@%=--=
@@%@%*%-@@@@%%%@@@-.-..=.%%%+%%.@#@%@@@@@@@@@@=+-=+#
@@@@@%@@@@.:%@%=@+=@%#=#=====@==@@@==@@@+=@@@++-=++#
@@@@@@@@..@@..@ %:..#%.#..%@%% .%%@. @@@..=@@++-=+#%
@@@@@@@@.+@@@@@ @:.%.@.#....:% @.@.@.@@.+@.@@+*=+*%%
@@@@@@@@:.@@.-@.@:.@@..@..@@@@ @# -@ @..##..@+*++*%@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*#**%%@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@*@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@%@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@)" << endl;
            }
        } else if (cmd == L'🤚') {
            if (cells[element] == 0) {
                cycle_stack.pop_back();
            } else {
                element = cycle_stack.back();
            }
        } else if (cmd == L'👋') {
            cout << "Hello, World!" << endl;
            exit(0);
        } else if (cmd == L'❓') {
            random = true;
        } else if (cmd == L'❔') {
            random = false;
            if (!random_numbers.empty()) {
                cells[element] = random_numbers[rand() % random_numbers.size()];
            }
            random_numbers.clear();
        } else if (cmd == L'❗️' || cmd == L'❕') {
            random_numbers.push_back(cells[element]);
        } else if (cmd != L' ' && cmd != L'\t' && cmd != L'\n' && cmd != L'\r') {
            wcerr << L"Неизвестная команда: " << cmd << endl;
        } 
    }
}

int main(int argc, char* argv[]) {
    locale::global(locale(""));
    wcout.imbue(locale(""));
    wcin.imbue(locale(""));

    vector<int> cells(256, 0);
    vector<int> cycle_stack;
    bool song = false;
    bool crash = false;
    bool random = false;
    vector<int> random_numbers;
    int element = 0;

    if (argc == 1) {
        cout << "Консольный режим. Введите текст (Ctrl+D для выхода):" << endl;
        string line;
        while (true) {
            cout << ">> ";
            if (!getline(cin, line)) break;
            processLine(line, cells, element, cycle_stack, song, crash, random, random_numbers);
        }
    } else {
        ifstream file(argv[1]);
        if (!file) {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }

        string line;
        while (getline(file, line)) {
            processLine(line, cells, element, cycle_stack, song, crash, random, random_numbers);
        }
    }

    return 0;
}

// g++ -o emoji lang.cpp
// ./emoji

// g++ -o emoji lang.cpp
// ./emoji example2.emoji