project (HomePalClient LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
cmake_minimum_required(VERSION 3.9)
set(CMAKE_AUTOMOC ON)

macro(print_all_variables)
    message(STATUS "print_all_variables-{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables-}")
endmacro()

FILE(GLOB SOURCE_FILES
    src/*.cpp
    src/*.h
    src/DataClasses/*.cpp
    src/DataClasses/*.h
    src/Serialization/*.cpp
    src/Serialization/*.h
    src/Connection/*.cpp
    src/Connection/*.h
    )
link_directories(${CMAKE_SOURCE_DIR}/lib)

find_package(Qt6 COMPONENTS Core Quick Qml Concurrent Widgets Multimedia WebSockets REQUIRED)
#find_package(Qt6QuickCompiler)

qt6_add_resources(RESOURCES ui/resources.qrc)
qt6_add_resources(RESOURCES ui/images.qrc)


add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
    ${RESOURCES}
    )

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Quick
    Qt6::Qml
    Qt6::Concurrent
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::WebSockets
)

set(QML_DIR ui)
set(QML_DIR_CMP ui/Components)
set(QML_DIR_VWS ui/Views)
set(QML_DIR_FONTS ui/fonts)
set(QML_DIR_ITEMS ui/Items)
set(QML_DIR_POPUPS ui/Popups)

FILE(GLOB QmlFiles "${QML_DIR}/*.qml")
FILE(GLOB QmlFiles_CMP "${QML_DIR_CMP}/*.qml")
FILE(GLOB QmlFiles_VWS "${QML_DIR_VWS}/*.qml")
FILE(GLOB QmlFiles_ITM "${QML_DIR_ITEMS}/*.qml")
FILE(GLOB QmlFiles_PPS "${QML_DIR_POPUPS}/*.qml")
FILE(GLOB QmlFiles_FNT "${QML_DIR_FONTS}/*.ttf")
FILE(GLOB QmlFiles_RSC "${QML_DIR}/*.qrc")

add_custom_target(${PROJECT_NAME}-qml SOURCES ${QmlFiles})
add_custom_target(${PROJECT_NAME}-views SOURCES ${QmlFiles_VWS})
add_custom_target(${PROJECT_NAME}-components SOURCES ${QmlFiles_CMP})
add_custom_target(${PROJECT_NAME}-items SOURCES ${QmlFiles_ITM})
add_custom_target(${PROJECT_NAME}-popups SOURCES ${QmlFiles_PPS})
add_custom_target(${PROJECT_NAME}-fonts SOURCES ${QmlFiles_FNT})
add_custom_target(${PROJECT_NAME}-recources SOURCES ${QmlFiles_RSC})


# Make Qt Creator aware of where the QML modules live
set (_QML_IMPORT_PATHS "")

## Add new module paths here.
list (APPEND _QML_IMPORT_PATHS ${QML_DIR})
list (APPEND _QML_IMPORT_PATHS ${QML_DIR_CMP})
#list (APPEND _QML_IMPORT_PATHS ${QML_DIR_VWS})

set (
    QML_IMPORT_PATH
    ${_QML_IMPORT_PATHS}
    CACHE
    STRING
    "Path used to locate CMake modules by Qt Creator"
    FORCE
)


print_all_variables()
