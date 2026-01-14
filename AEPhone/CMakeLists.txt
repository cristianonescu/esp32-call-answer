# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(app-template)
add_custom_target(merge_flash ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Merging bootloader + partition + app..."
    COMMAND ${ESPTOOLPY} --chip esp32 merge_bin
        -o ${PROJECT_BINARY_DIR}/esp32-call-buttons.bin
        0x1000 ${PROJECT_BINARY_DIR}/bootloader/bootloader.bin
        0x8000 ${PROJECT_BINARY_DIR}/partition_table/partition-table.bin
        0x10000 ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin
    DEPENDS app bootloader partition_table
)
