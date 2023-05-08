
###########
# Library #
###########


# Options
option(TESTS Enable tests OFF)


cmake_minimum_required(VERSION 3.26.0)
set (CMAKE_CXX_STANDARD 17)

# Setting library name
set(LIBRARY_NAME
    boollatex_parser
)

# Setting main environment variables
set(MAIN_LIBRARIES_DIR
    libs
)
set(MAIN_LIBRARIES 

)

set(LIBRARY_HEADERS_DIR
    include/${LIBRARY_NAME}
)
set(LIBRARY_HEADERS
    ${LIBRARY_HEADERS_DIR}/boollatex_parser.hpp
)
set(LIBRARY_SOURCE_DIR
    src
)
set(LIBRARY_SOURCE
    ${LIBRARY_SOURCE_DIR}/boollatex_parser.cpp
)



# Created project
project(${LIBRARY_NAME})





if (TARGET ${LIBRARY_NAME})
  # Do something when target found
else()
add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_HEADERS}
    ${LIBRARY_SOURCE}
)
endif()


################
# Dependencies #
################

# Git submodules
message("")
message("Finding and downloading submodules for library `${LIBRARY_NAME}`")
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS ${PROJECT_SOURCE_DIR}/.git)
	# Update submodules as needed
	option(GIT_SUBMODULE "Check submodules during build" ON)
	if (GIT_SUBMODULE)
		message(STATUS "Submodules updating")
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		    RESULT_VARIABLE GIT_SUBMOD_RESULT)
		if(NOT GIT_SUBMOD_RESULT EQUAL "0")
			message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
		endif()
	endif()
endif()
  

foreach(LIBRARY ${MAIN_LIBRARIES})
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/${LIBRARY}/CMakeLists.txt")
	message(FATAL_ERROR "The ${LIBRARY} submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
else()
    message (STATUS "Submodule ${LIBRARY} was downloaded and has been found.")
endif()
message("")
endforeach(LIBRARY)



# Addinng all libraries in libs/
foreach(LIBRARY ${MAIN_LIBRARIES})
    add_subdirectory(${MAIN_LIBRARIES_DIR}/${LIBRARY})
endforeach(LIBRARY)

# Linking libraries/dependencies
target_link_libraries(${LIBRARY_NAME} ${MAIN_LIBRARIES})


# adding include/ directories
target_include_directories(${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
)

# adding more include/ directories
target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Sets public header files for target
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER ${LIBRARY_HEADERS})


