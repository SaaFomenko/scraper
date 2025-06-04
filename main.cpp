// #define DEB_MKDIR
#ifdef DEB_MKDIR
#include <iostream>
#endif

#include <gtest/gtest.h>
#include <vector>
#include "lib/scraper/scraper.h"
#include "lib/Url/Url.h"
#include "lib/my_file/my_file.h"
//#include <gmosk/gmosk.h>


namespace my
{
    const char* test_div = "\n----------------------------------\n";
    enum
    {
        start_url = 0,
        host,
        html_file
    };
    const char* conf_path = "conf.txt";
}

template <class T>
void print_test(T val, const char* name)
{
    std::cout << my::test_div;
    std::cout << name << val;
    std::cout << my::test_div;
}

struct ScraperClassTest : public testing::Test
{
    Scraper *scraper;
    MyFile *conf_file;
    MyFile *html_file;
    std::vector<std::string> conf_list;
    std::string path_file;
    const char* url;

    void SetUp()
    {
        try
        {
            conf_file = new MyFile(my::conf_path);
            conf_list = conf_file->to_words();
            path_file = conf_list.at(my::host) + conf_list.at(my::html_file);
            html_file = new MyFile(path_file.c_str());
            const char* url = conf_list.at(my::start_url).c_str();
            scraper = new Scraper(url);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    void TearDown()
    {
        delete scraper;
        delete conf_file;
        delete url;
    }
};

TEST_F(ScraperClassTest, get_test)
{
    try
    {
        scraper->get();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    struct stat sb;

#ifdef DEB_MKDIR
    std::cout << "!!! Test print url: " << conf_list.at(my::host) << '\n';
#endif

   
    EXPECT_EQ(stat(path_file.c_str(), &sb), 0);
}

TEST_F(ScraperClassTest, cmp_text)
{
    std::string html_code = scraper->request();
    std::string text = html_file->raw_str();

    bool isTextEQ = html_code == text;

    EXPECT_EQ(isTextEQ, true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}