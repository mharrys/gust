#include "annotationarray.hpp"

#include "gmock/gmock.h"

TEST(AnnotationArrayTest, FormatsAsArrayWithDefaultIndex)
{
    const std::string name = "foo";
    gst::AnnotationArray formatter(name);

    for (auto annotation : { "", "bar" }) {
        const std::string expected = name + "[0]." + annotation;
        ASSERT_EQ(expected, formatter.format(annotation));
    }
}

TEST(AnnotationArrayTest, FormatsAsArrayWithNewIndex)
{
    const std::string name = "foo";
    gst::AnnotationArray formatter(name);

    for (auto index : { 42, 0, 1, 42 }) {
        formatter.set_current_index(index);
        for (auto annotation : { "", "bar" }) {
            const std::string expected = name + "[" + std::to_string(index) + "]." + annotation;
            ASSERT_EQ(expected, formatter.format(annotation));
        }
    }
}
