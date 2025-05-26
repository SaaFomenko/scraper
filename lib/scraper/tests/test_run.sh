#!/bin/bash

g++ main.cpp ../scraper.cpp -o test -lgtest -pthread && ./test