# init all git submodules
function(init_all_git_submodules)
   find_package(Git QUIET)

   if(WIN32)
      message(WARNING "GIT SUBMODULE: no test on windows")
      return()
   else()
      execute_process(COMMAND ${GIT_EXECUTABLE} submodule status
         COMMAND grep -v -c heads
         WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
         OUTPUT_VARIABLE GIT_TEST_RESULT)

      if(GIT_TEST_RESULT EQUAL "0")
         message(STATUS "GIT SUBMODULE: no uninitialized repositories")
         return()
      endif()
   endif()

   message(STATUS "GIT SUBMODULE: init recursive")

   # git submodule status | grep -v -c  heades
   execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
      RESULT_VARIABLE GIT_UPDATE_RESULT)

   if(NOT GIT_UPDATE_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init failed with ${GIT_UPDATE_RESULT}, please checkout submodules manually")
   endif()

   execute_process(COMMAND ${GIT_EXECUTABLE} submodule foreach "git switch master"
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
      RESULT_VARIABLE GIT_SWITCH_RESULT)

   if(NOT GIT_SWITCH_RESULT EQUAL "0")
      message(FATAL_ERROR "git failed with ${GIT_SWITCH_RESULT}, could not set all submodules to master branch")
   endif()

endfunction()
