#include <iostream>
#include <fsm.hpp>



int main(void)
{
    STATE_DEFINE(state)
    STATE_DEFINE(firstChildState)
    STATE_DEFINE(secondChildState)

    STATE_ON_ENTRY_DEFINE(state)
        std::cout << "On Entry" << std::endl;
    STATE_ON_ENTRY_DEFINE_END(state)

    STATE_ON_RUN_DEFINE(state)
        std::cout << "On Run" << std::endl;
    STATE_ON_RUN_DEFINE_END(state)

    STATE_ON_ENTRY_DEFINE(firstChildState)
        std::cout << "On Entry From First Child" << std::endl;
    STATE_ON_ENTRY_DEFINE_END(firstChildState)

    STATE_ON_RUN_DEFINE(firstChildState)
        std::cout << "On Run From First Child" << std::endl;
    STATE_ON_RUN_DEFINE_END(firstChildState)

    STATE_ON_ENTRY_DEFINE(secondChildState)
        std::cout << "On Entry From Second Child" << std::endl;
    STATE_ON_ENTRY_DEFINE_END(secondChildState)

    STATE_ON_RUN_DEFINE(secondChildState)
        std::cout << "On Run From Second Child" << std::endl;
    STATE_ON_RUN_DEFINE_END(secondChildState)

    TRIGGER_DEFINE(firstChildState, secondChildState)
        return true;
    TRIGGER_DEFINE_END(firstChildState, secondChildState)

    TRIGGER_DEFINE(secondChildState, firstChildState)
        return true;
    TRIGGER_DEFINE_END(secondChildState, firstChildState)

    INITIALIZE_STATE(state)
    INITIALIZE_STATE(firstChildState)
    INITIALIZE_STATE(secondChildState)

    state->RegisterState(firstChildState);
    state->RegisterState(secondChildState);
    state->RegisterDefaultState(firstChildState);

    TRIGGER_RESET_AND_CONFIG(firstChildState, secondChildState, state)
    TRIGGER_RESET_AND_CONFIG(secondChildState, firstChildState, state)

    state->OnEntry();

    state->OnRun();
    state->OnRun();
    state->OnRun();
    state->OnRun();
    state->OnRun();

    RELEASE_STATE(state)
    RELEASE_STATE(firstChildState)
    RELEASE_STATE(secondChildState)
    return 0;
}