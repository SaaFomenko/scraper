#include <iostream>
#include <curl/curl.h>
// #include "/opt/lib/curl/curl.h"
#include "scraper.h"


typedef size_t( * curl_write)(char * , size_t, size_t, std::string *);


Scraper::Scraper()
{}

Scraper::~Scraper()
{}

std::string Scraper::request(const std::string& url)
{
  CURLcode res_code = CURLE_FAILED_INIT;
  CURL * curl = curl_easy_init();
  std::string result;

  curl_global_init(CURL_GLOBAL_ALL);

  if (curl) {
    curl_easy_setopt(curl,
      CURLOPT_WRITEFUNCTION,
      static_cast < curl_write > ([](char * contents, size_t size,
        size_t nmemb, std::string * data) -> size_t {
        size_t new_size = size * nmemb;
        if (data == NULL) {
          return 0;
        }
        data -> append(contents, new_size);
        return new_size;
      }));
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, & result);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "simple scraper");

    res_code = curl_easy_perform(curl);

    if (res_code != CURLE_OK) {
      return curl_easy_strerror(res_code);
    }

    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return result;
}

void Scraper::get(const std::string& url)
{
//    throw MyException("Scraper get function not realise.");
    std::string web_code = request(url);

    std::cout << web_code << '\n';
}