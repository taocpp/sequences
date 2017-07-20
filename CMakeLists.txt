cmake_minimum_required (VERSION 3.2.0 FATAL_ERROR)

# set project and version
project (taocpp_sequences VERSION 1.0.0 LANGUAGES CXX)

# define a header-only library
add_library (taocpp_sequences INTERFACE)
add_library (taocpp::sequences ALIAS taocpp_sequences)
target_include_directories (taocpp_sequences INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# features used by taocpp/sequences
target_compile_features (taocpp_sequences INTERFACE
  cxx_alias_templates
  cxx_constexpr
  cxx_decltype
  cxx_noexcept
  cxx_rvalue_references
  cxx_static_assert
  cxx_template_template_parameters
  cxx_variadic_templates
)

# testing
enable_testing ()
option (TAOCPP_SEQUENCES_BUILD_TESTS "Build test programs" ON)
if (TAOCPP_SEQUENCES_BUILD_TESTS)
  add_subdirectory (src/test/seq)
endif ()

# installation directories
set (TAOCPP_SEQUENCES_INSTALL_INCLUDE_DIR "include" CACHE STRING "The installation include directory")
set (TAOCPP_SEQUENCES_INSTALL_DOC_DIR "share/doc/tao/seq" CACHE STRING "The installation doc directory")

# install
install (DIRECTORY include/ DESTINATION ${TAOCPP_SEQUENCES_INSTALL_INCLUDE_DIR})
install (FILES LICENSE DESTINATION ${TAOCPP_SEQUENCES_INSTALL_DOC_DIR})
