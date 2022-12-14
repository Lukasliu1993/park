/*
 * SubmapIteratorTest.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: Péter Fankhauser
 *	 Institute: ETH Zurich, ANYbotics
 */

// Eigen
#include <Eigen/Core>

// gtest
#include <gtest/gtest.h>

// Limits
#include <cfloat>

// Vector
#include <vector>

#include <string>

#include "grid_map_core/iterators/SubmapIterator.hpp"
#include "grid_map_core/GridMap.hpp"


TEST(SubmapIterator, Simple)
{
  Eigen::Array2i submapTopLeftIndex(3, 1);
  Eigen::Array2i submapBufferSize(3, 2);
  Eigen::Array2i index;
  Eigen::Array2i submapIndex;

  std::vector<std::string> types;
  types.push_back("type");
  grid_map::GridMap map(types);
  map.setGeometry(Eigen::Array2d(8.1, 5.1), 1.0, Eigen::Vector2d(0.0, 0.0));  // bufferSize(8, 5)

  grid_map::SubmapIterator iterator(map, submapTopLeftIndex, submapBufferSize);

  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(submapTopLeftIndex(0), (*iterator)(0));
  EXPECT_EQ(submapTopLeftIndex(1), (*iterator)(1));
  EXPECT_EQ(0, iterator.getSubmapIndex()(0));
  EXPECT_EQ(0, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(3, (*iterator)(0));
  EXPECT_EQ(2, (*iterator)(1));
  EXPECT_EQ(0, iterator.getSubmapIndex()(0));
  EXPECT_EQ(1, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(4, (*iterator)(0));
  EXPECT_EQ(1, (*iterator)(1));
  EXPECT_EQ(1, iterator.getSubmapIndex()(0));
  EXPECT_EQ(0, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(4, (*iterator)(0));
  EXPECT_EQ(2, (*iterator)(1));
  EXPECT_EQ(1, iterator.getSubmapIndex()(0));
  EXPECT_EQ(1, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(5, (*iterator)(0));
  EXPECT_EQ(1, (*iterator)(1));
  EXPECT_EQ(2, iterator.getSubmapIndex()(0));
  EXPECT_EQ(0, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(5, (*iterator)(0));
  EXPECT_EQ(2, (*iterator)(1));
  EXPECT_EQ(2, iterator.getSubmapIndex()(0));
  EXPECT_EQ(1, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_TRUE(iterator.isPastEnd());
  EXPECT_EQ(5, (*iterator)(0));
  EXPECT_EQ(2, (*iterator)(1));
  EXPECT_EQ(2, iterator.getSubmapIndex()(0));
  EXPECT_EQ(1, iterator.getSubmapIndex()(1));
}

TEST(SubmapIterator, CircularBuffer)
{
  Eigen::Array2i submapTopLeftIndex(6, 3);
  Eigen::Array2i submapBufferSize(2, 4);
  Eigen::Array2i index;
  Eigen::Array2i submapIndex;

  std::vector<std::string> types;
  types.push_back("type");
  grid_map::GridMap map(types);
  // bufferSize(8, 5)
  map.setGeometry(grid_map::Length(8.1, 5.1), 1.0, grid_map::Position(0.0, 0.0));
  map.move(grid_map::Position(-3.0, -2.0));  // bufferStartIndex(3, 2)

  grid_map::SubmapIterator iterator(map, submapTopLeftIndex, submapBufferSize);

  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(submapTopLeftIndex(0), (*iterator)(0));
  EXPECT_EQ(submapTopLeftIndex(1), (*iterator)(1));
  EXPECT_EQ(0, iterator.getSubmapIndex()(0));
  EXPECT_EQ(0, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(6, (*iterator)(0));
  EXPECT_EQ(4, (*iterator)(1));
  EXPECT_EQ(0, iterator.getSubmapIndex()(0));
  EXPECT_EQ(1, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(6, (*iterator)(0));
  EXPECT_EQ(0, (*iterator)(1));
  EXPECT_EQ(0, iterator.getSubmapIndex()(0));
  EXPECT_EQ(2, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(6, (*iterator)(0));
  EXPECT_EQ(1, (*iterator)(1));
  EXPECT_EQ(0, iterator.getSubmapIndex()(0));
  EXPECT_EQ(3, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(7, (*iterator)(0));
  EXPECT_EQ(3, (*iterator)(1));
  EXPECT_EQ(1, iterator.getSubmapIndex()(0));
  EXPECT_EQ(0, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(7, (*iterator)(0));
  EXPECT_EQ(4, (*iterator)(1));
  EXPECT_EQ(1, iterator.getSubmapIndex()(0));
  EXPECT_EQ(1, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(7, (*iterator)(0));
  EXPECT_EQ(0, (*iterator)(1));
  EXPECT_EQ(1, iterator.getSubmapIndex()(0));
  EXPECT_EQ(2, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_FALSE(iterator.isPastEnd());
  EXPECT_EQ(7, (*iterator)(0));
  EXPECT_EQ(1, (*iterator)(1));
  EXPECT_EQ(1, iterator.getSubmapIndex()(0));
  EXPECT_EQ(3, iterator.getSubmapIndex()(1));

  ++iterator;
  EXPECT_TRUE(iterator.isPastEnd());
  EXPECT_EQ(7, (*iterator)(0));
  EXPECT_EQ(1, (*iterator)(1));
  EXPECT_EQ(1, iterator.getSubmapIndex()(0));
  EXPECT_EQ(3, iterator.getSubmapIndex()(1));
}
