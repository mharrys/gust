#include "worldrunner.hpp"

#include "mock/mockclock.hpp"
#include "mock/mockwindow.hpp"
#include "mock/mockworld.hpp"

using ::testing::Return;

static const int SUCCESS = 0;
static const int FAILURE = 1;

TEST(WorldRunnerTest, BreakControlIfWindowShouldClose)
{
    gst::MockClock clock;
    gst::MockWindow window;
    gst::MockWorld world;
    gst::WorldRunner runner;

    EXPECT_CALL(window, should_close())
        .WillOnce(Return(true));

    ASSERT_EQ(FAILURE, runner.control(world, clock, window));
}

TEST(WorldRunnerTest, BreakControlIfWorldCreateFails)
{
    gst::MockClock clock;
    gst::MockWindow window;
    gst::MockWorld world;
    gst::WorldRunner runner;

    EXPECT_CALL(world, create())
        .WillOnce(Return(false));
    EXPECT_CALL(world, destroy())
        .Times(1);

    EXPECT_CALL(window, should_close())
        .WillOnce(Return(false));

    ASSERT_EQ(FAILURE, runner.control(world, clock, window));
}

TEST(WorldRunnerTest, BreakControlAfterOneSuccessfulLoop)
{
    gst::MockClock clock;
    gst::MockWindow window;
    gst::MockWorld world;
    gst::WorldRunner runner;

    EXPECT_CALL(clock, elapsed())
        .WillOnce(Return(1.0f));
    EXPECT_CALL(clock, delta())
        .WillOnce(Return(1.0f));

    EXPECT_CALL(world, create())
        .WillOnce(Return(true));
    EXPECT_CALL(world, update(1.0f, 1.0f))
        .Times(1);
    EXPECT_CALL(world, destroy())
        .Times(1);

    EXPECT_CALL(window, should_close())
        .WillOnce(Return(false))
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    EXPECT_CALL(window, poll())
        .Times(1);
    EXPECT_CALL(window, swap())
        .Times(1);

    ASSERT_EQ(SUCCESS, runner.control(world, clock, window));
}
