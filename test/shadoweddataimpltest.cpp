#include "shadoweddataimpl.hpp"

#include "gmock/gmock.h"

static std::vector<float> create_random_float_vector(
    unsigned int num_elements,
    int min,
    int max)
{
    std::random_device device;
    std::default_random_engine engine(device());
    std::uniform_real_distribution<float> uniform_dist(min, max);
    std::vector<float> result;
    for (unsigned int i = 0; i < num_elements; i++) {
        result.push_back(uniform_dist(engine));
    }
    return result;
}

static std::vector<int> create_random_int_vector(
    unsigned int num_elements,
    int min,
    int max)
{
    auto v = create_random_float_vector(num_elements, min, max);
    return std::vector<int>(v.begin(), v.end());
}

static std::vector<unsigned int> create_random_unsigned_int_vector(
    unsigned int num_elements,
    int max)
{
    auto v = create_random_float_vector(num_elements, 0, max);
    return std::vector<unsigned int>(v.begin(), v.end());
}

template<typename T>
static std::vector<T> create_random_vec_vector(
    unsigned int num_elements,
    int min,
    int max,
    unsigned int components)
{
    auto r = create_random_float_vector(num_elements, min, max);
    std::vector<T> v;
    for (unsigned int i = 0; i < r.size(); i += components) {
        T data;
        for (unsigned int j = 0; j < components; j++) {
            data[j] = r[i];
        }
        v.push_back(data);
    }
    return v;
}

TEST(ShadowedDataImplTest, NoDataTypeWhenCreated)
{
    gst::ShadowedDataImpl shadowed_data;
    ASSERT_EQ(gst::DataType::NONE, shadowed_data.get_type());
}

TEST(ShadowedDataImplTest, SetAndGetBool)
{
    gst::ShadowedDataImpl shadowed_data;

    for (auto expected : { false, true }) {
        shadowed_data.set_bool(expected);
        auto actual = shadowed_data.get_bool();
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetInt)
{
    gst::ShadowedDataImpl shadowed_data;

    for (auto expected : create_random_int_vector(1000, -10, 10)) {
        shadowed_data.set_int(expected);
        auto actual = shadowed_data.get_int();
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetUnsignedInt)
{
    gst::ShadowedDataImpl shadowed_data;

    for (auto expected : create_random_unsigned_int_vector(1000, 10)) {
        shadowed_data.set_unsigned_int(expected);
        auto actual = shadowed_data.get_unsigned_int();
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetFloat)
{
    gst::ShadowedDataImpl shadowed_data;

    for (auto expected : create_random_float_vector(1000, -10.0f, 10.0f)) {
        shadowed_data.set_float(expected);
        auto actual = shadowed_data.get_float();
        EXPECT_FLOAT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec2)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        glm::vec2(),
        glm::vec2(1.0f, 2.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec2(expected);
        auto actual = shadowed_data.get_vec2();
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec3)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        glm::vec3(),
        glm::vec3(1.0f, 2.0f, 3.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec3(expected);
        auto actual = shadowed_data.get_vec3();
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec4)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        glm::vec4(),
        glm::vec4(1.0f, 2.0f, 3.0f, 4.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec4(expected);
        auto actual = shadowed_data.get_vec4();
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetMat3)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        glm::mat3(),
        glm::mat3(42.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_mat3(expected);
        auto actual = shadowed_data.get_mat3();
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetMat4)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        glm::mat4(),
        glm::mat4(42.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_mat4(expected);
        auto actual = shadowed_data.get_mat4();
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetIntArray)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<int>{},
        std::vector<int>{ 42 },
        create_random_int_vector(1000, -10, 10),
        // invoke copy values since same size as previous
        create_random_int_vector(1000, -10, 10),
    };

    for (auto expected : test_data) {
        shadowed_data.set_int_array(expected);
        auto actual = shadowed_data.get_int_array();
        EXPECT_THAT(expected, ::testing::ContainerEq(actual));
    }
}

TEST(ShadowedDataImplTest, SetAndGetUnsignedIntArray)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<unsigned int>{},
        std::vector<unsigned int>{ 42 },
        create_random_unsigned_int_vector(1000, 10),
        // invoke copy values since same size as previous
        create_random_unsigned_int_vector(1000, 10),
    };

    for (auto expected : test_data) {
        shadowed_data.set_unsigned_int_array(expected);
        auto actual = shadowed_data.get_unsigned_int_array();
        EXPECT_THAT(expected, ::testing::ContainerEq(actual));
    }
}

TEST(ShadowedDataImplTest, SetAndGetFloatArray)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<float>{},
        std::vector<float>{ 42.0f },
        create_random_float_vector(1000, -10.0f, 10.0f),
        // invoke copy values since same size as previous
        create_random_float_vector(1000, -10.0f, 10.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_float_array(expected);
        auto actual = shadowed_data.get_float_array();
        EXPECT_THAT(expected, ::testing::ContainerEq(actual));
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec2Array)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<glm::vec2>{},
        std::vector<glm::vec2>{ glm::vec2(42.0f) },
        create_random_vec_vector<glm::vec2>(1000, -10.0f, 10.0f, 2),
        // invoke copy values since same size as previous
        create_random_vec_vector<glm::vec2>(1000, -10.0f, 10.0f, 2),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec2_array(expected);
        auto actual = shadowed_data.get_vec2_array();
        EXPECT_THAT(expected, ::testing::ContainerEq(actual));
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec3Array)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<glm::vec3>{},
        std::vector<glm::vec3>{ glm::vec3(42.0f) },
        create_random_vec_vector<glm::vec3>(1000, -10.0f, 10.0f, 3),
        // invoke copy values since same size as previous
        create_random_vec_vector<glm::vec3>(1000, -10.0f, 10.0f, 3),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec3_array(expected);
        auto actual = shadowed_data.get_vec3_array();
        EXPECT_THAT(expected, ::testing::ContainerEq(actual));
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec4Array)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<glm::vec4>{},
        std::vector<glm::vec4>{ glm::vec4(42.0f) },
        create_random_vec_vector<glm::vec4>(1000, -10.0f, 10.0f, 4),
        // invoke copy values since same size as previous
        create_random_vec_vector<glm::vec4>(1000, -10.0f, 10.0f, 4),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec4_array(expected);
        auto actual = shadowed_data.get_vec4_array();
        EXPECT_THAT(expected, ::testing::ContainerEq(actual));
    }
}

TEST(ShadowedDataImplTest, DataTypeReflectsDataStorage)
{
    gst::ShadowedDataImpl shadowed_data;

    shadowed_data.set_bool(false);
    EXPECT_EQ(gst::DataType::BOOL, shadowed_data.get_type());

    shadowed_data.set_int(0);
    EXPECT_EQ(gst::DataType::INT, shadowed_data.get_type());

    shadowed_data.set_unsigned_int(0);
    EXPECT_EQ(gst::DataType::UNSIGNED_INT, shadowed_data.get_type());

    shadowed_data.set_float(0.0f);
    EXPECT_EQ(gst::DataType::FLOAT, shadowed_data.get_type());

    shadowed_data.set_vec2(glm::vec2());
    EXPECT_EQ(gst::DataType::VEC2, shadowed_data.get_type());

    shadowed_data.set_vec3(glm::vec3());
    EXPECT_EQ(gst::DataType::VEC3, shadowed_data.get_type());

    shadowed_data.set_vec4(glm::vec4());
    EXPECT_EQ(gst::DataType::VEC4, shadowed_data.get_type());

    shadowed_data.set_mat3(glm::mat3());
    EXPECT_EQ(gst::DataType::MAT3, shadowed_data.get_type());

    shadowed_data.set_mat4(glm::mat4());
    EXPECT_EQ(gst::DataType::MAT4, shadowed_data.get_type());

    shadowed_data.set_int_array({});
    EXPECT_EQ(gst::DataType::INT_ARRAY, shadowed_data.get_type());

    shadowed_data.set_unsigned_int_array({});
    EXPECT_EQ(gst::DataType::UNSIGNED_INT_ARRAY, shadowed_data.get_type());

    shadowed_data.set_float_array({});
    EXPECT_EQ(gst::DataType::FLOAT_ARRAY, shadowed_data.get_type());

    shadowed_data.set_vec2_array({});
    EXPECT_EQ(gst::DataType::VEC2_ARRAY, shadowed_data.get_type());

    shadowed_data.set_vec3_array({});
    EXPECT_EQ(gst::DataType::VEC3_ARRAY, shadowed_data.get_type());

    shadowed_data.set_vec4_array({});
    EXPECT_EQ(gst::DataType::VEC4_ARRAY, shadowed_data.get_type());
}
