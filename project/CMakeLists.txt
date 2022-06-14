INCLUDE_DIRECTORIES(include)
ADD_LIBRARY(prepmatrix STATIC src/matrix.cpp src/base_methods.cpp src/base_math.cpp src/extra_math.cpp)

ADD_SUBDIRECTORY(tests)
