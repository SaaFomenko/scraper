#ifndef SCRAPER_H 
#define SCRAPER_H

#include <string>
#include <exception>


class MyException : public std::exception
{
	private:
	const char* msg;

	public:
		MyException(const char* msg_) : msg(msg_){}
		virtual ~MyException(){}

		const char* what() const noexcept override
		{
			return msg;
		}
};

class Scraper
{
	public:
		Scraper();
		virtual ~Scraper();

		void get(const std::string& url);
		std::string request(const std::string& url);
};

#endif
