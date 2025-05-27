#!/bin/bash

g++ main.cpp ../scraper.cpp ../../Url/Url.cpp ../../my_file/my_file.cpp -o test -lgtest -pthread && ./test