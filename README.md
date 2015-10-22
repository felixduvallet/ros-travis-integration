Sandbox for understanding how Travis.CI can work with ROS packages.

The packages start simple and get more complicated:

* basic_ros_pkg: Just a simple C++ node.
* ros_pkg_with_tests: Includes both python and C++ tests
* ros_pkg_with_dependencies: Has dependencies in package.xml that must be resolved by rosdep.

[![Build Status](https://travis-ci.org/felixduvallet/travis-sandbox-ros.svg?branch=master)](https://travis-ci.org/felixduvallet/travis-sandbox-ros)
[![Code Health](https://landscape.io/github/felixduvallet/travis-sandbox-ros/master/landscape.svg?style=flat)](https://landscape.io/github/felixduvallet/travis-sandbox-ros/master)
