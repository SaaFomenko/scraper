// #define DEB_MKDIR
//#ifdef DEB_MKDIR
//#define DEB_REQ
//#ifdef DEB_REQ
//#define DEB_INDEX
#ifdef DEB_INDEX
#include <iostream>
#endif

#include <curl/curl.h>
#include "scraper.h"
#include "../Url/Url.h"
#include "../my_file/my_file.h"

static const char* err_create_dir = "Fail, do not create dir!";
static const char* warn_create_file = " - this file allready exist.";
static const char* html_file = "/index.html";

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

#ifdef DEB_MKDIR
  if(stat(dir_start, &sb) == 0)
  {
    std::cout << "!!! Directory: " << dir_start << " - exist.\n";
  }
  else
  {
    std::cout << "!!! Directory: " << dir_start << " - do not exist.\n";
  }
#endif

  if(stat(dir_start, &sb) != 0)
  {
    if(mkdir(dir_start, 0777) != 0)
    {
      throw MyException(err_create_dir);
    }
  }

  std::string file_path = dir_start;
  file_path += html_file;

  MyFile file(file_path.c_str());

  if(file.exist())
  {

#ifdef DEB_INDEX
    std::cout << "!!! File: " << file_path << " - exist.\n";
#endif 
    std::string html_file = file.raw_str();
    bool code_eq = html_file == web_code; 
    if(!code_eq) file.set_str(web_code.c_str());

  }
  else
  {

#ifdef DEB_INDEX
    std::cout << "!!! Create file: " << file_path << '\n';
    std::cout << "!!! Set this text: " << web_code << '\n';
#endif

    file.set_str(web_code.c_str());
  }

}