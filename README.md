# ROS package continuous integration with travis.

SOME NEW FEATURE!

This repository contains a [.travis.yml](https://github.com/felixduvallet/ros-travis-integration/blob/master/.travis.yml)
file for setting up continuous integration (through Travis-CI) for any ROS package.

Improvements & issues are welcome via pull requests and the issue tracker.
If you find this Travis file helpful, please star this repository!

In addition, this repository contains several example (trivial) ROS packages
that serve as example packages for Travis to build and test. They also showcase
how to correctly handle dependencies (system and source).

[![Build Status](https://travis-ci.org/blackpc/ros-travis-integration.svg?branch=master)](https://travis-ci.org/blackpc/ros-travis-integration)

# Installation instructions

To enable Travis continuous integration for your ROS package, first copy these
files to the *root* of your repository:
 - [.travis.yml](https://github.com/felixduvallet/ros-travis-integration/blob/master/.travis.yml): The script that tells Travis CI what to build.
 - [dependencies.rosinstall](https://github.com/felixduvallet/ros-travis-integration/blob/master/dependencies.rosinstall): A wstool-generated list of source dependencies
   (optional). **Update the contents with your packages.**
 - [catkin.options](https://github.com/felixduvallet/ros-travis-integration/blob/master/catkin.options): Contents of this file are passed as arguments to catkin_make,
   for example package blacklists (optional).

Then, log on to travis-ci and turn on continuous integration for the repository:
 - [travis-ci.org](http://travis-ci.org) is free for open-source repositories.
 - [travis-ci.com](http://travis-ci.com) provides the same functionality for private repositories (at a price).

From then on, any push to this repository will trigger a new Travis-ci build.

# About Travis-CI

Travis provides a clean virtual machine for each build. The .travis.yml script
installs ROS, creates a workspace, resolves all given dependencies, and sets
environment variables (devel/setup.bash). Then, it compiles the entire ROS
workspace (ensuring there are no compilation errors), and runs any available
unittests. If any of the compilation/test phases fail, the build is marked as a
failure. Otherwise, it's a clean build.

For more information on Travis CI, see their documentation:
http://docs.travis-ci.com/

# Handling Dependencies:

We handle two types of package dependencies specified in the package manifest:

  - system dependencies that can be installed using `rosdep`, including other
    ROS packages and system libraries. These dependencies must be known to
    `rosdistro` and get installed using apt-get.
  - package dependencies that must be checked out from source. These are handled by
    `wstool`, and should be listed in a file named dependencies.rosinstall.

All dependencies should be handled in one of these fashions; in general you
should not install packages directly to the .travis.yml file.
If you are missing a package, it's most likely that you haven't defined the
dependency in package.xml.

Note that any packages located inside your catkin workspace will take
precendence over the rosdistro system-wide package.
This allows you to use the cutting-edge version of a package directly from
source.

For public builds (i.e. when using travis-ci.org), `wstool` dependencies should
use a *public* access link (for instance, the https github address instead of
ssh). Otherwise you will get a "Permission denied (publickey)" error.

The example package `ros_pkg_with_dependencies` showcases both types of
dependencies: there's a dependency on audio_common_msgs (known to rosdistro), so
that package will get installed using `rosdep`. There is also a public
repository link inside `dependencies.rosinstall`, so Travis will clone the
repository into the workspace before building anything.  Make building your own
package, make sure to remove the contents of dependencies.rosinstall and add
your package's source dependencies instead.

# ROS variables:

There are two variables you may want to change:

  - ROS_DISTRO (indigo or jade, default is indigo): Note that packages must be
    available for ubuntu 14.04 trusty, so kinetic is not supported at this time.
  - ROSINSTALL_FILE (default is dependencies.rosinstall in repo): This file
    list all necessary repositories in wstool format (see the ros wiki). If the
    file does not exists then nothing happens.
  - CATKIN_OPTIONS (default is catkin.options in repo): File **whose contents**
    specify the options passed to catkin_make. If this file does not exist,
    catkin_make is called without options. For example, you can have catkin
    *not* build several packages by putting this inside the file:

        -DCATKIN_BLACKLIST_PACKAGES=pkg_a;pkg_b

# Private repositories:

Travis-ci.com can build a private repository. However if your package has
dependencies that are also private, you have to go through additional steps.

The instructions are generally listed here:
http://docs.travis-ci.com/user/private-dependencies/

1. Create a machine account on github.
2. Generate a public/private key on your computer, if not done already.
3. Add the public key (id_rsa.pub) to the machine account's github settings (see [here](https://developer.github.com/guides/managing-deploy-keys/#machine-users)).
4. In github, make sure the machine account has read access to all the dependency repositories.
5. In github, add the machine account as an administrator for the repository you want to build (note: not the dependencies).
6. In travis settings for the machine user, add the *private* key (id_rsa) in the build job settings.

NOTE: This very somewhat experimental.

# The example packages

These packages start simple and get more complicated, and serve as sample
packages to give Travis something to do. They're also examples of how to best
handle dependencies on other packages; both checking out from source.

* basic_ros_pkg: Just a simple C++ node.
* ros_pkg_with_tests: Includes both python and C++ tests
* ros_pkg_with_dependencies: Has dependencies in package.xml that must be
  resolved by wstool (in this case, clone pocketsphinx from source) and rosdep
  (in this case, install audio_common_msgs using rosdep).

You can look at the Travis build log to see exactly how it resolves dependencies
and then builds the package.
