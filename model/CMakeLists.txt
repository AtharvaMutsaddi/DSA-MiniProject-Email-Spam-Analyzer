cmake_minimum_required(VERSION 3.0)
project(main)

# Include directories for headers
include_directories(include)

# List all source files
set(SOURCE_FILES
    src/finalmodel.c
    src/model_to_score_an_email_file.c
    # Add more source files as needed
)

# List all header files
set(HEADER_FILES
    include/bloomfilter.h
    include/model_to_score_an_email_file.h
    # Add more header files as needed
)

# Add the executable target and specify source files
add_executable(main ${SOURCE_FILES} ${HEADER_FILES})