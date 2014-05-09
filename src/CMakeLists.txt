
FIND_PACKAGE(FindMFInterfaces)
if(FindMFInterfaces_FOUND)
  message(STATUS "FindMF found" ${FindMFInterfaces_INCLUDE_DIR})
  SET(inc ${inc} ${FindMFInterfaces_INCLUDE_DIR})
else(FindMFInterfaces_FOUND)
  message(STATUS " !!!!!!!!!!!!!!!! FindMFInterfaces_FOUND !!!!!!!!!!!!!!!! ")
  return()
endif(FindMFInterfaces_FOUND)
SET( inc ${inc} ${FindMFInterfaces_INCLUDE_DIR} )



FIND_PACKAGE(FindMFBase REQUIRED)
if(FindMFBase_FOUND)
  message(STATUS "FindMF found" ${FindMFBase_INCLUDE_DIR})
  SET(inc ${inc} ${FindMFBase_INCLUDE_DIR})
else(FindMFBase_FOUND)
  message(FATAL_ERROR " !!!!!!!!!!!!!!!! FindMFBase !!!!!!!!!!!!!!!! ")
  return()
endif(FindMFBase_FOUND)
SET( inc ${inc} ${FindMFBase_INCLUDE_DIR} )



add_subdirectory(findmf)
add_subdirecotry(test)
