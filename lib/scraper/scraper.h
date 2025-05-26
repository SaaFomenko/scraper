#ifndef SCRAPER_H 
#define SCRAPER_H

#include <string>
#include <vector>


enum 
{
    url = 0,
    new_url,
};

class Scraper
{
	public:
		Scraper();
		virtual ~Scraper();

		void get(std::vector<std::string>& conf_list);
		std::string request(const std::string& url);
		// void save(std::string& str, std::string path);
};

#endif