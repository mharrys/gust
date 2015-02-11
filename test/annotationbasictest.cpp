#include "annotationbasic.hpp"

#include "gmock/gmock.h"

TEST(AnnotationBasicTest, FormatsWithoutModification)
{
    gst::AnnotationBasic formatter;

    for (auto annotation : { "", "foo" }) {
        ASSERT_EQ(annotation, formatter.format(annotation));
    }
}
