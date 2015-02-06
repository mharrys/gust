#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "uniform.hpp"

TEST(UniformTest, ValidateStateOperator)
{
    gst::Uniform uniform_invalid;
    EXPECT_FALSE(!!uniform_invalid);

    bool bool_data = true;
    gst::Uniform uniform_bool(bool_data);
    EXPECT_TRUE(!!uniform_bool);

    int int_data = 1;
    gst::Uniform uniform_int(int_data);
    EXPECT_TRUE(!!uniform_int);

    float float_data = 1.0f;
    gst::Uniform uniform_float(float_data);
    EXPECT_TRUE(!!uniform_float);

    std::vector<float> float_array_data = { 1.0f };
    gst::Uniform uniform_float_array(float_array_data);
    EXPECT_TRUE(!!uniform_float_array);

    glm::vec2 vec2_data(1.0f);
    gst::Uniform uniform_vec2(vec2_data);
    EXPECT_TRUE(!!uniform_vec2);

    glm::vec3 vec3_data(1.0f);
    gst::Uniform uniform_vec3(vec3_data);
    EXPECT_TRUE(!!uniform_vec3);

    glm::vec4 vec4_data(1.0f);
    gst::Uniform uniform_vec4(vec4_data);
    EXPECT_TRUE(!!uniform_vec4);

    glm::mat3 mat3_data(1.0f);
    gst::Uniform uniform_mat3(mat3_data);
    EXPECT_TRUE(!!uniform_mat3);

    glm::mat4 mat4_data(1.0f);
    gst::Uniform uniform_mat4(mat4_data);
    EXPECT_TRUE(!!uniform_mat4);
}
