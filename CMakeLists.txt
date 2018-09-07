cmake_minimum_required(VERSION 3.10.0)

project(log11-test)

set(src_SOURCES
	tlog.cpp)

set(inc_HEADERS
	log11.hpp)


add_executable(log11-test 
    ${src_SOURCES}
	${inc_HEADERS})
