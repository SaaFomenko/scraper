#include <gtest/gtest.h>
#include "../lib/Url/Url.h"
//#include <gmosk/gmosk.h>


namespace my
{
    const char* test_div = "\n----------------------------------\n";
    const char* url_test = "http://example.com";
    const char* root_test = "example.com";
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
        url = new Url(my::url_test);
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

TEST_F(UrlClassTest, to_root_test)
{
    std::string value = url->to_root();

    EXPECT_STREQ(value.c_str(), my::root_test);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}