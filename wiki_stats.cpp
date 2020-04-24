#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <map>
#include "wiki_graph.hpp"
#include "utf8.hpp"

using namespace std;

void width_search(const WikiGraph &wg, const string &from, const string &to);
void count_pages_with_redirect(const WikiGraph &wg);
int32_t min_count_links_from_page(const WikiGraph &wg);
void count_pages_with_min_links_from(const WikiGraph &wg, const int32_t &min);
int32_t max_count_links_from_page(const WikiGraph &wg);
void count_pages_with_max_links_from(const WikiGraph &wg, const int32_t &max);
void page_with_max_links(const WikiGraph &wg, const int32_t &max);
void average_links_in_page(const WikiGraph &wg);
int32_t min_count_links_on_page(const WikiGraph &wg);
void count_pages_with_min_links_on(const WikiGraph &wg, const int32_t &min);
int32_t max_count_links_on_page(const WikiGraph &wg);
void count_pages_with_max_links_on(const WikiGraph &wg, const int32_t &max);

int main(int argc, char* argv[]){
    if (argc != 2){
        cout << utf16_to_utf8(L"Использование: ./wiki <файл с графом статей>") << endl;
        return -1;
    }

    WikiGraph wg;
    ifstream file(argv[1]);
    if (file){
        cout << utf16_to_utf8(L"Загружаю граф из файла: ") << argv[1] << endl;;
        wg.load_from_stream(file);
        file.close();

        // ***********************************************************************
        // launch the tests

        width_search(wg, "Python", "Список_файловых_систем");
        count_pages_with_redirect(wg);
        int32_t min_links_from = min_count_links_from_page(wg);
        cout << utf16_to_utf8(L"Минимальное количество ссылок из статьи: ") << min_links_from << endl;
        count_pages_with_min_links_from(wg, min_links_from);
        int32_t max_links_from = max_count_links_from_page(wg);
        cout << utf16_to_utf8(L"Максимальное количество ссылок из статьи: ") << max_links_from << endl;
        count_pages_with_min_links_from(wg, max_links_from);
        page_with_max_links(wg, max_links_from);
        average_links_in_page(wg);
        int32_t min_links_on = min_count_links_on_page(wg);
        cout << utf16_to_utf8(L"Минимальное количество ссылок на статью: ") << min_links_on << endl;
        count_pages_with_min_links_on(wg, min_links_on);
        int32_t max_links_on = max_count_links_on_page(wg);

        //************************************************************************
    }
    else
    {
        cout << utf16_to_utf8(L"Файл с графом не найден") << endl;;
        return -1;
    }

    //FIXIT статистика, путь
}

void width_search(const WikiGraph &wg, const string &from, const string &to) {
    cout << utf16_to_utf8(L"Запускаем поиск в ширину") << endl;
}

void count_pages_with_redirect(const WikiGraph &wg) {
    int32_t count=0;
    for (int32_t i=1; i<=wg.get_number_of_pages(); i++) {
        if (wg.is_redirect(i)) {
            count++;
        }
    }
    double_t procent = count * 100. / wg.get_number_of_pages();
    cout << utf16_to_utf8(L"Количество статей с перенаправлением: ") << count
         << " (" << round(procent*100)/100 << "%)" << endl;
}

int32_t min_count_links_from_page(const WikiGraph &wg) {
    int32_t min_count = wg.get_number_of_pages();
    for (int32_t i=1; i<=wg.get_number_of_pages(); i++) {
        if (wg.get_number_of_links_from(i) < min_count) {
            min_count = wg.get_number_of_links_from(i);
        }
    }
    return min_count;
}

void count_pages_with_min_links_from(const WikiGraph &wg, const int32_t &min) {
    int32_t count=0;
    for (int32_t i=1; i<=wg.get_number_of_pages(); i++) {
        if (wg.get_number_of_links_from(i) == min) {
            count++;
        }
    }
    cout << utf16_to_utf8(L"Количество статей с минимальным количеством ссылок: ") << count << endl;
}

int32_t max_count_links_from_page(const WikiGraph &wg) {
    int32_t max_count = 0;
    for (int32_t i=1; i<=wg.get_number_of_pages(); i++) {
        if (wg.get_number_of_links_from(i) > max_count) {
            max_count = wg.get_number_of_links_from(i);
        }
    }
    return max_count;
}

void count_pages_with_max_links_from(const WikiGraph &wg, const int32_t &max) {
    int32_t count=0;
    for (int32_t i=1; i<=wg.get_number_of_pages(); i++) {
        if (wg.get_number_of_links_from(i) == max) {
            count++;
        }
    }
    cout << utf16_to_utf8(L"Количество статей с максимальным количеством ссылок: ") << count << endl;
}

void page_with_max_links(const WikiGraph &wg, const int32_t &max) {
    for (int32_t i=1; i<=wg.get_number_of_pages(); i++) {
        if (wg.get_number_of_links_from(i) == max) {
            cout << utf16_to_utf8(L"Статья с наибольшим количеством ссылок: ") << wg.get_title(i) << endl;
            break;
        }
    }
}

void average_links_in_page(const WikiGraph &wg) {
    int32_t count_links=0;
    for (int32_t i=1; i<=wg.get_number_of_pages(); i++) {
        count_links += wg.get_number_of_links_from(i);
    }
    double_t result = count_links * 1. / wg.get_number_of_pages();
    cout << utf16_to_utf8(L"Среднее количество ссылок в статье: ") << round(result*100)/100 << "%)" << endl;
}

int32_t min_count_links_on_page(const WikiGraph &wg) {
    map<int32_t, int32_t> count_on;
    for (int32_t i=1; i<=wg.get_number_of_pages(); i++) {
        for (int32_t j=0; j<wg.get_number_of_links_from(i); j++) {
            int32_t link = *(wg.get_links_from(i)+j);
            cout << link << endl;
            if (count_on.find(link) != count_on.end()) {
                count_on[link]++;
            } else {
                count_on[link] = 1;
            }
        }
    }
    int32_t min = wg.get_number_of_pages();
    for (map<int32_t, int32_t>::iterator it=count_on.begin(); it!=count_on.end(); ++it) {
        if (it->second < min) {
            min = it->second;
        }
    }
    return min;
}

void count_pages_with_min_links_on(const WikiGraph &wg, const int32_t &min) {
    map<int32_t, int32_t> count_on;
    for (int32_t i=1; i<=wg.get_number_of_pages(); i++) {
        for (int32_t j=0; j<wg.get_number_of_links_from(i); j++) {
            int32_t link = *(wg.get_links_from(i)+j);
            if (count_on.find(link) != count_on.end()) {
                count_on[link]++;
            } else {
                count_on[link] = 1;
            }
        }
    }
    int32_t count_min = 0;
    for (map<int32_t, int32_t>::iterator it=count_on.begin(); it!=count_on.end(); ++it) {
        if (it->second == min) {
            count_min++;
        }
    }
    cout << utf16_to_utf8(L"Количество статей с минимальным количеством внешних ссылок: ") << count_min << endl;
}

int32_t max_count_links_on_page(const WikiGraph &wg) {
    return 0;
}

void count_pages_with_max_links_on(const WikiGraph &wg, const int32_t &max) {

}
