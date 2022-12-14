/*
 * test_grid_map_sdf.cpp
 *
 *  Created on: Aug 28, 2017
 *      Author: Péter Fankhauser
 *	 Institute: ETH Zurich, ANYbotics
 */

// gtest
#include <gtest/gtest.h>

// Run all the tests that were declared with TEST()
int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  srand(static_cast<int>(time(0)));
  return RUN_ALL_TESTS();
}
