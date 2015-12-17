#!/usr/bin/env python

import unittest
import rospy
import rostest
import numpy as np

from scripts.double import double

class TestCase(unittest.TestCase):

    def test_four(self):
        ret = double(4)
        self.assertEqual(8, ret)

    def test_two(self):
        ret = double(2)
        self.assertEqual(4, ret)

    def test_good_math(self):
        ret = double(3)
        self.assertEqual(6, ret)

    def test_double_vector(self):
        x = np.array([2, 5])
        ret = double(x)
        ref = np.array([4, 10])
        self.assertTrue(np.array_equal(ref, ret))


if __name__ == '__main__':
    rostest.rosrun('package_name', 'test_name', TestCase)
