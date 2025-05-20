#include <gtest/gtest.h>
#include "../lib/Url/Url.h"
//#include <gmosk/gmosk.h>


namespace my
{
    const char* test_div = "\n----------------------------------\n";
    std::string test_url = "http://example.com"; 
}

template <class T>
void print_test(T val, const char* name)
{
    std::cout << my::test_div;
    std::cout << name << val;
    std::cout << my::test_div;
}

TEST(UrlGroupTest, get_url)
{
    // Arange - source
    Url url(my::test_url);

    // Act
    std::string value = url.get();

    // Assert
    EXPECT_STREQ(value.c_str(), my::test_url.c_str());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}