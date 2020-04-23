#include <iostream>
#include <fstream>
#include <string>
#include "wiki_graph.hpp"
#include "utf8.hpp"


int main(int argc, char* argv[]){
    if (argc != 2){
        std::cout << utf16_to_utf8(L"Использование: ./wiki <файл с графом статей>") << std::endl;
        return -1;
    }

    WikiGraph wg;
    std::ifstream file(argv[1]);
    if (file){
        std::cout << utf16_to_utf8(L"Загружаю граф из файла: ") << argv[1] << std::endl;;
        wg.load_from_stream(file);
        file.close();

        // exercise 3
        // *

        // *
        std::cout << utf16_to_utf8(L"Количество статей с перенаправлением: ");
        // *
    }
    else
    {
        std::cout << utf16_to_utf8(L"Файл с графом не найден") << std::endl;;
        return -1;
    }

    //FIXIT статистика, путь
}

