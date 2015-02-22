#include "annotationstruct.hpp"

#include "gmock/gmock.h"

TEST(AnnotationStructTest, FormatsAsStruct)
{
    const std::string name = "foo";
    gst::AnnotationStruct formatter(name);

    for (auto annotation : { "", "bar" }) {
        const std::string expected = name + "." + annotation;
        ASSERT_EQ(expected, formatter.format(annotation));
    }
}
