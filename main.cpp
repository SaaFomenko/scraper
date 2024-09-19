#include <iostream>
#include <vector>
#include "lib/scraper/scraper.h"
#include "lib/my_file/my_file.h"


int main()
{
    const char* conf_path = "conf.txt";
    const char* request_url = "Enter url for parse (http://example.com): ";
    const char* new_domain = "Enter new doman for parse resurce or non (new_doman.com): ";
    const char* lable_url = "Parse url: ";
    const char* lable_new_doman = "New doman for parse data: ";
    const char* lable_conf_descript = "Data for parse to save current dir in conf.txt, delete this \
file for other purposes.";
    const char* not_found_url = "Not found url: ";
    const char* not_found_conf = "Not found conf.txt";
    const char* parse_susses = " - parse to current dir.";

    Scraper scraper;
    std::vector<std::string> conf_list;
    std::string str;

    try
    {
        MyFile conf_file(conf_path);
        conf_list = conf_file.to_words();

        std::cout << lable_url << conf_list.at(url) << '\n';
        std::cout << lable_new_doman << conf_list.at(new_url) << '\n';
        std::cout << lable_conf_descript << '\n';
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << not_found_conf << '\n';

        std::cout << request_url;
        std::cin >> str;
        conf_list.push_back(str);

        std::cout << new_domain;
        std::cin >> str;
        conf_list.push_back(str);

        str = conf_list.at(url) + ' ' + conf_list.at(new_url) + '\n';
        MyFile conf_file(conf_path, str);
    }

    try 
    {
        scraper.get(conf_list);
    }
    catch (std::exception& e)
    {
        std::cout << not_found_url << conf_list[url] << "\n";
        std::cout << e.what() << "\n";
        return 1;
    }

//    scraper = new Scraper();

//    std::cout << conf_list[url] << parse_susses << "\n";

    return 0;
}