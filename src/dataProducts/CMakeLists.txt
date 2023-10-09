file(GLOB SOURCE_FILES
    *.cc
)
    
add_library(dataProducts
    SHARED
        ${SOURCE_FILES}
)

target_link_libraries(dataProducts
    PUBLIC
        ${ROOT_LIBRARIES}
)