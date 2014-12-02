include_directories(${SFML2_INCLUDE_DIRS})

file(GLOB SOUNDS_SRC "*.cc")

add_executable(sounds ${SOUNDS_SRC})

target_link_libraries(sounds
  gzzzt0
  gzzzt-shared0
  ${SFML2_LIBRARIES}
)
