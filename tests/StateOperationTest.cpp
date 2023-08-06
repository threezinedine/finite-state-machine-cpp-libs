#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fsm.hpp>
#include <macros.hpp>


class StateOperationTest: public ::testing::Test
{
    protected:
        MOCK_STATE_DEFINE(state)
        MOCK_STATE_DEFINE(firstChildState)
        MOCK_STATE_DEFINE(secondChildState)
        MOCK_STATE_DEFINE(thirdChildState)

        MOCK_STATE_DEFINE(firstChildFirstChildState)
        MOCK_STATE_DEFINE(secondChildFirstChildState)


        MOCK_TRIGGER_DEFINE(firstChildState, secondChildState)
        MOCK_TRIGGER_DEFINE(firstChildState, thirdChildState)
        MOCK_TRIGGER_DEFINE(secondChildState, firstChildState)
        MOCK_TRIGGER_DEFINE(secondChildState, thirdChildState)
        MOCK_TRIGGER_DEFINE(thirdChildState, secondChildState)
        MOCK_TRIGGER_DEFINE(thirdChildState, firstChildState)

        MOCK_TRIGGER_DEFINE(firstChildFirstChildState, secondChildFirstChildState)
        MOCK_TRIGGER_DEFINE(secondChildFirstChildState, firstChildFirstChildState)

        void SetUp() override 
        {
            MOCK_STATE_RESET(state)
            MOCK_STATE_RESET_AND_CONFIG(firstChildState, state)
            MOCK_STATE_RESET_AND_CONFIG(secondChildState, state)
            MOCK_STATE_RESET_AND_CONFIG(thirdChildState, state)
            state->RegisterDefaultState(firstChildState);

            MOCK_STATE_RESET_AND_CONFIG(firstChildFirstChildState, firstChildState)
            MOCK_STATE_RESET_AND_CONFIG(secondChildFirstChildState, firstChildState)
            firstChildState->RegisterDefaultState(firstChildFirstChildState);

            TRIGGER_RESET_AND_CONFIG(firstChildState, secondChildState, state)
            TRIGGER_RESET_AND_CONFIG(firstChildState, thirdChildState, state)
            TRIGGER_RESET_AND_CONFIG(secondChildState, firstChildState, state)
            TRIGGER_RESET_AND_CONFIG(secondChildState, thirdChildState, state)
            TRIGGER_RESET_AND_CONFIG(thirdChildState, secondChildState, state)
            TRIGGER_RESET_AND_CONFIG(thirdChildState, firstChildState, state)

            TRIGGER_RESET_AND_CONFIG(firstChildFirstChildState, secondChildFirstChildState, firstChildState)
            TRIGGER_RESET_AND_CONFIG(secondChildFirstChildState, firstChildFirstChildState, firstChildState)
        }

        void TearDown() override
        {
            RELEASE_STATE(state)
            RELEASE_STATE(firstChildState)
            RELEASE_STATE(secondChildState)
            RELEASE_STATE(thirdChildState)

            RELEASE_STATE(firstChildFirstChildState)
            RELEASE_STATE(secondChildFirstChildState)
        }
};


TEST_F(StateOperationTest, testFirstRun)
{
    state->OnEntry();
    state->OnRun();

    state->OnRun();

    EXPECT_EQ(state->GetCurrentState(), firstChildState);
}


TEST_F(StateOperationTest, testRunAndATriggerRises)
{
    state->OnEntry();
    state->OnRun();
    MOCK_TRIGGER_VARIABLE(firstChildState, secondChildState) = true;
    state->OnRun();

    state->OnRun();

    EXPECT_EQ(state->GetCurrentState(), secondChildState);
    EXPECT_THAT(GET_ON_RUN_CALLED_TIMES_VARIALBE(firstChildState), ::testing::Le(2));
    EXPECT_THAT(GET_ON_RUN_CALLED_TIMES_VARIALBE(secondChildState), ::testing::Ge(1));
    EXPECT_THAT(GET_ON_ENTRY_CALLED_TIMES_VARIABLE(secondChildState), ::testing::Ge(1));
}


TEST_F(StateOperationTest, testRunAndReturnNotReturnTheDefaultState)
{
    state->OnEntry();
    state->OnRun();

    EXPECT_EQ(state->GetCurrentState()->GetCurrentState(), firstChildFirstChildState);
    EXPECT_THAT(GET_ON_RUN_CALLED_TIMES_VARIALBE(firstChildFirstChildState), ::testing::Ge(1));
}

TEST_F(StateOperationTest, transitionToAnotherState)
{
    state->OnEntry();
    state->OnRun();
    MOCK_TRIGGER_VARIABLE(firstChildFirstChildState, secondChildFirstChildState) = true;
    state->OnRun();
    state->OnRun();
    state->OnRun();

    EXPECT_EQ(state->GetCurrentState(), firstChildState);
    EXPECT_EQ(state->GetCurrentState()->GetCurrentState(), secondChildFirstChildState);
    EXPECT_THAT(GET_ON_RUN_CALLED_TIMES_VARIALBE(firstChildFirstChildState), ::testing::Le(2));
    EXPECT_THAT(GET_ON_RUN_CALLED_TIMES_VARIALBE(secondChildFirstChildState), ::testing::Ge(2));
}

TEST_F(StateOperationTest, transitionToAnotherStateInHigherLevel)
{
    state->OnEntry();
    state->OnRun();
    MOCK_TRIGGER_VARIABLE(firstChildFirstChildState, secondChildFirstChildState) = true;
    state->OnRun();
    MOCK_TRIGGER_VARIABLE(firstChildFirstChildState, secondChildFirstChildState) = false;
    MOCK_TRIGGER_VARIABLE(firstChildState, secondChildState) = true;
    state->OnRun();
    MOCK_TRIGGER_VARIABLE(firstChildState, secondChildState) = false;

    state->OnRun();

    EXPECT_EQ(state->GetCurrentState(), secondChildState);
    EXPECT_EQ(state->GetCurrentState()->GetCurrentState(), nullptr);
}

TEST_F(StateOperationTest, transitionToAnotherStateInHigherLevelAndReturnBack)
{
    state->OnEntry();
    state->OnRun();
    MOCK_TRIGGER_VARIABLE(firstChildFirstChildState, secondChildFirstChildState) = true;
    state->OnRun();
    MOCK_TRIGGER_VARIABLE(firstChildFirstChildState, secondChildFirstChildState) = false;
    MOCK_TRIGGER_VARIABLE(firstChildState, secondChildState) = true;
    state->OnRun();
    MOCK_TRIGGER_VARIABLE(firstChildState, secondChildState) = false;
    MOCK_TRIGGER_VARIABLE(secondChildState, firstChildState) = true;
    state->OnRun();
    MOCK_TRIGGER_VARIABLE(secondChildState, firstChildState) = false;

    state->OnRun();

    EXPECT_EQ(state->GetCurrentState(), firstChildState);
    EXPECT_EQ(state->GetCurrentState()->GetCurrentState(), firstChildFirstChildState);
    EXPECT_THAT(GET_ON_ENTRY_CALLED_TIMES_VARIABLE(firstChildFirstChildState), ::testing::Eq(2));
    EXPECT_THAT(GET_ON_ENTRY_CALLED_TIMES_VARIABLE(firstChildState), ::testing::Eq(2));
    EXPECT_THAT(GET_ON_ENTRY_CALLED_TIMES_VARIABLE(secondChildState), ::testing::Eq(1));
}