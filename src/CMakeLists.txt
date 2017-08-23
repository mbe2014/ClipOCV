# Find source files
file(GLOB SOURCES *.cpp *.h)

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME}
  ${OpenCV_LIBS}
)

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADERS *.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
