cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
idf_component_register(
    SRCS "SynchUartEsp.cpp"
    PRIV_REQUIRES Mission Courier driver  
)
set(ETL_NO_TESTS ON CACHE BOOL "" FORCE)
set(ETL_NO_CPP_VERSION_CHECK ON CACHE BOOL "" FORCE)
include(FetchContent)
FetchContent_Declare(
    etl
    GIT_REPOSITORY https://github.com/etlcpp/etl.git
    GIT_TAG 20.38.2
)
FetchContent_MakeAvailable(etl)

target_link_libraries(${COMPONENT_LIB} PRIVATE etl)
