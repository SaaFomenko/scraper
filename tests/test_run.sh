#!/bin/bash

g++ main.cpp ../lib/Url/Url.cpp -o test -lgtest -pthread && ./test