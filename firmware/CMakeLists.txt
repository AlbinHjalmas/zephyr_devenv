
cmake_minimum_required(VERSION 3.20.0)
unset(CONF_FILE CACHE)

list(APPEND CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/prj.conf)
# list(APPEND DTC_OVERLAY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/application.overlay)

if(DEFINED TEST)
  list(APPEND CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/test.conf)
endif()

# !!! IMPORTANT !!! ###################################################################################################
# The find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE}) command, which is part of the Zephyr application 
# boilerplate code, essentially loads the Zephyr build system. When it's executed, it sets up various configuration 
# options, including CONF_FILE. If CONF_FILE is not stored in the cache before find_package is called, the value 
# will be overwritten with the Zephyr defaults.
# By using set(CONF_FILE ${CONF_FILE} CACHE INTERNAL "conf_file") before the find_package command, we're storing 
# the CONF_FILE configuration in the CMake cache. This ensures that the configuration is retained when find_package 
# is called.
set(CONF_FILE ${CONF_FILE} CACHE INTERNAL "conf_file")
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(sx1303)

# if(DEFINED TEST) # If we're building a test, we don't want to build the main application

#   if(${TEST} STREQUAL "network_transport_manager")
#       add_subdirectory(src/network_transport_manager/test)
#   else()
#       message(FATAL_ERROR "Unknown test: ${TEST}")
#   endif()

# else()

  # add_subdirectory(src/network_transport_manager)

  target_sources(app PRIVATE
    src/main.c
  )

# endif()

zephyr_library_include_directories(.)
