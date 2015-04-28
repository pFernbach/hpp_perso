#
# Copyright (c) 2014 CNRS
# Authors: Florent Lamiraux
#
#
# This file is part of hpp_tutorial
# hpp_tutorial is free software: you can redistribute it
# and/or modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation, either version
# 3 of the License, or (at your option) any later version.
#
# hpp_tutorial is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Lesser Public License for more details.  You should have
# received a copy of the GNU Lesser General Public License along with
# hpp_tutorial  If not, see
# <http://www.gnu.org/licenses/>.

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CXX_DISABLE_WERROR TRUE)
INCLUDE(cmake/base.cmake)
INCLUDE(cmake/python.cmake)

SET(PROJECT_NAME hpp_perso)
SET(PROJECT_DESCRIPTION
  "test de motion planning de pierre"
)
SET(PROJECT_URL "")

FINDPYTHON()

SETUP_PROJECT()

# Catkin stuff
FIND_PACKAGE(catkin)
CATKIN_PACKAGE()

# Activate hpp-util logging if requested
SET (HPP_DEBUG FALSE CACHE BOOL "trigger hpp-util debug output")
IF (HPP_DEBUG)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHPP_DEBUG")
ENDIF()

#ADD_DOC_DEPENDENCY("hpp-core >= 3")
ADD_REQUIRED_DEPENDENCY("hpp-corbaserver >= 3")
ADD_REQUIRED_DEPENDENCY(hpp-util >= 3)

# Declare Headers
SET(${PROJECT_NAME}_HEADERS
  include/hpp/perso/planner.hh
	include/hpp/perso/rrtperso.hh
	include/hpp/perso/rrtconnect.hh
)


# Create and install executable running the corba server
ADD_EXECUTABLE (hpp-perso-server
  src/planner.cc
	src/rrtperso.cc
	src/rrtconnect.cc
	src/mainPerso.cc	
)
# Link executable with hpp-corbaserver library
PKG_CONFIG_USE_DEPENDENCY (hpp-perso-server hpp-corbaserver hpp-util)
# Install executable
INSTALL (TARGETS hpp-perso-server DESTINATION ${CMAKE_INSTALL_BINDIR})


SET(CATKIN_PACKAGE_SHARE_DESTINATION
  ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME})

install(FILES
  urdf/robot_boule.urdf
	urdf/robot_stick.urdf
	urdf/robot_cursor.urdf
	urdf/robot_r2d2.urdf
  urdf/box.urdf
  urdf/ur5_robot.urdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/urdf
  )
install(FILES
  srdf/robot_boule.srdf
	srdf/robot_stick.srdf
	srdf/robot_cursor.srdf
	srdf/robot_r2d2.srdf
  srdf/box.srdf
  srdf/ur5_robot.srdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/srdf
  )
install (FILES
  src/hpp/corbaserver/r2d2/robot_r2d2.py
  src/hpp/corbaserver/r2d2/__init__.py
  DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/r2d2)

install (FILES
  src/hpp/corbaserver/boule/robot_boule.py
  src/hpp/corbaserver/boule/__init__.py
  DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/boule)

install (FILES
  src/hpp/corbaserver/stick/robot_stick.py
  src/hpp/corbaserver/stick/__init__.py
  DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/stick)

install (FILES
  src/hpp/corbaserver/cursor/robot_cursor.py
  src/hpp/corbaserver/cursor/__init__.py
  DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/cursor)

install (FILES
  src/hpp/corbaserver/ur5/ur5_robot.py
  src/hpp/corbaserver/ur5/__init__.py
  DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/ur5)


# Installation for documentation
#install(FILES
#  urdf/robot_boule.urdf
#	urdf/robot_stick.urdf
#	urdf/robot_cursor.urdf
#	urdf/robot_r2d2.urdf
#  urdf/box.urdf
#  DESTINATION
#  ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME}/doxygen-html/urdf
#  )
#install(FILES
#  script/tutorial_1.py
#  script/tutorial_2.py
#  DESTINATION
#  ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME}/doxygen-html/script
#  )
SETUP_PROJECT_FINALIZE()
