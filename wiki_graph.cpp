#include "wiki_graph.hpp"

WikiGraph::~WikiGraph() {
    if (n_links > 0) {
        delete[] titles;
        delete[] sizes;
        delete[] links;
        delete[] redirect;
        delete[] offset;
    }
}

void  WikiGraph::load_from_stream(std::istream &file) {

    n_pages = n_links = 0; //FIXIT: прочитать из файла

    file >> n_pages >> n_links;

    titles = new std::string [n_pages];
    sizes = new int32_t [n_pages];
    links = new int32_t [n_links];
    redirect = new bool [n_pages];
    offset = new int32_t [n_pages + 1];

    offset[0] = 0;
    int32_t i = 0;
    int32_t link_id = 0;
    while (i<n_pages) {
        file >> titles[i];
        int32_t count_links = 0;
        file >> sizes[i] >> redirect[i] >> count_links;
        for (int32_t j=0; j<count_links; j++) {
            file >> links[link_id];
            link_id++;
        }
        i++;
        offset[i] += offset[i-1] + count_links;
    }

    //FIXIT прочитать граф из файла

    std::cout << utf16_to_utf8(L"Граф загружен") << std::endl;
}

int32_t  WikiGraph::get_number_of_links_from(const int32_t &id) {
    return offset[id] - offset[id-1];
}

int32_t*  WikiGraph::get_links_from(const int32_t &id) {
    return links+id;
}

int32_t  WikiGraph::get_id(const std::string &title) {
    index = 0;
    while (index < n_pages) {
        if (titles[index] == title) {
            return index;
        }
        index++;
    }
    return -1;
}

int32_t  WikiGraph::get_number_of_pages() {
    return n_pages;
}

bool  WikiGraph::is_redirect(const int32_t &id) {
    return redirect[id-1];
}

std::string  WikiGraph::get_title(const int32_t &id) {
    return titles[id-1];
}

int32_t  WikiGraph::get_page_size(const int32_t &id) {
    return sizes[id-1];
}
