cmake_minimum_required(VERSION 2.8)
project( FaceSwap )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( FaceSwap faceswap.cpp )
target_link_libraries( FaceSwap ${OpenCV_LIBS} )

set_target_properties(FaceSwap PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

