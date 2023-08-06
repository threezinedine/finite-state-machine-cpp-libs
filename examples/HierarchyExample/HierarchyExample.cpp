#include <iostream>
#include <fsm.hpp>


int main(void)
{
    #include "StateDefine.hpp"
    #include "ParentState.hpp"
    #include "FirstChildState.hpp"
    #include "SecondChildState.hpp"
    #include "FirstFirstChildState.hpp"
    #include "SecondFirstChildState.hpp"
    #include "FirstToSecondTrigger.hpp"
    #include "SecondToFirstTrigger.hpp"
    #include "FirstFirstToSecondFirstTrigger.hpp"
    #include "SecondFirstToFirstFirstTrigger.hpp"

    INITIALIZE_STATE(parentState)
    INITIALIZE_STATE(firstChildState)
    INITIALIZE_STATE(secondChildState)
    INITIALIZE_STATE(firstFirstChildState)
    INITIALIZE_STATE(secondFirstChildState)

    parentState->RegisterState(firstChildState);
    parentState->RegisterState(secondChildState);
    parentState->RegisterDefaultState(firstChildState);

    firstChildState->RegisterState(firstFirstChildState);
    firstChildState->RegisterState(secondFirstChildState);
    firstChildState->RegisterDefaultState(firstFirstChildState);

    TRIGGER_RESET_AND_CONFIG(firstChildState, secondChildState, parentState)
    TRIGGER_RESET_AND_CONFIG(secondChildState, firstChildState, parentState)

    TRIGGER_RESET_AND_CONFIG(firstFirstChildState, secondFirstChildState, firstChildState)
    TRIGGER_RESET_AND_CONFIG(secondFirstChildState, firstFirstChildState, firstChildState)

    parentState->OnEntry();

    parentState->OnRun();
    parentState->OnRun();
    parentState->OnRun();
    parentState->OnRun();
    parentState->OnRun();

    RELEASE_STATE(parentState)
    RELEASE_STATE(firstChildState)
    RELEASE_STATE(secondChildState)
    RELEASE_STATE(firstFirstChildState)
    RELEASE_STATE(secondFirstChildState)
    return 0;
}