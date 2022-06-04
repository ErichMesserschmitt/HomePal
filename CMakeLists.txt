cmake_minimum_required(VERSION 3.13)

add_subdirectory("HomePalClient")
add_subdirectory("HomePalServer")



#set(InstrumentTypes TTR_INSTR_TTRU3 TTR_INSTR_TAU3 TTR_INSTR_TTRU1)
#set(InstrumentType TTR_INSTR_TAU3 CACHE STRING "Build Device Type")
#set_property(CACHE InstrumentType PROPERTY STRINGS ${InstrumentTypes})

#project (${InstrumentType}
#    DESCRIPTION "Megger TTR project"
#    LANGUAGES CXX)

## default properties
#if(NOT CAN_BUILD_FACTORY_TOOLS)
#    set(CAN_BUILD_FACTORY_TOOLS true)
#endif()

## default properties
#if(NOT IS_RELEASE_BUILD)
#    set(IS_RELEASE_BUILD false)
#endif()

#message("CAN_BUILD_FACTORY_TOOLS: ${CAN_BUILD_FACTORY_TOOLS}")

#set(ENGINE_DATABASE_SUPPORT true)
#set(BLUETOOTH_SUPPORT false)
#set(SUPPORT_MOBILE_CONNECTION false)
#set(SAVE_USER_DATA_ON_INTERNAL_STORAGE false)

#set(USE_SYSTEM_FONTS false)

#set(APP_VERSION_FILE "product-config/${InstrumentType}/VERSION")
#message("APP_VERSION_FILE: ${APP_VERSION_FILE}")

#file (STRINGS "${APP_VERSION_FILE}" APP_VERSION_FILE_CONTENT)
#list (GET APP_VERSION_FILE_CONTENT 0 APP_VERSION)
##remove leading and trailing spaces (and the trailing newline).
#string(STRIP "${APP_VERSION}" APP_VERSION)

#message("VERSION: ${APP_VERSION}")
#add_definitions(-DC_TTR_SOFTWARE_VERSION="${APP_VERSION}")

#if(InstrumentType STREQUAL "TTR_INSTR_TTRU3")
#    add_definitions(-DINSTRUMENT_TTRU3=1)
#    add_definitions(-DINSTRUMENT_NAME="TTRU3")
#    add_definitions(-DINSTRUMENT_BOARD_FW_MASK="TTRU3_AFW_*.hex")

#    add_definitions(-DEMBEDDED_TOUCHSCREEN_DEVICE="/dev/input/touchscreen0")

#    set(HAS_TOUCHSCREEN true)
#    set(SUPPORTS_WEBENGINE true)
#    set(SUPPORT_MOBILE_CONNECTION true)
#    set(BUILD_CARRIER_TEST true)
#    set(MAIN_GUI_APP "ttr-gui-bin")
#    set(SAVE_USER_DATA_ON_INTERNAL_STORAGE false)

#elseif(InstrumentType STREQUAL "TTR_INSTR_TAU3")
#    add_definitions(-DINSTRUMENT_TAU3=1)
#    add_definitions(-DINSTRUMENT_NAME="TAU3")
#    add_definitions(-DINSTRUMENT_BOARD_FW_MASK="TAU3_FW_*.bin")

#    add_definitions(-DEMBEDDED_TOUCHSCREEN_DEVICE="/dev/input/event0")

#    #set(SUPPORTS_WEBENGINE true)

#    set(HAS_TOUCHSCREEN true)
#    set(BLUETOOTH_SUPPORT true)
#    set(SUPPORT_MOBILE_CONNECTION true)
#    set(BUILD_CARRIER_TEST true)
#    set(MAIN_GUI_APP "ttr-gui-ng-bin")
#    set(SAVE_USER_DATA_ON_INTERNAL_STORAGE false)

#elseif(InstrumentType STREQUAL "TTR_INSTR_TTRU1")
#    add_definitions(-DINSTRUMENT_TTRU1=1)
#    add_definitions(-DINSTRUMENT_NAME="TTRU1")
#    add_definitions(-DINSTRUMENT_BOARD_FW_MASK="TTRU1_FW_*.bin")

#    set(HAS_TOUCHSCREEN false)
#    set(SUPPORTS_WEBENGINE false)
#    set(SUPPORT_MOBILE_CONNECTION false)
#    set(BUILD_CARRIER_TEST false)
#    set(MAIN_GUI_APP "ttr-gui-ttru1-bin")
#    set(SAVE_USER_DATA_ON_INTERNAL_STORAGE true)
#endif()

#add_definitions(-DDATABASE_FILE_NAME="instrument.db")

#add_definitions(-DINSTRUMENT_TYPE=${InstrumentType})

#message("InstrumentType: ${InstrumentType}")

#message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}.")

#SET(CMAKE_CROSSCOMPILING 1)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(PROJECT_BINARY_DIR ${CMAKE_BINARY_DIR})

#SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
#    ${PROJECT_BINARY_DIR})

## --------- Setup the Executable output Directory -------------
#SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
#    ${PROJECT_BINARY_DIR})

## --------- Setup the Executable output Directory -------------
#SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
#    ${PROJECT_BINARY_DIR})

#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## silence some CMP0071 warnings
#foreach(p
#        CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
#        )
#    if(POLICY ${p})
#        cmake_policy(SET ${p} NEW)
#    endif()
#endforeach()

## Disable use of C++ API deprecated in Qt 5.15
#add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x050F00)

#if(ANDROID)
#    set(IS_MOBILE_BUILD true)
#    set(BUILD_TEST_STATION false)
#    set(USE_WEBENGINE false)

#    add_definitions(-DPLATFORM_ANDROID=1)
#    add_definitions(-DPLATFORM_MOBILE=1)

#    set(QT_ANDROID_APPLICATION_BINARY "${MAIN_GUI_APP}")

#    # workaround for QTBUG-87863
#    find_package(Qt5 COMPONENTS Core REQUIRED)
#else ()
#    if (CMAKE_C_COMPILER_TARGET MATCHES "arm-poky-linux-gnueabi")
#        set(CMAKE_SYSTEM_PROCESSOR "arm")
#    endif()

#    IF(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
#    set(IS_EMBEDDED_BUILD true)
#    set(BUILD_TEST_STATION true)

#    if(SUPPORTS_WEBENGINE)
#        set(USE_WEBENGINE true)
#    endif()

#    if(SUPPORT_MOBILE_CONNECTION)
#        set(USE_HEIFLIB true)
#        add_definitions(-DUSE_HEIFLIB=1)
#        add_definitions(-DSUPPORT_MOBILE_CONNECTION=1)
#    endif()

#    set(BUILD_MEASUREMENT_BOARD_FW true)

#    add_definitions(-DCLIENT_ARCH="ARM")
#    add_definitions(-DPLATFORM_EMBEDDED=1)

#    set(SUPPORT_USB_MONITORS true)

#    message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
#    message("OE_QMAKE_PATH_EXTERNAL_HOST_BINS: ${OE_QMAKE_PATH_EXTERNAL_HOST_BINS}")
#else ()
#    set(IS_PC_BUILD true)
#    add_definitions(-DPLATFORM_PC=1)
#    add_definitions(-DCLIENT_ARCH="x86")

#    if(CMAKE_SYSTEM_NAME MATCHES "Linux")
#        set(IS_LINUX_PC true)
#        set(BUILD_TEST_STATION true)
#        set(GENERATE_PROTO true)
#        set(BUILD_MEASUREMENT_BOARD_FW true)
#        set(BUILD_EXAMPLES true)

##        set(SUPPORT_USB_MONITORS true)
#    endif()
#endif ()

#if (WIN32 OR CMAKE_C_COMPILER_TARGET MATCHES "i686-w64-mingw32")
#    message( STATUS "MinGW build detected!" )

#    SET(CMAKE_SYSTEM_NAME Windows)

#    set(IS_MINGW true)
#    set(IS_PC_BUILD true)
#    set(IS_LINUX_PC false)
#    set(BUILD_TEST_STATION true)
#    set(BUILD_EXAMPLES false)
#    set(WIN32 true)

#    # fix PS ABI change warning
#    add_compile_options(-Wno-psabi)

#    # DB not supported yet
#    set(ENGINE_DATABASE_SUPPORT false)

#    message( STATUS "IS_MINGW: ${IS_MINGW}" )
#    message( STATUS "WIN32: ${WIN32}" )

#    set(CMAKE_SYSTEM_NAME "Windows")

#    # Fix for mingw crosscompiler on linux host. Remove these lines when bug is fixed
#    # https://bugreports.qt.io/browse/QTBUG-54666?focusedCommentId=347401&page=com.atlassian.jira.plugin.system.issuetabpanels%3Acomment-tabpanel
#    get_property(cxx_features GLOBAL PROPERTY CMAKE_CXX_KNOWN_FEATURES)
#    set(CMAKE_CXX_COMPILE_FEATURES ${cxx_features})
#    set(GLOBAL PROPERTY CMAKE_C_COMPILE_FEATURES ${cxx_features})
#    # end WORKAROUND
#endif()
#endif ()

#if(SAVE_USER_DATA_ON_INTERNAL_STORAGE)
#    add_definitions(-DSAVE_USER_DATA_ON_INTERNAL_STORAGE=1)
#endif()

#message( STATUS "Architecture: ${CMAKE_C_COMPILER_TARGET}" )
#message( STATUS "System Processor: ${CMAKE_SYSTEM_PROCESSOR}" )
#message( STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}" )
#message( STATUS "System name: ${CMAKE_SYSTEM_NAME}" )
#message( STATUS "Build type: ${CMAKE_BUILD_TYPE}" )
#message( STATUS "Build target dir: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )
#message( STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}" )
#message( STATUS "USE_WEBENGINE: ${USE_WEBENGINE}")
#message( STATUS "USE_HEIFLIB: ${USE_HEIFLIB}")
#message( STATUS "ENGINE_DATABASE_SUPPORT: ${ENGINE_DATABASE_SUPPORT}")

#FIND_PACKAGE (Threads)

## treat warnings as errors
#add_compile_options(-Wall -Wextra -Wpedantic -Wcast-qual -Wenum-compare)

#if(NOT IGNORE_WARNINGS)
#    add_compile_options(-Werror)
#endif()

## C++ specific flags
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual")

###    -Wconversion
###    -Wfloat-equal
## #    -Wold-style-cast
## #   -Wsign-conversion

##)

#message( STATUS "IS_EMBEDDED_BUILD: ${IS_EMBEDDED_BUILD}" )
#message( STATUS "IS_PC_BUILD: ${IS_PC_BUILD}" )
#message( STATUS "IS_MOBILE_BUILD: ${IS_MOBILE_BUILD}" )
#message( STATUS "BUILD_TEST_STATION: ${BUILD_TEST_STATION}" )

#set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
#set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

#find_package(Threads REQUIRED)

#if (IS_EMBEDDED_BUILD)
#    set(CMAKE_INSTALL_PREFIX "/")

#    set(USE_SYSTEM_FONTS true)

#    set(BIN_DIR "/usr/local/bin")
#    set(SHARED_DATA_DIR "/usr/local/share/megger")
#    set(LIB_DIR "/usr/lib")
#    set(SYSTEMD_SERVICE_DIR "/etc/systemd/system")

#    set(LOGS_DIR "/var/ttr/log")
#    set(DATA_DIR "/var/ttr")
#    set(ETC_PATH "/etc/ttr")

#    add_definitions(
#        -DENABLE_RAW_DATA_COLLECTION=1
#        )
#else()
#    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install-root")

#    set(BIN_DIR ".")
#    set(SHARED_DATA_DIR ".")
#    set(LIB_DIR ".")
#    set(SYSTEMD_SERVICE_DIR ".")

#    set(LOGS_DIR ".")
#    set(DATA_DIR ".")
#    set(ETC_PATH ".")

#    add_definitions(
#        -DENABLE_RAW_DATA_COLLECTION
#        )
#endif()
#set(TRANSLATIONS_DIR "${SHARED_DATA_DIR}/translations")


#add_definitions(
#    -DTEST_PLAN_RELEASE
#    -DTTR_DATA_DIRECTORY="${DATA_DIR}"
#    -DTTR_LOGS_DIRECTORY="${LOGS_DIR}"
#    -DTTR_RAW_DATA_DIRECTORY="${LOGS_DIR}/raw_data"
#    -DTTR_ETC_PATH="${ETC_PATH}"
#    )

#if(USE_WEBENGINE)
#    add_definitions(-DUSE_WEBENGINE=1)
#endif()

#if(USE_SYSTEM_FONTS)
#    add_definitions(-DUSE_SYSTEM_FONTS=1)
#endif()

#if(BUILD_TEST_STATION)
#    add_definitions(
#        -DTEST_STATION
#        )
#endif()

#if(SUPPORT_USB_MONITORS)
#add_definitions(-DSUPPORT_USB_MONITORS=1)
#endif()

## Must use GNUInstallDirs to install libraries into correct
## locations on all platforms.
##include(GNUInstallDirs)

#if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
#    message(SEND_ERROR "In-source builds are not allowed.")
#endif ()

#set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_COLOR_MAKEFILE   ON)

#if (WIN32)
#    # Remove 'lib' prefix for shared libraries on Windows
#    set(CMAKE_SHARED_LIBRARY_PREFIX "")

#    # enable unicode
#    add_definitions(-DUNICODE -D_UNICODE)
#endif ()


#if (NOT WIN32 AND NOT APPLE)
#    # (GNU ld) Use -Bsymbolic-functions for your shared libraries.
#    # This tells the linker to use direct local jumps to symbols within your library
#    # instead of trying to resolve them by the usual means.
#    # The effect is that every function call within your library will be initially faster since there's no lookup required.
#    # This leads to faster load times.
#    add_link_options(-Wl,-Bsymbolic -Wl,-Bsymbolic-functions)
#endif ()

##if(IS_LINUX_PC)
##include(PVS-Studio.cmake)
##pvs_studio_add_target(TARGET example1.analyze ALL
##                      OUTPUT FORMAT errorfile
##                      ANALYZE ttr-rpc ttr-rpc-protocol ttr-client-api common common-api license-manager ttr-console-tester ttr-embedded-api ttr-server
##                      MODE GA:1,2 OP
##                      LOG target.err)
##endif()

## Yocto recipes
#FILE(GLOB_RECURSE YoctoRecipes "yocto-recipe/*")
#add_custom_target(yocto-recipes SOURCES ${YoctoRecipes})

################
## API
#add_library(ttr-api INTERFACE)
#target_include_directories( ttr-api INTERFACE api/ )
#add_custom_target(API SOURCES api/TTR_API.h api/TTR_API_Internal.h)
################\

#add_subdirectory("product-config")

#add_subdirectory("lib")
#add_subdirectory("common")
#add_subdirectory("client")
#add_subdirectory("gui")

#if(IS_PC_BUILD AND BUILD_EXAMPLES)
#    add_subdirectory("examples")
#endif()

#add_subdirectory("transformer-model")

#if(IS_PC_BUILD AND CAN_BUILD_FACTORY_TOOLS)
#    add_subdirectory("factory")
#endif()

#if(BUILD_TEST_STATION)
#    add_subdirectory("server")
#endif()

#if(IS_EMBEDDED_BUILD OR IS_LINUX_PC)
#    add_subdirectory("tools-embedded")
#endif()

#add_subdirectory(tests)
