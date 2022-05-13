add_library(MathFunctions MathFunctions.cpp)
set_property(TARGET MathFunctions PROPERTY VERSION "1.0.0")
set_property(TARGET MathFunctions PROPERTY SOVERSION "1")

# 頭文件
target_include_directories(MathFunctions
                           INTERFACE
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                            $<INSTALL_INTERFACE:include>
                           )

 # should we use our own math functions         
option(USE_MYMATH "Use tutorial provided math implementation" ON)
if(USE_MYMATH)
  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")
  # first we add the executable that generates the table
  add_executable(MakeTable MakeTable.cpp)
  target_link_libraries(MakeTable PRIVATE tutorial_compiler_flags)
  
  # add the command to generate the source code
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable
    )

  # library that just does sqrt
  add_library(SqrtLibrary STATIC
              mysqrt.cpp
              ${CMAKE_CURRENT_BINARY_DIR}/Table.h
              )

  # state that we depend on our binary dir to find Table.h
  target_include_directories(SqrtLibrary PRIVATE
                             ${CMAKE_CURRENT_BINARY_DIR}
                             )
# state that SqrtLibrary need PIC when the default is shared libraries
set_target_properties(SqrtLibrary PROPERTIES
                                              POSITION_INDEPENDENT_CODE True}
)

target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)
target_link_libraries(MathFunctions PRIVATE SqrtLibrary)

endif()

target_link_libraries(MathFunctions PUBLIC tutorial_compiler_flags)

target_compile_definitions(MathFunctions PRIVATE "EXPORTING_MYMATH")
set(installable_libs MathFunctions tutorial_compiler_flags)
if(TARGET SqrtLibrary)
  list(APPEND installable_libs SqrtLibrary)
endif()

# 安裝規則
install(TARGETS ${installable_libs}  EXPORT MathFunctionsTargets DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)         