# tests/CMakeLists.txt

add_executable(test_jacobi test_jacobi.cpp)
target_link_libraries(test_jacobi LinearSolversLib)

add_executable(test_gauss_seidel test_gauss_seidel.cpp)
target_link_libraries(test_gauss_seidel LinearSolversLib)

# Indique au compilateur où chercher les .h
target_include_directories(test_jacobi PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

target_include_directories(test_gauss_seidel PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)
