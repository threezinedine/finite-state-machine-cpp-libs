#include <string> 
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <functional>
#include <memory>
#include <fsm.hpp>
#include <macros.hpp>

class StateConfigTest: public ::testing::Test
{
    protected:
        MOCK_STATE_DEFINE(state)
        MOCK_STATE_DEFINE(firstChildState)
        MOCK_STATE_DEFINE(secondChildState)
        MOCK_STATE_DEFINE(thirdChildState)

        MOCK_TRIGGER_DEFINE(firstChildState, secondChildState)
        MOCK_TRIGGER_DEFINE(firstChildState, thirdChildState)
        MOCK_TRIGGER_DEFINE(nullptr, thirdChildState)
        MOCK_TRIGGER_DEFINE(firstChildState, nullptr)

        void SetUp() override 
        {
            MOCK_STATE_RESET(state)
            MOCK_STATE_RESET(firstChildState)
            MOCK_STATE_RESET(secondChildState)
            MOCK_STATE_RESET(thirdChildState)

            TRIGGER_RESET(firstChildState, secondChildState)
            TRIGGER_RESET(firstChildState, thirdChildState)
            TRIGGER_RESET(nullptr, thirdChildState)
            TRIGGER_RESET(firstChildState, nullptr)
        }

        void TearDown() override
        {
            delete state;
            delete firstChildState;
            delete secondChildState;
            delete thirdChildState;
        }
};

TEST_F(StateConfigTest, RunOnRun)
{
    State state(GET_STATE_NAME(state), GET_ON_RUN_FUNC(state));
    state.OnRun();

    EXPECT_EQ(GET_ON_RUN_CALLED_TIMES_VARIALBE(state), 1);
}

TEST_F(StateConfigTest, RunOnRunWithNullOnRun)
{
    State state(GET_STATE_NAME(state));
    EXPECT_NO_THROW(state.OnRun());
}

TEST_F(StateConfigTest, RunOnEntry)
{
    State state(GET_STATE_NAME(state), GET_ON_RUN_FUNC(state), GET_ON_ENTRY_FUNC(state));

    state.OnEntry();

    EXPECT_EQ(GET_ON_ENTRY_CALLED_TIMES_VARIABLE(state), 1);
}

TEST_F(StateConfigTest, RunOnExit)
{
    State state(GET_STATE_NAME(state), GET_ON_RUN_FUNC(state), 
                    GET_ON_ENTRY_FUNC(state), GET_ON_EXIT_FUNC(state));

    state.OnExit();

    EXPECT_EQ(GET_ON_EXIT_CALLED_TIMES_VARIABLE(state), 1);
}

TEST_F(StateConfigTest, RunOnExitWithoutOnExit)
{
    State state(GET_STATE_NAME(state), GET_ON_RUN_FUNC(state), 
                    GET_ON_ENTRY_FUNC(state));

    EXPECT_NO_THROW(state.OnExit());
}

TEST_F(StateConfigTest, RunOnEntryWithNullOnEntry)
{
    State state(GET_STATE_NAME(state), GET_ON_RUN_FUNC(state));

    EXPECT_NO_THROW(state.OnEntry());
}

TEST_F(StateConfigTest, RunGetName)
{
    State state(GET_STATE_NAME(state), GET_ON_RUN_FUNC(state));

    EXPECT_THAT(state.GetName(), ::testing::StrEq(GET_STATE_NAME(state)));
}

TEST_F(StateConfigTest, RegisterChildState)
{
    auto result = state->RegisterState(firstChildState);

    EXPECT_THAT(state->CheckExists(firstChildState), ::testing::IsTrue());
    EXPECT_EQ(result, RegisterResult_OK);
}

TEST_F(StateConfigTest, CheckExistOfNull)
{
    auto result = state->RegisterState(firstChildState);

    EXPECT_THAT(state->CheckExists(nullptr), ::testing::IsFalse());
}

TEST_F(StateConfigTest, RegisterWithExistedState)
{
    state->RegisterState(firstChildState);

    auto result = state->RegisterState(firstChildState);

    EXPECT_EQ(result, RegisterResult_DUPLICATION);
    EXPECT_THAT(state->CheckExists(firstChildState), ::testing::IsTrue());
}

TEST_F(StateConfigTest, RegisterANullState)
{
    auto result = state->RegisterState(nullptr);

    EXPECT_EQ(result, RegisterResult_NULL_STATE);
}

TEST_F(StateConfigTest, RegisterTransitionForState)
{
    auto result = state->RegisterTransition(
        TRIGGER_TRANSITION(
            firstChildState,
            secondChildState
        )
    ); 

    EXPECT_EQ(result, RegisterResult_OK);
}

TEST_F(StateConfigTest, RegisterTransitionForStateWithFromStateIsDoubleAndToStateIsDouble)
{
    state->RegisterTransition(
        TRIGGER_TRANSITION(
            firstChildState,
            secondChildState
        )
    ); 

    auto result = state->RegisterTransition(
        TRIGGER_TRANSITION(
            firstChildState,
            secondChildState
        ) 
    );

    EXPECT_EQ(result, RegisterResult_DUPLICATION);
}

TEST_F(StateConfigTest, RegisterTransitionForStateWithFromStateIsDouble)
{
    state->RegisterTransition(
        TRIGGER_TRANSITION(
            firstChildState,
            secondChildState
        )
    ); 

    auto result = state->RegisterTransition(
        TRIGGER_TRANSITION(
            firstChildState,
            thirdChildState
        ) 
    );

    EXPECT_EQ(result, RegisterResult_OK);
}

TEST_F(StateConfigTest, RegisterTransitionWithMultipleTimes)
{
    state->RegisterTransition(
        TRIGGER_TRANSITION(
            firstChildState,
            secondChildState
        )
    ); 

    state->RegisterTransition(
        TRIGGER_TRANSITION(
            firstChildState,
            thirdChildState
        ) 
    );

    auto result = state->RegisterTransition(
        TRIGGER_TRANSITION(
            firstChildState,
            secondChildState
        )
    ); 

    EXPECT_EQ(result, RegisterResult_DUPLICATION);
}

TEST_F(StateConfigTest, RegisterTranstionWithNullFromState)
{
    auto result =state->RegisterTransition(
        TRIGGER_TRANSITION(
            nullptr,
            thirdChildState
        )
    );

    EXPECT_EQ(result, RegisterResult_FROM_STATE_NULL_PTR);
}

TEST_F(StateConfigTest, RegisterTranstionWithNullToState)
{
    auto result = state->RegisterTransition(
        TRIGGER_TRANSITION(
            firstChildState,
            nullptr
        )
    );

    EXPECT_EQ(result, RegisterResult_TO_STATE_NULL_PTR);
}

TEST_F(StateConfigTest, RegisterTransitionWithNullTriggerFunc)
{
    auto result = state->RegisterTransition(
        {
            firstChildState,
            secondChildState,
            nullptr
        }
    );

    EXPECT_EQ(result, RegisterResult_TRIGGER_FUNC_NULL);
}

TEST_F(StateConfigTest, RegisterTheDefaultState)
{
    state->RegisterState(firstChildState);
    auto result = state->RegisterDefaultState(firstChildState);

    EXPECT_EQ(result, RegisterResult_OK);
}

TEST_F(StateConfigTest, runOnEntryWithConfigDefaultState)
{
    state->RegisterState(firstChildState);
    auto result = state->RegisterDefaultState(firstChildState);

    state->OnEntry();

    EXPECT_EQ(state->GetCurrentState(), firstChildState);
}

TEST_F(StateConfigTest, runOnEntryWithoutDefaultState)
{
    secondChildState->OnEntry();

    EXPECT_EQ(state->GetCurrentState(), nullptr);
}

TEST_F(StateConfigTest, registerStateWithoutPreConfig)
{
    auto result = state->RegisterDefaultState(firstChildState);

    EXPECT_EQ(result, RegisterResult_NOT_REGISTER_YET);
}

TEST_F(StateConfigTest, registerWithNullPointer)
{
    auto result = state->RegisterDefaultState(nullptr);
    EXPECT_EQ(result, RegisterResult_NULL_STATE);
}


TEST(StateInitializedTest, registerWithBothOnRunAndOnEntry)
{
    STATE_DEFINE(testState)
    bool onEntryCalled = false;
    bool onRunCalled = false;

    STATE_ON_ENTRY_DEFINE(testState, &onEntryCalled)
        onEntryCalled = true;
    STATE_ON_ENTRY_DEFINE_END(testState)

    STATE_ON_RUN_DEFINE(testState, &onRunCalled)
        onRunCalled = true;
    STATE_ON_RUN_DEFINE_END(testState)

    INITIALIZE_STATE(testState)

    testState->OnEntry();
    testState->OnRun();

    EXPECT_THAT(onEntryCalled, ::testing::IsTrue());
    EXPECT_THAT(onRunCalled, ::testing::IsTrue());

    RELEASE_STATE(testState)
}

TEST(StateInitializedTest, registerWithoutOnEntry)
{
    STATE_DEFINE(testState)
    bool onRunCalled = false;

    STATE_ON_RUN_DEFINE(testState, &onRunCalled)
        onRunCalled = true;
    STATE_ON_RUN_DEFINE_END(testState)

    INITIALIZE_STATE(testState)

    testState->OnEntry();
    testState->OnRun();

    EXPECT_THAT(onRunCalled, ::testing::IsTrue());

    RELEASE_STATE(testState)
}

TEST(StateInitializedTest, registerWithNothing)
{
    STATE_DEFINE(testState)

    INITIALIZE_STATE(testState)

    testState->OnEntry();
    testState->OnRun();

    RELEASE_STATE(testState)
}