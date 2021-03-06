################################################################################
#
# medInria
#
# Copyright (c) INRIA 2013 - 2014. All rights reserved.
# See LICENSE.txt for details.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
################################################################################

macro(set_exe_install_rules
  target
  )

################################################################################
#
# Usage: set_exe_install_rules(target)
# set rules for the executable designed by the target
#
################################################################################

install(TARGETS ${target}
  RUNTIME DESTINATION bin
  BUNDLE  DESTINATION bin
  )

## #############################################################################
##  Mac bundle specificites
## #############################################################################

if (APPLE)
    set(MACOSX_BUNDLE_BUNDLE_NAME
    ${target}
    )
  set(MACOSX_BUNDLE_ICON_FILE
    ${target}.icns
    )
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING
    ${${target}_VERSION}
    )
  set(MACOSX_BUNDLE_BUNDLE_VERSION
    ${${target}_VERSION}
    )
  set(MACOSX_BUNDLE_LONG_VERSION_STRING
    "Version ${${target}_VERSION}"
    )
  set(${target}_RESOURCE_DIR
    ${EXECUTABLE_OUTPUT_PATH}/${target}.app/Contents/Resources
    )
  add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${${target}_RESOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/resources/${target}.icns ${${target}_RESOURCE_DIR}
    )

  install(CODE "
  execute_process(COMMAND
    \${QT_BINARY_DIR}/macdeployqt \${CMAKE_INSTALL_PREFIX}/bin/${target}.app
    )
    execute_process(COMMAND
      \${dtk_DIR}/bin/dtkDeploy \${CMAKE_INSTALL_PREFIX}/bin/${target}.app -inject-dir=\${CMAKE_CURRENT_BINARY_DIR}/plugins
      )
  ")
endif()

endmacro()

