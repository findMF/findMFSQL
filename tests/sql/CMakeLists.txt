# Copyright : ETH Zurich
# License   : three-clause BSD license
# Authors   : Witold Wolski
# for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

include_directories(${inc})

message(STATUS ">>>>>>> ${Boost_LIBRARIES} >>>>")

ADD_EXECUTABLE(sqlsocitest sqlsocitest.cpp )
TARGET_LINK_LIBRARIES(sqlsocitest ${Boost_LIBRARIES} ${QT_LIBRARIES} utilslib)

ENABLE_TESTING()

add_test(NAME sqlsocitest
WORKING_DIRECTORY ${BinOut}
COMMAND ${BinOut}/sqlsocitest )
set_tests_properties(sqlsocitest PROPERTIES ENVIRONMENT "${LD_VARNAME}=${LD_PATH}")


