# CMakeList.txt : CMake project for FinalProjectCS202, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.21)



# Add source to this project's executable.
file(GLOB sourcecode ${CMAKE_SOURCE_DIR}/FinalProjectCS202/*.cpp)
add_executable (FinalProjectCS202 ${sourcecode})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FinalProjectCS202 PROPERTY CXX_STANDARD 20)
endif()



#message("Hello" + "${CMAKE_CURRENT_SOURCE_DIR}")
# TODO: Add tests and install targets if needed.

if(WIN32)
	#add_custom_command(TARGET FinalProjectCS202 POST_BUILD        # Adds a post-build event to MyTest
    #    COMMAND ${CMAKE_COMMAND} -E copy_directory  # which executes "cmake - E copy_if_different..."
    #        "${CMAKE_SOURCE_DIR}/External/bin"      # <--this is in-file
    #        $<TARGET_FILE_DIR:FinalProjectCS202>)





    target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-audio-d.lib)
    target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-graphics-d.lib)
    target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-network-d.lib)
    target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-system-d.lib)
    target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-window-d.lib)
    target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/tgui-d.lib)

    include_directories(${CMAKE_SOURCE_DIR}/External/include)
    include_directories(${CMAKE_SOURCE_DIR}/External/bin)
endif (WIN32)

if(UNIX)
    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
    include_directories(${SFML_INCLUDE_DIRS})
    target_link_libraries(FinalProjectCS202 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
endif (UNIX)





