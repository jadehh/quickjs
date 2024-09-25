cmake_minimum_required(VERSION 3.14)
project(quickjs)

set(CMAKE_CXX_STANDARD 11)


set(QUICKJS_PATH "./cxx/quickjs")

file(STRINGS "${QUICKJS_PATH}/VERSION" CONFIG_VERSION)

add_definitions(-DCONFIG_VERSION=\"${CONFIG_VERSION}\")


file(GLOB quickjs_src
        "${QUICKJS_PATH}/cutils.c"
        "${QUICKJS_PATH}/libbf.c"
        "${QUICKJS_PATH}/libregexp.c"
        "${QUICKJS_PATH}/libunicode.c"
        "${QUICKJS_PATH}/quickjs.c"
)


#add_executable(${PROJECT_NAME} main.cpp ${quickjs_src} ./cxx/ffi.cpp)
#add_executable(${PROJECT_NAME} main.cpp )
add_library(${PROJECT_NAME} SHARED
        ${quickjs_src}
        ./cxx/ffi.cpp
)




#target_link_libraries(${PROJECT_NAME} PRIVATE user32)
