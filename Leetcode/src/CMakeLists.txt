aux_source_directory(. DIR_SRCS)

add_executable(lc ${DIR_SRCS})

target_include_directories(lc PRIVATE ../include)
target_link_directories(lc PRIVATE ../include)

#target_link_libraries(lc libdata_structure.so)