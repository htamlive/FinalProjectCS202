# CMakeList.txt : CMake project for FinalProjectCS202, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Add source to this project's executable.
file(GLOB sourcecode ${CMAKE_SOURCE_DIR}/src/*.cpp)


set(APP_ICON_RESOURCE_WINDOWS "../resources/icons/appicon.rc")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    add_executable(FinalProjectCS202 WIN32 ${sourcecode} ${APP_ICON_RESOURCE_WINDOWS} )
else()
    add_executable(FinalProjectCS202 ${sourcecode} ${APP_ICON_RESOURCE_WINDOWS})
endif(WIN32)





if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FinalProjectCS202 PROPERTY CXX_STANDARD 20)
endif()



message("Hello" + "${CMAKE_BUILD_TYPE}")

if(WIN32)

	#add_custom_command(TARGET FinalProjectCS202 POST_BUILD        # Adds a post-build event to MyTest
    #   COMMAND ${CMAKE_COMMAND} -E copy_directory  # which executes "cmake - E copy_if_different..."
    #        "${CMAKE_SOURCE_DIR}/External/bin"      # <--this is in-file
    #        $<TARGET_FILE_DIR:FinalProjectCS202>)


    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        #message("Hello" + "${CMAKE_BUILD_TYPE}")
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-audio-d.lib)
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-graphics-d.lib)
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-network-d.lib)
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-system-d.lib)
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-window-d.lib)
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/tgui-d.lib)
    else()
        #message("Hello" + "${CMAKE_BUILD_TYPE}")
        #message("Hello" + "${CMAKE_BUILD_TYPE}")
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-audio.lib)
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-graphics.lib)
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-network.lib)
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-system.lib)
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/sfml-window.lib)
        target_link_libraries(FinalProjectCS202 ${CMAKE_SOURCE_DIR}/External/lib/tgui.lib)
    
    endif (CMAKE_BUILD_TYPE STREQUAL "Debug")



    include_directories(${CMAKE_SOURCE_DIR}/External/include)
    #include_directories(${CMAKE_SOURCE_DIR}/External/bin)
endif (WIN32)

if(UNIX)
    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
    include_directories(${SFML_INCLUDE_DIRS})
    if(APPLE)
        target_link_libraries(FinalProjectCS202 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
    else()
        target_link_libraries(FinalProjectCS202 sfml-system sfml-window sfml-graphics sfml-audio sfml-network tgui)
    endif()

    include_directories(${CMAKE_SOURCE_DIR}/TGUI-0.9.5/include)
    file(GLOB LIBRARIES "${CMAKE_SOURCE_DIR}/TGUI-0.9.5/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    target_link_libraries(FinalProjectCS202 ${LIBRARIES})
endif(UNIX)