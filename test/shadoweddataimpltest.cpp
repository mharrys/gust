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

TEST(ShadowedDataImplTest, NoDataTypeWhenCreated)
{
    gst::ShadowedDataImpl shadowed_data;
    ASSERT_EQ(gst::DataType::NONE, shadowed_data.get_type());
}

TEST(ShadowedDataImplTest, SetAndGetBool)
{
    gst::ShadowedDataImpl shadowed_data;

    for (auto expected : { false, true, true, false }) {
        shadowed_data.set_bool(expected);
        EXPECT_EQ(1, shadowed_data.get_count());
        auto actual = static_cast<int const *>(shadowed_data.get_data());
        EXPECT_EQ(expected, *actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetInt)
{
    gst::ShadowedDataImpl shadowed_data;

    for (auto expected : create_random_int_vector(1000, -10, 10)) {
        shadowed_data.set_int(expected);
        EXPECT_EQ(1, shadowed_data.get_count());
        auto actual = static_cast<int const *>(shadowed_data.get_data());
        EXPECT_EQ(expected, *actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetUnsignedInt)
{
    gst::ShadowedDataImpl shadowed_data;

    for (auto expected : create_random_unsigned_int_vector(1000, 10)) {
        shadowed_data.set_unsigned_int(expected);
        EXPECT_EQ(1, shadowed_data.get_count());
        auto actual = static_cast<unsigned int const *>(shadowed_data.get_data());
        EXPECT_EQ(expected, *actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetFloat)
{
    gst::ShadowedDataImpl shadowed_data;

    for (auto expected : create_random_float_vector(1000, -10.0f, 10.0f)) {
        shadowed_data.set_float(expected);
        EXPECT_EQ(1, shadowed_data.get_count());
        auto actual = static_cast<float const *>(shadowed_data.get_data());
        EXPECT_FLOAT_EQ(expected, *actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec2)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        glm::vec2(),
        glm::vec2(1.0f, 2.0f),
        // invoke copy values since same size as previous but with different values
        glm::vec2(3.0f, 4.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec2(expected);
        EXPECT_EQ(1, shadowed_data.get_count());
        auto actual = glm::make_vec2(static_cast<float const *>(shadowed_data.get_data()));
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec3)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        glm::vec3(),
        glm::vec3(1.0f, 2.0f, 3.0f),
        // invoke copy values since same size as previous but with different values
        glm::vec3(4.0f, 5.0f, 6.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec3(expected);
        EXPECT_EQ(1, shadowed_data.get_count());
        auto actual = glm::make_vec3(static_cast<float const *>(shadowed_data.get_data()));
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec4)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        glm::vec4(),
        glm::vec4(1.0f, 2.0f, 3.0f, 4.0f),
        // invoke copy values since same size as previous but with different values
        glm::vec4(5.0f, 6.0f, 7.0f, 8.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec4(expected);
        EXPECT_EQ(1, shadowed_data.get_count());
        auto actual = glm::make_vec4(static_cast<float const *>(shadowed_data.get_data()));
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetMat3)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        glm::mat3(),
        glm::mat3(42.0f),
        // invoke copy values since same size as previous but with different values
        glm::mat3(24.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_mat3(expected);
        EXPECT_EQ(1, shadowed_data.get_count());
        auto actual = glm::make_mat3(static_cast<float const *>(shadowed_data.get_data()));
        EXPECT_EQ(expected, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetMat4)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        glm::mat4(),
        glm::mat4(42.0f),
        // invoke copy values since same size as previous but with different values
        glm::mat4(24.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_mat4(expected);
        EXPECT_EQ(1, shadowed_data.get_count());
        auto actual = glm::make_mat4(static_cast<float const *>(shadowed_data.get_data()));
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
        // invoke copy values since same size as previous but with different values
        create_random_int_vector(1000, -10, 10),
    };

    for (auto expected : test_data) {
        shadowed_data.set_int_array(expected);
        auto actual = static_cast<int const *>(shadowed_data.get_data());
        for (unsigned int i = 0; i < expected.size(); i++) {
            EXPECT_EQ(expected[i], actual[i]);
        }
    }
}

TEST(ShadowedDataImplTest, SetAndGetUnsignedIntArray)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<unsigned int>{},
        std::vector<unsigned int>{ 42 },
        create_random_unsigned_int_vector(1000, 10),
        // invoke copy values since same size as previous but with different values
        create_random_unsigned_int_vector(1000, 10),
    };

    for (auto expected : test_data) {
        shadowed_data.set_unsigned_int_array(expected);
        auto actual = static_cast<unsigned int const *>(shadowed_data.get_data());
        for (unsigned int i = 0; i < expected.size(); i++) {
            EXPECT_EQ(expected[i], actual[i]);
        }
    }
}

TEST(ShadowedDataImplTest, SetAndGetFloatArray)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<float>{},
        std::vector<float>{ 42.0f },
        create_random_float_vector(1000, -10.0f, 10.0f),
        // invoke copy values since same size as previous but with different values
        create_random_float_vector(1000, -10.0f, 10.0f),
    };

    for (auto expected : test_data) {
        shadowed_data.set_float_array(expected);
        auto actual = static_cast<float const *>(shadowed_data.get_data());
        for (unsigned int i = 0; i < expected.size(); i++) {
            EXPECT_FLOAT_EQ(expected[i], actual[i]);
        }
    }
}

template<typename T>
static std::vector<T> create_random_glm_vector(
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
            glm::value_ptr(data)[j] = r[i];
        }
        v.push_back(data);
    }
    return v;
}

template<typename T>
static void compare_glm_array(std::vector<T> expected, unsigned int components, float const * actual)
{
    for (unsigned int i = 0; i < expected.size(); i++) {
        for (unsigned int j = 0; j < components; j++) {
            auto index = i * components + j;
            EXPECT_FLOAT_EQ(glm::value_ptr(expected[i])[j], actual[index]);
        }
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec2Array)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<glm::vec2>{},
        std::vector<glm::vec2>{ glm::vec2(1.0f, 2.0f) },
        create_random_glm_vector<glm::vec2>(1000, -10.0f, 10.0f, 2),
        // invoke copy values since same size as previous but with different values
        create_random_glm_vector<glm::vec2>(1000, -10.0f, 10.0f, 2),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec2_array(expected);
        auto actual = static_cast<float const *>(shadowed_data.get_data());
        compare_glm_array(expected, 2, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec3Array)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<glm::vec3>{},
        std::vector<glm::vec3>{ glm::vec3(1.0f, 2.0f, 3.0f) },
        create_random_glm_vector<glm::vec3>(1000, -10.0f, 10.0f, 3),
        // invoke copy values since same size as previous but with different values
        create_random_glm_vector<glm::vec3>(1000, -10.0f, 10.0f, 3),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec3_array(expected);
        auto actual = static_cast<float const *>(shadowed_data.get_data());
        compare_glm_array(expected, 3, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetVec4Array)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<glm::vec4>{},
        std::vector<glm::vec4>{ glm::vec4(1.0f, 2.0f, 3.0f, 4.0f) },
        create_random_glm_vector<glm::vec4>(1000, -10.0f, 10.0f, 4),
        // invoke copy values since same size as previous but with different values
        create_random_glm_vector<glm::vec4>(1000, -10.0f, 10.0f, 4),
    };

    for (auto expected : test_data) {
        shadowed_data.set_vec4_array(expected);
        auto actual = static_cast<float const *>(shadowed_data.get_data());
        compare_glm_array(expected, 4, actual);
    }
}

template<typename T>
static std::vector<T> create_random_mat_vector(
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
            glm::value_ptr(data)[j] = r[i];
            //data[j] = r[i];
        }
        v.push_back(data);
    }
    return v;
}

TEST(ShadowedDataImplTest, SetAndGetMat3Array)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<glm::mat3>{},
        std::vector<glm::mat3>{ glm::mat3(42.0f) },
        create_random_glm_vector<glm::mat3>(1000, -10.0f, 10.0f, 9),
        // invoke copy values since same size as previous but with different values
        create_random_glm_vector<glm::mat3>(1000, -10.0f, 10.0f, 9),
    };

    for (auto expected : test_data) {
        shadowed_data.set_mat3_array(expected);
        auto actual = static_cast<float const *>(shadowed_data.get_data());
        compare_glm_array(expected, 9, actual);
    }
}

TEST(ShadowedDataImplTest, SetAndGetMat4Array)
{
    gst::ShadowedDataImpl shadowed_data;

    auto test_data = {
        std::vector<glm::mat4>{},
        std::vector<glm::mat4>{ glm::mat4(42.0f) },
        create_random_glm_vector<glm::mat4>(1000, -10.0f, 10.0f, 16),
        // invoke copy values since same size as previous but with different values
        create_random_glm_vector<glm::mat4>(1000, -10.0f, 10.0f, 16),
    };

    for (auto expected : test_data) {
        shadowed_data.set_mat4_array(expected);
        auto actual = static_cast<float const *>(shadowed_data.get_data());
        compare_glm_array(expected, 16, actual);
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

    shadowed_data.set_mat3_array({});
    EXPECT_EQ(gst::DataType::MAT3_ARRAY, shadowed_data.get_type());

    shadowed_data.set_mat4_array({});
    EXPECT_EQ(gst::DataType::MAT4_ARRAY, shadowed_data.get_type());
}
