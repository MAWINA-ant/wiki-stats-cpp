#include <iostream>
#include <fstream>
#include <string>
#include "utf8.hpp"


class WikiGraph {
private:
    std::string * titles;
    int32_t *sizes, *links, *offset, n_links, n_pages;
    bool * redirect;

public:
    WikiGraph () {n_links = 0; n_pages= 0;}
    ~WikiGraph();

    void load_from_stream(std::istream&);
    int32_t get_number_of_links_from(const int32_t &);
    int32_t* get_links_from(const int32_t &);
    int32_t get_id(const std::string &);
    int32_t get_number_of_pages();
    bool is_redirect(const int32_t &);
    std::string get_title(const int32_t &);
    int32_t get_page_size(const int32_t &);
};
