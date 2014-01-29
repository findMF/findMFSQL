include_directories(${inc})
link_directories()


ADD_EXECUTABLE(etl4example1 etl4example1.cpp)
TARGET_LINK_LIBRARIES(etl4example1 odbc )
