#ifndef SCRAPER_H 
#define SCRAPER_H

#include <string>
#include <vector>


class Scraper
{
	private:
		std::string url;
	public:
		Scraper(const char* path);
		virtual ~Scraper();

		void get();
		std::string request();
		// void save(std::string& str, std::string path);
};

#endif