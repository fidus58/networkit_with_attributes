/*
 * AttributeTest.cpp
 *
 *  Created on: 26.02.2022
 *      Author: Klaus Ahrens
 */

#include <iostream>

#include <gtest/gtest.h>

#include <networkit/graph/Graph.hpp>

namespace NetworKit {

class AttributeTest : public testing::Test {};

TEST_F(AttributeTest, testSetGetOnExistingNodes) {

    Graph graph = Graph(15);

    auto intAttr = graph.nodeAttributes().attach<int>("some int attribute");

    // set / get
    for (node n=0; n<graph.numberOfNodes(); ++n)
	intAttr.set(n, int(n));

    for (node n=0; n<graph.numberOfNodes(); ++n) {
	int got = intAttr.get(n);
	EXPECT_EQ(got, int(n));
    }
    // by index proxy	
    for (node n=0; n<graph.numberOfNodes(); ++n)
        intAttr[n] = int(n);
    
    for (node n=0; n<graph.numberOfNodes(); ++n) {
	int got = intAttr[n];
        EXPECT_EQ(got, int(n));
    }
}

TEST_F(AttributeTest, testSetGetOnNonExistingNodes) {

    Graph graph = Graph(5);

    graph.removeNode(3);

    auto intAttr = graph.nodeAttributes().attach<int>("some int attribute");

    EXPECT_FALSE(graph.hasNode(5));
    EXPECT_THROW(intAttr.set(5, 5), std::runtime_error);
    EXPECT_THROW(intAttr.get(5),    std::runtime_error);
    EXPECT_THROW(intAttr[5] = 5,    std::runtime_error);
    EXPECT_THROW(int i = intAttr[5],std::runtime_error);

    EXPECT_FALSE(graph.hasNode(3));
    EXPECT_THROW(intAttr.set(3, 3), std::runtime_error);
    EXPECT_THROW(intAttr.get(3),    std::runtime_error);
    EXPECT_THROW(intAttr[3] = 3,    std::runtime_error);
    EXPECT_THROW(int i= intAttr[3], std::runtime_error);
}
} // namespace NetworKit
