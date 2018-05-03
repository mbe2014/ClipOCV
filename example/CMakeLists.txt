# must be a shorter way to do this

add_executable(add add.cpp)
add_executable(db db.cpp)
add_executable(db1 db1.cpp)
add_executable(disk disk.cpp)
add_executable(display display.cpp)
add_executable(display1 display1.cpp)
add_executable(mirror mirror.cpp)
add_executable(mirror1 mirror1.cpp)
add_executable(pow0_5 pow0_5.cpp)
add_executable(sobel1 sobel1.cpp)
add_executable(sobel2 sobel2.cpp)
add_executable(togray togray.cpp)
add_executable(togray1 togray1.cpp)
add_executable(warp warp.cpp)
add_executable(invert invert.cpp)
add_executable(blend blend.cpp)
add_executable(fft fft.cpp)

include_directories(../src)

target_link_libraries(add
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(db
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(db1
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(disk
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(display
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(display1
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(mirror
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(mirror1
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(pow0_5
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(sobel1
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(sobel2
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(togray
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(togray1
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(warp
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(invert
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(blend
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)

target_link_libraries(fft
  ${PROJECT_NAME}
  ${OpenCV_LIBS}
)
