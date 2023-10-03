file(GLOB SOURCE_FILES
    *.cc
)
    
add_library(dataProducts SHARED 
    ${SOURCE_FILES}
)