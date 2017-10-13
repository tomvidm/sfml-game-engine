#include "test_AnimationHandler.h"
#include <iostream>

namespace engine
{
    void TestAnimationHandler::SetUp()
    {
        ;
    }

    TEST_F(TestAnimationHandler, CorrectlyImportsAnimationFromLuaTable)
    {
        animationHandler.loadFromLuaTable("../../../resources/images/spritesheet_testsprite.lua", "spritesheet_testsprite");
        FrameData frameData = animationHandler.get("testsprite_walk_right");
        EXPECT_EQ(frameData.getNumFrames(), 8);
    }
}