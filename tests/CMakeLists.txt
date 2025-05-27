cmake_minimum_required(VERSION 3.5)

project(test_scraper)

# set the C++ standard
set(CMAKE_CXX_STANDARD 11)


set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# set libcurl
find_package(CURL REQUIRED) 

add_subdirectory(lib)

add_executable(${PROJECT_NAME}.exe main.cpp)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}.exe 
					# ${CURL_LIBRARIES}
					CURL::libcurl
					gtest
					pthread
					scraper_lib 
					my_file_lib
					Url_lib)
