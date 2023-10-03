project(unpacker)

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})
include("${ROOT_DIR}/RootMacros.cmake")

find_package(ZLIB REQUIRED)

cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

#Set the path for where to look for the libraries of the installed target
set(CMAKE_INSTALL_RPATH "${CMAKE_SOURCE_DIR}/lib")

#create installation directories
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#Add all the sub directories
add_subdirectory(external/midas)
add_subdirectory(src/dataProducts)
add_subdirectory(src/unpackers)

#These are the data products for which we make root dictionaries
set(DataProducts 
    ${CMAKE_SOURCE_DIR}/src/dataProducts/DataProduct.hh
    ${CMAKE_SOURCE_DIR}/src/dataProducts/WFD5Header.hh
    ${CMAKE_SOURCE_DIR}/src/dataProducts/ChannelHeader.hh
    ${CMAKE_SOURCE_DIR}/src/dataProducts/WaveformHeader.hh
    ${CMAKE_SOURCE_DIR}/src/dataProducts/Waveform.hh
    ${CMAKE_SOURCE_DIR}/src/dataProducts/FC7Header.hh
)

#Create the executable
add_executable(pioneer_unpacker src/main.cc)

#link libraries
target_link_libraries(pioneer_unpacker
    PRIVATE 
        unpackers dataProducts midas ${ZLIB_LIBRARIES} ${ROOT_LIBRARIES}
)

#link include directories
target_include_directories(pioneer_unpacker 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include ${ZLIB_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS}
)

root_generate_dictionary(DataProductDictionary
    ${DataProducts} 
    MODULE dataProducts
    LINKDEF ${CMAKE_SOURCE_DIR}/src/dataProducts/LinkDef.h
)
    
# Move the dictionaries so that they are next to the .so file
add_custom_command(
    TARGET pioneer_unpacker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_BINARY_DIR}/libdataProducts_rdict.pcm 
    ${CMAKE_BINARY_DIR}/libdataProducts.rootmap
    ${CMAKE_SOURCE_DIR}/lib
)

# Install the libraries
install(TARGETS unpackers
                dataProducts
                midas 
        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib
)

#Install the executable
install(TARGETS pioneer_unpacker
        DESTINATION ${CMAKE_SOURCE_DIR}/bin
)

