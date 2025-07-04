# init all git submodules
function(init_all_git_submodules)
   find_package(Git QUIET)

   if(WIN32)
      message(WARNING "GIT SUBMODULE: no test")
   else()
      execute_process(COMMAND ${GIT_EXECUTABLE} submodule status
         COMMAND grep -v -c heads
         WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
         OUTPUT_VARIABLE GIT_TEST_RESULT)

      if(GIT_TEST_RESULT EQUAL "0")
         message(STATUS "GIT SUBMODULE: no uninitialized")
         return()
      endif()
   endif()

   message(STATUS "GIT SUBMODULE: init recursive")

   # git submodule status | grep -v -c  heades
   execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
      RESULT_VARIABLE GIT_UPDATE_RESULT)

   if(NOT GIT_UPDATE_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init failed with ${GIT_UPDATE_RESULT}, please checkout submodules")
   endif()
endfunction()