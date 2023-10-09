file(GLOB SOURCE_FILES
    *.cc
    parsers/*.cc
    utils/*cc
)

add_library(unpackers SHARED  
    ${SOURCE_FILES}
)

target_include_directories(unpackers
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/external
)

target_link_libraries(unpackers
    PUBLIC
        dataProducts
        midas
)