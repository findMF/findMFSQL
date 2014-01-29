
FIND_PACKAGE(FindMFBase)
if(FindMFBase_FOUND)
  message(STATUS "FindMF found" ${FindMFBase_INCLUDE_DIR})
  SET(inc ${inc} ${FindMFBase_INCLUDE_DIR})
else(FindMFBase_FOUND)
  message(STATUS " !!!!!!!!!!!!!!!! FindMFBase_FOUND !!!!!!!!!!!!!!!! ")
  return()
endif(FindMFBase_FOUND)

SET( inc ${inc} ${FindMFBase_INCLUDE_DIR} )

add_subdirectory(findmf)
