#include <gtest/gtest.h>
#include "../lib/Url/Url.h"
//#include <gmosk/gmosk.h>


namespace my
{
    const char* test_div = "\n----------------------------------\n";
    const char* url_test = "http://example.com:8080/home/test.html";
    const char* way_test = "example.com:8080/home/test.html";
    const char* host_test = "example.com";
    const std::string http_scheme = "http";
    const std::string https_scheme = "https";
}

template <class T>
void print_test(T val, const char* name)
{
    std::cout << my::test_div;
    std::cout << name << val;
    std::cout << my::test_div;
}

// TEST(UrlSingleTest, get_url)
// {
//     // Arange - source
//     Url url(my::test_url);

//     // Act
//     std::string value = url.get();

//     // Assert
//     EXPECT_STREQ(value.c_str(), my::test_url.c_str());
// }

struct UrlClassTest : public testing::Test
{
    Url *url;

    void SetUp()
    {
        try
        {
            url = new Url(my::url_test);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    void TearDown()
    {
        delete url;
    }
};

TEST_F(UrlClassTest, get_test)
{
    std::string value = url->get();

    EXPECT_STREQ(value.c_str(), my::url_test);
}

TEST_F(UrlClassTest, get_sheme_test)
{
    const std::string value = url->get_scheme();

    const char* test_scheme;    
    if(value == my::http_scheme)
    {
        test_scheme = my::http_scheme.c_str();
    }
    else
    {
        test_scheme = my::https_scheme.c_str(); 
    }

    EXPECT_STREQ(value.c_str(), test_scheme);
}

TEST_F(UrlClassTest, to_host_test)
{
    const char* value = url->get_way().c_str();

    EXPECT_STREQ(value, test_way);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}