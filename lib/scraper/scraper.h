#ifndef SCRAPER_H 
#define SCRAPER_H

#include <string>


class Scraper
{
	public:
		Scraper();
		virtual ~Scraper();

		void get(const std::string& url);
};

#endif
