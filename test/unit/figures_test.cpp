/*
 * figures_test.cpp - Unit testing for the cpplot library
 *
 * References:
 *
 *   [1]
 *
 * Future Improvements:
 *
 *   [1]
 *
 * Author:              Tom Clark  (thclark@github)
 *
 * Copyright (c) 2017-8 T Clark. All Rights Reserved.
 *
 */

#define BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED

#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include <boost/stacktrace.hpp>
#include <boost/filesystem.hpp>
#include "figures.h"
#include "eigen.h"
#include "exceptions.h"
#include "gtest/gtest.h"
#include "glog/logging.h"


using namespace Eigen;
using namespace google;
using namespace plotly;


// TODO inherit from a base test class
class FigureTest : public ::testing::Test {

protected:

    /* Returns environment variable TEST_DATA_DIR, which contains a system-dependent path to a directory where test
     * fixture data may be stored, and which may be used to write output test files. If no environment variable is set,
     * defaults to the current working directory in which the test framework is being run.
     * A trailing slash is always appended.
     */
    std::string TestDataDir() {

        const char *tmp = std::getenv("TEST_DATA_DIR");
        std::string test_data_dir;
        if (tmp) {
            std::string s(tmp);
            test_data_dir = s;
        } else {
            boost::filesystem::path cwd(boost::filesystem::current_path());
            test_data_dir = cwd.string();
        }
        if (!boost::algorithm::ends_with(test_data_dir, "/")) {
            test_data_dir.append("/");
        }

        return test_data_dir;
    }

    // Define the matrix output format for this set of tests
    IOFormat test_format;

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right before each test)

        IOFormat debug_format(FullPrecision, 0, ", ", ";\n", "", "", "[", "]");
        test_format = debug_format;

    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right before the destructor)
    }

};


TEST_F(FigureTest, test_bar_plot) {

    BarPlot p = BarPlot();
    Figure fig = Figure();
    fig.add(p);
    std::cout << "Writing to TestDataDir(): " << TestDataDir() << std::endl;
    fig.write(TestDataDir().append("test_bar_plot.json"));

}


TEST_F(FigureTest, test_scatter_plot) {

    ScatterPlot p = ScatterPlot();
    Figure fig = Figure();
    fig.add(p);
    fig.write(TestDataDir().append("test_scatter_plot.json"));

}


TEST_F(FigureTest, test_bar_and_scatter_plot) {

    Figure fig = Figure();
    BarPlot p1 = BarPlot();
    fig.add(p1);
    ScatterPlot p2 = ScatterPlot();
    fig.add(p2);
    std::cout << "Writing to TestDataDir(): " << TestDataDir() << std::endl;
    fig.write(TestDataDir().append("test_bar_and_scatter_plot.json"));

}


TEST_F(FigureTest, test_eigen_serialiser) {

    nlohmann::json j;

    Eigen::ArrayXd arr1(5);
    arr1 << 0.001, 0.1, 0.3, 0.6, 1.0;
    nlohmann::json j1;
    to_json(j1, arr1);
    j["array1"] = j1;

    // NB Eigen uses column major indexing, but you have to init arrays in a row major way.
    Eigen::ArrayXXd arr2(5,2);
    arr2 << 0.0, 0.1,
            1.0, 1.1,
            2.0, 2.1,
            3.0, 3.1,
            4.0, 4.1;
    nlohmann::json j2;
    to_json(j2, arr2);
    j["array2"] = j2;
    std::cout << "array 0,1: " << arr2(0,1) << std::endl;
    std::cout << "array 1,0: " << arr2(1,0) << std::endl;

    std::cout << j.dump() << std::endl;
    EXPECT_EQ(j.dump(), "{\"array1\":[0.001,0.1,0.3,0.6,1],\"array2\":[[0,0.1],[1,1.1],[2,2.1],[3,3.1],[4,4.1]]}");

}

//// Test the osstream operator works. Bloody thing.
//TEST_F(FigureTest, test_figure_ostream) {
//
//    // Example bar chart
//    BarPlot p = BarPlot();
//    std::cout << p.toJson() << std::endl;
//
//    // Send to plotly for rendering
//    Figure<BarPlot> fig = Figure<BarPlot>(p);
//
//    std::cout << fig << std::endl;
//
//}
