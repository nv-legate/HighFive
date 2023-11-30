/*
 *  Copyright (c), 2017-2019, Blue Brain Project - EPFL
 *
 *  Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#include <string>

#include <catch2/catch_template_test_macros.hpp>

#include <highfive/highfive.hpp>
#include "tests_high_five.hpp"

using namespace HighFive;

TEMPLATE_TEST_CASE("Scalar in DataSet", "[Types]", bool, std::string) {
    const std::string file_name("rw_dataset_" + typeNameHelper<TestType>() + ".h5");
    const std::string dataset_name("dset");
    TestType t1{};

    {
        // Create a new file using the default property lists.
        File file(file_name, File::ReadWrite | File::Create | File::Truncate);

        // Create the dataset
        DataSet dataset =
            file.createDataSet(dataset_name,
                               DataSpace(1),
                               create_datatype<typename details::inspector<TestType>::base_type>());

        // Write into the initial part of the dataset
        dataset.write(t1);
    }

    // read it back
    {
        File file(file_name, File::ReadOnly);

        TestType value;
        DataSet dataset = file.getDataSet("/" + dataset_name);
        dataset.read(value);
        CHECK(t1 == value);
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Scalar in std::vector", "[Types]", std::vector, (bool, std::string)) {
    const std::string file_name("rw_dataset_" + typeNameHelper<TestType>() + ".h5");
    const std::string dataset_name("dset");
    TestType t1(5);

    {
        // Create a new file using the default property lists.
        File file(file_name, File::ReadWrite | File::Create | File::Truncate);

        // Create the dataset
        DataSet dataset = file.createDataSet(
            dataset_name, {5}, create_datatype<typename details::inspector<TestType>::base_type>());

        // Write into the initial part of the dataset
        dataset.write(t1);
    }

    // read it back
    {
        File file(file_name, File::ReadOnly);

        TestType value;
        DataSet dataset = file.getDataSet("/" + dataset_name);
        dataset.read(value);
        CHECK(t1 == value);
        CHECK(value.size() == 5);
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Scalar in std::vector<std::vector>",
                           "[Types]",
                           std::vector,
                           (bool, std::string)) {
    const std::string file_name("rw_dataset_vector_" + typeNameHelper<TestType>() + ".h5");
    const std::string dataset_name("dset");
    std::vector<TestType> t1(5);
    for (auto&& e: t1) {
        e.resize(6);
    }

    {
        // Create a new file using the default property lists.
        File file(file_name, File::ReadWrite | File::Create | File::Truncate);

        // Create the dataset
        DataSet dataset = file.createDataSet(
            dataset_name,
            {5, 6},
            create_datatype<typename details::inspector<std::vector<TestType>>::base_type>());

        // Write into the initial part of the dataset
        dataset.write(t1);
    }

    // read it back
    {
        File file(file_name, File::ReadOnly);

        std::vector<TestType> value;
        DataSet dataset = file.getDataSet("/" + dataset_name);
        dataset.read(value);
        CHECK(t1 == value);
        CHECK(value.size() == 5);
    }
}

TEMPLATE_TEST_CASE("Scalar in std::array", "[Types]", bool, std::string) {
    const std::string file_name("rw_dataset_array_" + typeNameHelper<TestType>() + ".h5");
    const std::string dataset_name("dset");
    std::array<TestType, 5> t1{};

    {
        // Create a new file using the default property lists.
        File file(file_name, File::ReadWrite | File::Create | File::Truncate);

        // Create the dataset
        DataSet dataset = file.createDataSet(
            dataset_name,
            {5},
            create_datatype<typename details::inspector<std::array<TestType, 5>>::base_type>());

        // Write into the initial part of the dataset
        dataset.write(t1);
    }

    // read it back
    {
        File file(file_name, File::ReadOnly);

        std::array<TestType, 5> value;
        DataSet dataset = file.getDataSet("/" + dataset_name);
        dataset.read(value);
        CHECK(t1 == value);
        CHECK(value.size() == 5);
    }
}

TEMPLATE_TEST_CASE("Scalar in std::vector<std::array>", "[Types]", bool, std::string) {
    const std::string file_name("rw_dataset_vector_array_" + typeNameHelper<TestType>() + ".h5");
    const std::string dataset_name("dset");
    std::vector<std::array<TestType, 6>> t1(5);

    {
        // Create a new file using the default property lists.
        File file(file_name, File::ReadWrite | File::Create | File::Truncate);

        // Create the dataset
        DataSet dataset = file.createDataSet(
            dataset_name,
            {5, 6},
            create_datatype<
                typename details::inspector<std::vector<std::array<TestType, 5>>>::base_type>());

        // Write into the initial part of the dataset
        dataset.write(t1);
    }

    // read it back
    {
        File file(file_name, File::ReadOnly);

        std::vector<std::array<TestType, 6>> value;
        DataSet dataset = file.getDataSet("/" + dataset_name);
        dataset.read(value);
        CHECK(t1 == value);
        CHECK(value.size() == 5);
    }
}

TEMPLATE_TEST_CASE("Scalar in std::array<std::vector>", "[Types]", bool, std::string) {
    const std::string file_name("rw_dataset_array_vector" + typeNameHelper<TestType>() + ".h5");
    const std::string dataset_name("dset");
    std::array<std::vector<TestType>, 6> t1;
    for (auto& tt: t1) {
        tt = std::vector<TestType>(5);
    }

    {
        // Create a new file using the default property lists.
        File file(file_name, File::ReadWrite | File::Create | File::Truncate);

        // Create the dataset
        DataSet dataset = file.createDataSet(
            dataset_name,
            {6, 5},
            create_datatype<
                typename details::inspector<std::vector<std::array<TestType, 5>>>::base_type>());

        // Write into the initial part of the dataset
        dataset.write(t1);
    }

    // read it back
    {
        File file(file_name, File::ReadOnly);

        std::array<std::vector<TestType>, 6> value;
        DataSet dataset = file.getDataSet("/" + dataset_name);
        dataset.read(value);
        CHECK(t1 == value);
        CHECK(value.size() == 6);
    }
}

#if HIGHFIVE_CXX_STD >= 17
TEMPLATE_PRODUCT_TEST_CASE("Scalar in std::vector<std::byte>", "[Types]", std::vector, std::byte) {
    const std::string file_name("rw_dataset_vector_" + typeNameHelper<TestType>() + ".h5");
    const std::string dataset_name("dset");
    TestType t1(5, std::byte(0xCD));

    {
        // Create a new file using the default property lists.
        File file(file_name, File::ReadWrite | File::Create | File::Truncate);

        // Create the dataset
        DataSet dataset = file.createDataSet(dataset_name, {5}, create_datatype<std::byte>());

        // Write into the initial part of the dataset
        dataset.write(t1);
    }

    // read it back
    {
        File file(file_name, File::ReadOnly);

        TestType value(5, std::byte(0xCD));
        DataSet dataset = file.getDataSet("/" + dataset_name);
        dataset.read(value);
        CHECK(t1 == value);
        CHECK(value.size() == 5);
    }
}
#endif
