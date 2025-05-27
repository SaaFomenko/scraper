#ifdef DEB_REQ
#include <iostream>
#endif

#include <sys/stat.h>
#include <curl/curl.h>
#include "scraper.h"
#include "../Url/Url.h"

static const char* err_create_dir = "Fail, do not create dir!";

typedef size_t( * curl_write)(char * , size_t, size_t, std::string *);

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

Scraper::Scraper(const char* url) :
url(url)
{}

Scraper::~Scraper()
{}

std::string Scraper::request()
{
  CURLcode res_code = CURLE_FAILED_INIT;
  CURL * curl = curl_easy_init();
  std::string result;

  curl_global_init(CURL_GLOBAL_ALL);

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt (curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
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

void Scraper::get()
{
//    throw AppException("Scraper get function not realise.");

  // namespace fs = std::filesystem;
  std::string web_code = request();

#ifdef DEB_REQ
  std::cout << "String result >>>\n";
  std::cout << web_code << '\n';
  std::cout << "<<< End.\n";

  std::cout << url << " - be to parse." << '\n';
#endif

  Url url_start(url);

  const char* dir_start = url_start.get_host().c_str();
  struct stat sb;

  if(stat(dir_start, &sb) != 0)
  {
    if(mkdir(dir_start, 0777) != 0)
    {
      throw MyException(err_create_dir);
    }
  }
}