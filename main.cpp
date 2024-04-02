#include <iostream>
#include "lib/scraper/scraper.h"

int main()
{
    const std::string quest = "Enter url for parse (http://examlle.com): ";
    const std::string not_found_url = "Not found url: ";
    const std::string parse_susses = " - parse to current dir.";

    Scraper scraper;
    std::string url;

    std::cout << quest;
    std::cin >> url;

    try 
    {
        scraper.get(url);
    }
    catch (std::exception& e)
    {
        std::cout << not_found_url << url << "/n";
        std::cout << e.what() << "/n";
        return 1;
    }

//    scraper = new Scraper();

    std::cout << url << parse_susses << "/n";

    return 0;
}