set(LOCAL_NAME fft)

set(LOCAL_SOURCES
    src/complex.cpp
    src/fft.cpp
    src/fourier.cpp
)

# ------------------------- Boilerplate for TAFFO ------------------------- #
list(TRANSFORM LOCAL_SOURCES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)
add_custom_command(
    OUTPUT  generated.cpp
    COMMAND cat ${LOCAL_SOURCES} > ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp
    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/taffo_logs
    DEPENDS ${LOCAL_SOURCES}
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_application(${LOCAL_NAME} ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp FLAGS "-O3 -Xvra -max-unroll=0 -temp-dir taffo_logs -float-output ${LOCAL_NAME}.float.o")

# Hack to add ${LOCAL_NAME}.float.o as a BYPRODUCT of ${LOCAL_NAME}.elf
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_NAME}.float.o
    COMMAND true
    DEPENDS ${LOCAL_NAME}.elf)
add_application(${LOCAL_NAME}.float ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_NAME}.float.o SUBDIR ../${LOCAL_NAME}.float)
