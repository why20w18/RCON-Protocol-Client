CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(MC_RCON_CLIENT)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED YES)

#PLATFORM AYARLARI:
#GEREKLI DIS KUTUPHANELER ASAGIDADIR
#-> wxWidgets
#-> sqlite3

if(WIN32)
                          #mingw ile derlenmis wxWidgets kutuphanesi readme.md (bknz:TEKNIK-1)
    set(wxWidgets_ROOT_DIR "/home/archw/wxWidgetsWIN32")
    
    set(wxWidgets_INCLUDE_DIRS 
        "${wxWidgets_ROOT_DIR}/include/wx-3.3/" 
        "${wxWidgets_ROOT_DIR}/lib/wx/include/x86_64-w64-mingw32-msw-unicode-3.3"
    )
    
    set(wxWidgets_LIBRARY_DIRS "${wxWidgets_ROOT_DIR}/lib")
    set(wxWidgets_LIBRARIES
        "${wxWidgets_ROOT_DIR}/lib/"
        "${wxWidgets_ROOT_DIR}/lib/libwx_baseu-3.3-x86_64-w64-mingw32.dll.a"
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_propgrid-3.3-x86_64-w64-mingw32.dll.a"
        "${wxWidgets_ROOT_DIR}/lib/libwx_baseu_net-3.3-x86_64-w64-mingw32.dll.a"
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_qa-3.3-x86_64-w64-mingw32.dll.a"
        "${wxWidgets_ROOT_DIR}/lib/libwx_baseu_xml-3.3-x86_64-w64-mingw32.dll.a  "
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_ribbon-3.3-x86_64-w64-mingw32.dll.a"
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_adv-3.3-x86_64-w64-mingw32.dll.a "
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_richtext-3.3-x86_64-w64-mingw32.dll.a"
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_aui-3.3-x86_64-w64-mingw32.dll.a "
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_stc-3.3-x86_64-w64-mingw32.dll.a"
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_core-3.3-x86_64-w64-mingw32.dll.a  "
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_webview-3.3-x86_64-w64-mingw32.dll.a"
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_gl-3.3-x86_64-w64-mingw32.dll.a "
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_xrc-3.3-x86_64-w64-mingw32.dll.a"
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_html-3.3-x86_64-w64-mingw32.dll.a  "
        "${wxWidgets_ROOT_DIR}/lib/libwx_mswu_media-3.3-x86_64-w64-mingw32.dll.a"
    )
    include_directories(${wxWidgets_INCLUDE_DIRS})
    link_directories(${wxWidgets_LIBRARY_DIRS})


    set(SQLITE3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/sqlite3_WIN32)  
    set(SQLITE3_LIB_DIR ${CMAKE_SOURCE_DIR}/sqlite3_WIN32)      
    include_directories(${SQLITE3_INCLUDE_DIR})
    link_directories(${SQLITE3_LIB_DIR})
    set(SQLITE3_LIBRARIES ${SQLITE3_LIB_DIR}/libsqlite3.a)


elseif(UNIX)
    find_package(wxWidgets REQUIRED COMPONENTS core base)
    find_package(SQLite3 REQUIRED)
    include(${wxWidgets_USE_FILE})
endif()

#DIZINLERI AYARLAMA
SET(DIZIN_SRC ${CMAKE_SOURCE_DIR}/src)
SET(DIZIN_INCLUDE ${CMAKE_SOURCE_DIR}/include)

#PROGRAM DOSYALARINI AYARLAMA: SOURCE CODE
SET(
    PROGRAM_SRC 
    ${DIZIN_SRC}/main.cpp
    ${DIZIN_SRC}/main_frame.cpp
    ${DIZIN_SRC}/window.cpp
    ${DIZIN_SRC}/dbProcess.cpp

    
)

#PROGRAM DOSYALARINI AYARLAMA: HEADER
SET(
    PROGRAM_INCLUDE
    ${DIZIN_INCLUDE}/funcEnums.hpp
    ${DIZIN_INCLUDE}/main_frame.hpp
    ${DIZIN_INCLUDE}/window.hpp
    ${DIZIN_INCLUDE}/dbConnector.hpp
    ${DIZIN_INCLUDE}/rcon.hpp
    
    
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
        )


elseif(UNIX)
    INCLUDE_DIRECTORIES(
        ${PROGRAM_INCLUDE} 
        ${wxWidgets_INCLUDE_DIRS} 
        ${SQLite3_INCLUDE_DIRS}
        )
    
    add_executable(
        ${PROJECT_NAME} 
        ${PROGRAM_SRC}
        )

    target_link_libraries(
        ${PROJECT_NAME}
        ${wxWidgets_LIBRARIES}
        ${SQLite3_LIBRARIES}
          )

endif()