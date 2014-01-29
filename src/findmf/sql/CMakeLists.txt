SET(datastruct_SOURCES parsesql.cpp)

include_directories(${inc})
add_library(utilslib parsesql.cpp)
