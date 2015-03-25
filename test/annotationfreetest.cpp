#include "annotationfree.hpp"

#include "gmock/gmock.h"

TEST(AnnotationFreeTest, FormatsWithoutModification)
{
    gst::AnnotationFree formatter;

    for (auto annotation : { "", "foo" }) {
        ASSERT_EQ(annotation, formatter.format(annotation));
    }
}
