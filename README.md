# ROS package continuous integration with travis.

This repository contains a .travis.yml file for setting up continuous integration
(through Travis-CI) for any ROS package.

Improvements & issues are welcome via pull requests and the issue tracker.

In addition, this repository contains several example (trivial) ROS packages
that serve as example packages for Travis to build and test. They also showcase
how to correctly handle dependencies (system and source).

[![Build Status](https://travis-ci.org/felixduvallet/ros-travis-integration.svg?branch=master)](https://travis-ci.org/felixduvallet/ros-travis-integration)

# Installation instructions

To enable Travis continuous integration for your ROS package, first copy these
files to the *root* of your repository:
 - .travis.yml: The script that tells Travis CI what to build.
 - dependencies.rosinstall: A wstool-generated list of source dependencies
   (optional). **Update the contents with your packages.**
 - catkin.options: Contents of this file are passed as arguments to catkin_make,
   for example package blacklists (optional).

Then, log on to travis-ci and turn on continuous integration for the repository:
 - travis-ci.org is free for open-source repositories.
 - travis-ci.com provides the same functionality for private repositories.

From then on, any push to this repository will trigger a new Travis-ci build.

# About Travis-CI

Travis provides a clean virtual machine for each build. The .travis.yml script
installs ROS, creates a workspace, resolves all given dependencies, and sets
environment variables (devel/setup.bash). Then, it compiles the entire ROS
workspace (ensuring there are no compilation errors), and runs any available
unittests. If any of the compilation/test phases fail, the build is marked as a
failure. Otherwise, it's a clean build.

For more information, see the Travis CI documentation:
http://docs.travis-ci.com/

# Handling Dependencies:

We handle two types of package dependencies:
  - packages (ros and otherwise) available through apt-get. These are installed
    using rosdep, based on the information in all the ROS package.xml files.
  - dependencies that must be checked out from source. These are handled by
    'wstool', and should be listed in a file named dependencies.rosinstall.  For
    example, depdendencies.rosinstall has a source dependency on a fork of the
    pocketsphinx package (you should remove this and replace it with your
    package dependencies). You should use the `https` url (not `ssh`) to
    check out the repository.

Note that any packages located inside your catkin workspace will take
precendence over the apt-get package (this allows you to use the cutting-edge
version of a package directly from github instead of what's available via
rosdep).

All dependencies should be handled in one of these fashions; you should not add
package dependencies directly to the .travis.yml file.

For public builds (i.e. when using travis-ci.org), `wstool` dependencies should
use a *public* access link (for instance, the https github address instead of
ssh). Otherwise you will get a "Permission denied (publickey)" error.

# ROS variables:

There are two variables you may want to change:
  - ROS_DISTRO (default is indigo): Note that packages must be available for
    ubuntu 14.04 trusty.
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

NOTE: This very much remains work-in-progress (i.e. experimental).

The instructions are generally listed here:
http://docs.travis-ci.com/user/private-dependencies/

1. Create a machine account on github.
2. Generate a public/private key on your computer, if not done already.
3. Add the public key (id_rsa.pub) to the machine account's github settings (see [here](https://developer.github.com/guides/managing-deploy-keys/#machine-users)).
4. In github, make sure the machine account has read access to all the dependency repositories.
5. In github, add the machine account as an administrator for the repository you want to build (note: not the dependencies).
6. In travis settings for the machine user, add the *private* key (id_rsa) in the build job settings.

# The example packages

These packages start simple and get more complicated, and serve as sample
packages to give Travis something to do. They're also examples of how to best
handle dependencies on other packages; both checking out from source.

* basic_ros_pkg: Just a simple C++ node.
* ros_pkg_with_tests: Includes both python and C++ tests
* ros_pkg_with_dependencies: Has dependencies in package.xml that must be
  resolved by wstool (e.g., clone pocketsphinx from source) and rosdep (e.g.,
  audio_common_msgs using apt-get).

You can look at the Travis build log to see exactly how it resolves dependencies
and then builds the package.