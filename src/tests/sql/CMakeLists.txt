# Copyright : ETH Zurich
# License   : three-clause BSD license
# Authors   : Witold Wolski
# for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

include_directories(${inc})

message(STATUS ">>>>>>> ${Boost_LIBRARIES} >>>>")

ADD_EXECUTABLE(samplewriteTest samplewriteTest.cpp )
TARGET_LINK_LIBRARIES(samplewriteTest ${Boost_LIBRARIES} ${QT_LIBRARIES} utilslib)


#ADD_EXECUTABLE(writeMapInfoTest writeMapInfoTest.cpp )
#TARGET_LINK_LIBRARIES(writeMapInfoTest ${Boost_LIBRARIES} ${QT_LIBRARIES} utilslib)

ENABLE_TESTING()

add_test(NAME samplewriteTest
WORKING_DIRECTORY ${BinOut}
COMMAND ${BinOut}/samplewriteTest )
set_tests_properties(samplewriteTest PROPERTIES ENVIRONMENT "${LD_VARNAME}=${LD_PATH}")


#add_test(NAME writeMapInfoTest
#WORKING_DIRECTORY ${BinOut}
#COMMAND ${BinOut}/writeMapInfoTest )
#set_tests_properties(writeMapInfoTest PROPERTIES ENVIRONMENT "${LD_VARNAME}=${LD_PATH}")


