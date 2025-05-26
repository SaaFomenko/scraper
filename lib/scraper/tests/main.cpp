#include <gtest/gtest.h>
#include "../scraper.h"
#include "../../Url/Url.h"
//#include <gmosk/gmosk.h>


namespace my
{
    const char* test_div = "\n----------------------------------\n";
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

    void SetUp()
    {
        // try
        // {
            scraper = new Scraper();
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        
    }
    void TearDown()
    {
        delete scraper;
    }
};

TEST_F(ScraperClassTest, get_test)
{
    try
    {
        scraper->get(my::url_test);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
   

    EXPECT_STREQ(value.c_str(), my::url_test);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}