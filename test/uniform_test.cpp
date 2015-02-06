#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "uniform.hpp"

// Tests operator for validating uniform (if it has shadowed data or not)
TEST(UniformTest, ValidateStateOperator)
{
    gst::Uniform uniform_invalid;
    EXPECT_FALSE(!!uniform_invalid);

    const bool bool_data = true;
    gst::Uniform uniform_bool(bool_data);
    EXPECT_TRUE(!!uniform_bool);

    const int int_data = 1;
    gst::Uniform uniform_int(int_data);
    EXPECT_TRUE(!!uniform_int);

    const float float_data = 1.0f;
    gst::Uniform uniform_float(float_data);
    EXPECT_TRUE(!!uniform_float);

    std::vector<float> float_array_data = { 1.0f };
    gst::Uniform uniform_float_array(float_array_data);
    EXPECT_TRUE(!!uniform_float_array);

    const glm::vec2 vec2_data(1.0f);
    gst::Uniform uniform_vec2(vec2_data);
    EXPECT_TRUE(!!uniform_vec2);

    const glm::vec3 vec3_data(1.0f);
    gst::Uniform uniform_vec3(vec3_data);
    EXPECT_TRUE(!!uniform_vec3);

    const glm::vec4 vec4_data(1.0f);
    gst::Uniform uniform_vec4(vec4_data);
    EXPECT_TRUE(!!uniform_vec4);

    const glm::mat3 mat3_data(1.0f);
    gst::Uniform uniform_mat3(mat3_data);
    EXPECT_TRUE(!!uniform_mat3);

    const glm::mat4 mat4_data(1.0f);
    gst::Uniform uniform_mat4(mat4_data);
    EXPECT_TRUE(!!uniform_mat4);
}

// Tests if uniform is equal or not based on its shadowed data
TEST(UniformTest, ValidateComparisonOperator)
{
    const int int_data_a = 13;
    const int int_data_b = 37;
    gst::Uniform uniform_int_a(int_data_a);
    gst::Uniform uniform_int_b(int_data_b);

    EXPECT_EQ(uniform_int_a, uniform_int_a);
    EXPECT_NE(uniform_int_a, uniform_int_b);
    // we compare pointer and not value of pointer
    EXPECT_NE(uniform_int_a, gst::Uniform(int_data_a));
}

// Tests if the shadowed data is allocated correctly and that its description
// is correctly defined
TEST(UniformTest, ShadowedDataAllocation)
{
    float * data;

    const bool bool_data = true;
    gst::Uniform uniform_bool(bool_data);
    EXPECT_EQ(gst::UniformType::BOOL, uniform_bool.get_type());
    EXPECT_EQ(1, uniform_bool.get_count());
    EXPECT_EQ(bool_data, *uniform_bool.get_bool().get());
    EXPECT_EQ(sizeof(bool), uniform_bool.get_bytes());

    const int int_data = 42;
    gst::Uniform uniform_int(int_data);
    EXPECT_EQ(gst::UniformType::INT, uniform_int.get_type());
    EXPECT_EQ(1, uniform_int.get_count());
    EXPECT_EQ(int_data, *uniform_int.get_int().get());
    EXPECT_EQ(sizeof(int), uniform_int.get_bytes());

    const float float_data = 42.0f;
    gst::Uniform uniform_float(float_data);
    EXPECT_EQ(gst::UniformType::FLOAT, uniform_float.get_type());
    EXPECT_EQ(1, uniform_float.get_count());
    EXPECT_FLOAT_EQ(float_data, *uniform_float.get_float().get());
    EXPECT_EQ(sizeof(float), uniform_float.get_bytes());

    std::vector<float> float_array_data = { 13.0f, 37.0f, 42.0f };
    gst::Uniform uniform_float_array(float_array_data);
    EXPECT_EQ(gst::UniformType::FLOAT_ARRAY, uniform_float_array.get_type());
    EXPECT_EQ(float_array_data.size(), uniform_float_array.get_count());
    data = uniform_float_array.get_float().get();
    for (unsigned int i = 0; i < float_array_data.size(); i++) {
        EXPECT_FLOAT_EQ(float_array_data[i], data[i]);
    }
    EXPECT_EQ(float_array_data.size() * sizeof(float), uniform_float_array.get_bytes());

    const glm::vec2 vec2_data(1.0f, 2.0f);
    gst::Uniform uniform_vec2(vec2_data);
    EXPECT_EQ(gst::UniformType::VEC2, uniform_vec2.get_type());
    EXPECT_EQ(2, uniform_vec2.get_count());
    data = uniform_vec2.get_float().get();
    for (unsigned int i = 0; i < 2; i++) {
        EXPECT_FLOAT_EQ(vec2_data[i], data[i]);
    }
    EXPECT_EQ(2 * sizeof(float), uniform_vec2.get_bytes());

    const glm::vec3 vec3_data(1.0f, 2.0f, 3.0f);
    gst::Uniform uniform_vec3(vec3_data);
    EXPECT_EQ(gst::UniformType::VEC3, uniform_vec3.get_type());
    EXPECT_EQ(3, uniform_vec3.get_count());
    data = uniform_vec3.get_float().get();
    for (unsigned int i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(vec3_data[i], data[i]);
    }
    EXPECT_EQ(3 * sizeof(float), uniform_vec3.get_bytes());

    const glm::vec4 vec4_data(1.0f, 2.0f, 3.0f, 4.0f);
    gst::Uniform uniform_vec4(vec4_data);
    EXPECT_EQ(gst::UniformType::VEC4, uniform_vec4.get_type());
    EXPECT_EQ(4, uniform_vec4.get_count());
    data = uniform_vec4.get_float().get();
    for (unsigned int i = 0; i < 4; i++) {
        EXPECT_FLOAT_EQ(vec4_data[i], data[i]);
    }
    EXPECT_EQ(4 * sizeof(float), uniform_vec4.get_bytes());

    const glm::mat3 mat3_data;
    gst::Uniform uniform_mat3(mat3_data);
    EXPECT_EQ(gst::UniformType::MAT3, uniform_mat3.get_type());
    EXPECT_EQ(9, uniform_mat3.get_count());
    data = uniform_mat3.get_float().get();
    for (unsigned int i = 0; i < 9; i++) {
        EXPECT_FLOAT_EQ(glm::value_ptr(mat3_data)[i], data[i]);
    }
    EXPECT_EQ(9 * sizeof(float), uniform_mat3.get_bytes());

    const glm::mat4 mat4_data;
    gst::Uniform uniform_mat4(mat4_data);
    EXPECT_EQ(gst::UniformType::MAT4, uniform_mat4.get_type());
    EXPECT_EQ(16, uniform_mat4.get_count());
    data = uniform_mat4.get_float().get();
    for (unsigned int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(glm::value_ptr(mat4_data)[i], data[i]);
    }
    EXPECT_EQ(16 * sizeof(float), uniform_mat4.get_bytes());
}

// Tests if shadowed data is updated correctly when changed
TEST(UniformTest, UpdateShadowedData)
{
    float * data;

    // simple swap
    const int int_data_a = 13;
    const int int_data_b = 37;
    gst::Uniform uniform_int(int_data_a);
    EXPECT_EQ(int_data_a, *uniform_int.get_int().get());
    uniform_int = int_data_b;
    EXPECT_EQ(int_data_b, *uniform_int.get_int().get());

    // vector element swap and add new element
    std::vector<float> float_array_data = { 13.0f, 37.0f };
    gst::Uniform uniform_float_array(float_array_data);
    float_array_data[0] = 42.0f;
    uniform_float_array = float_array_data;
    data = uniform_float_array.get_float().get();
    for (unsigned int i = 0; i < float_array_data.size(); i++) {
        EXPECT_FLOAT_EQ(float_array_data[i], data[i]);
    }
    float_array_data.push_back(1337.0f);
    uniform_float_array = float_array_data;
    data = uniform_float_array.get_float().get();
    for (unsigned int i = 0; i < float_array_data.size(); i++) {
        EXPECT_FLOAT_EQ(float_array_data[i], data[i]);
    }

    // change data type
    const bool bool_data = true;
    const glm::vec3 vec3_data;
    gst::Uniform uniform_dynamic(bool_data);
    uniform_dynamic = vec3_data;
    EXPECT_EQ(gst::UniformType::VEC3, uniform_dynamic.get_type());
    EXPECT_EQ(3, uniform_dynamic.get_count());
    data = uniform_dynamic.get_float().get();
    for (unsigned int i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(vec3_data[i], data[i]);
    }
    EXPECT_EQ(3 * sizeof(float), uniform_dynamic.get_bytes());
}
