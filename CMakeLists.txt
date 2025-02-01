CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(MC_RCON_CLIENT)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED YES)


cmake_policy(SET CMP0167 NEW)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

if(WIN32)

	#wxWidgets
    set(wxWidgets_ROOT_DIR "./utils-WIN32/wxWidgetsWIN32")
    set(wxWidgets_INCLUDE_DIRS 
        "${wxWidgets_ROOT_DIR}/include/wx-3.3/" 
        "${wxWidgets_ROOT_DIR}/lib/wx/include/x86_64-w64-mingw32-msw-unicode-3.3"
    )
    
    set(wxWidgets_LIBRARY_DIRS "${wxWidgets_ROOT_DIR}/lib")
	set(wxWidgets_LIBRARIES
		wx_baseu-3.3-x86_64-w64-mingw32
		wx_mswu_propgrid-3.3-x86_64-w64-mingw32
		wx_baseu_net-3.3-x86_64-w64-mingw32
		wx_mswu_qa-3.3-x86_64-w64-mingw32
		wx_baseu_xml-3.3-x86_64-w64-mingw32
		wx_mswu_ribbon-3.3-x86_64-w64-mingw32
		wx_mswu_adv-3.3-x86_64-w64-mingw32
		wx_mswu_richtext-3.3-x86_64-w64-mingw32
		wx_mswu_aui-3.3-x86_64-w64-mingw32
		wx_mswu_stc-3.3-x86_64-w64-mingw32
		wx_mswu_core-3.3-x86_64-w64-mingw32
		wx_mswu_webview-3.3-x86_64-w64-mingw32
		wx_mswu_gl-3.3-x86_64-w64-mingw32
		wx_mswu_xrc-3.3-x86_64-w64-mingw32
		wx_mswu_html-3.3-x86_64-w64-mingw32
		wx_mswu_media-3.3-x86_64-w64-mingw32
	)

    include_directories(${wxWidgets_INCLUDE_DIRS})
    link_directories(${wxWidgets_LIBRARY_DIRS})

	
	
	#sqlite3
    set(SQLITE3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/utils-WIN32/sqlite3_WIN32)  
    set(SQLITE3_LIB_DIR ${CMAKE_SOURCE_DIR}/utils-WIN32/sqlite3_WIN32)      
    include_directories(${SQLITE3_INCLUDE_DIR})
    link_directories(${SQLITE3_LIB_DIR})
    set(SQLITE3_LIBRARIES ${SQLITE3_LIB_DIR}/libsqlite3.a)


	#boost
    set(BOOST_ROOT "./utils-WIN32/boost_build")
    set(CMAKE_PREFIX_PATH ${BOOST_ROOT})
    set(BOOST_INCLUDE_DIR ${BOOST_ROOT}/include)
    set(BOOST_LIBRARY_DIR ${BOOST_ROOT}/lib)
    
    include_directories(${BOOST_INCLUDE_DIR})   
    link_directories(${BOOST_LIBRARY_DIR})
    
    find_package(Boost 1.87.0 REQUIRED COMPONENTS system thread
    PATHS "./utils-WIN32/boost_build"
    NO_DEFAULT_PATH)

    
elseif(UNIX)
    find_package(wxWidgets REQUIRED COMPONENTS core base)
    find_package(SQLite3 REQUIRED)
    find_package(Boost REQUIRED)
    include(${wxWidgets_USE_FILE})
endif()

#DIZINLERI AYARLAMA
SET(DIZIN_SRC ${CMAKE_SOURCE_DIR}/src)
SET(DIZIN_INCLUDE ${CMAKE_SOURCE_DIR}/include)

#PROGRAM DOSYALARINI AYARLAMA: SOURCE CODE
SET(
    PROGRAM_SRC 
    ${DIZIN_SRC}/main.cpp
    
    ${DIZIN_SRC}/gui/window.cpp
    ${DIZIN_SRC}/gui/login_frame.cpp
    ${DIZIN_SRC}/gui/main_frame.cpp
    
    ${DIZIN_SRC}/database/dbProcess.cpp
    
    ${DIZIN_SRC}/rcon-connection/rcon.cpp
    
    ${DIZIN_SRC}/file-operations/configParser.cpp
    

)

#PROGRAM DOSYALARINI AYARLAMA: HEADER
SET(
    PROGRAM_INCLUDE
    ${DIZIN_INCLUDE}/window.hpp
    ${DIZIN_INCLUDE}/login_frame.hpp
    ${DIZIN_INCLUDE}/main_frame.hpp
    ${DIZIN_INCLUDE}/funcEnums.hpp
    ${DIZIN_INCLUDE}/dbConnector.hpp
    ${DIZIN_INCLUDE}/rcon.hpp
    ${DIZIN_INCLUDE}/configParser.hpp

    
    
    
    )


if(WIN32)
    INCLUDE_DIRECTORIES(
        ${wxWidgets_INCLUDE_DIRS}
        )
    
    add_executable(
        ${PROJECT_NAME} 
        ${PROGRAM_SRC}
        )
    
    target_link_libraries(
        ${PROJECT_NAME}
        ${wxWidgets_LIBRARIES}
        ${SQLITE3_LIBRARIES}
        Boost::system
        Boost::thread
        ws2_32
        )



elseif(UNIX)
    INCLUDE_DIRECTORIES(
        ${PROGRAM_INCLUDE} 
        ${wxWidgets_INCLUDE_DIRS} 
        ${SQLite3_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        )
    
    add_executable(
        ${PROJECT_NAME} 
        ${PROGRAM_SRC}
        )

    target_link_libraries(
        ${PROJECT_NAME}
        ${wxWidgets_LIBRARIES}
        ${SQLite3_LIBRARIES}
        ${Boost_LIBRARIES}
          )

endif()
