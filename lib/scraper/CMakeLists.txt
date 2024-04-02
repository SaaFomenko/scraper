cmake_minimum_required(VERSION 3.18)

project(scraper)

file(GLOB
	public_headers "*.h"
	sources "*.cpp")

add_library(${PROJECT_NAME}_lib ${sources} ${public_headers})
