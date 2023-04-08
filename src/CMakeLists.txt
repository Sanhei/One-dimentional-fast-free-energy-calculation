

# problem 5.1
add_executable(free_energy
  Free_energy.cpp
)

target_link_libraries(free_energy
  ${Boost_LIBRARIES}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  )

install(TARGETS free_energy
  DESTINATION bin
)

