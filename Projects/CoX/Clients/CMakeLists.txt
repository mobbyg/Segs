# Client_I0 should be compiled separately, since it has to be 32bit
# add_subdirectory(Client_I0)
if(WIN32)
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    add_subdirectory(Client_I0)
else()
    MESSAGE("Client_I0 should be compiled separately, since it has to be 32bit, and Your build is 64bit")
endif()
endif()
