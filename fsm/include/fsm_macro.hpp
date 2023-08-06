#pragma once


#define TRIGGER_FUNC_NAME(fromState, toState) mock_##fromState##_to_##toState##_trigger
#define TRIGGER_TRANSITION(fromState, toState) transition_##fromState##_to_##toState
#define TRIGGER_DEFINE(fromState, toState, ...) \
        std::function<bool()> TRIGGER_FUNC_NAME(fromState, toState) \
                        = [__VA_ARGS__]() -> bool {
#define TRIGGER_DEFINE_END(fromState, toState) }; \
        Transition TRIGGER_TRANSITION(fromState, toState);

#define TRIGGER_RESET(fromState, toState)                  \
            TRIGGER_TRANSITION(fromState, toState) =       \
            {                                                   \
                fromState,                                      \
                toState,                                        \
                TRIGGER_FUNC_NAME(fromState, toState)           \
            };
#define TRIGGER_RESET_AND_CONFIG(fromState, toState, parentState) \
            TRIGGER_RESET(fromState, toState) \
            parentState->RegisterTransition(    \
                TRIGGER_TRANSITION(  \
                    fromState,      \
                    toState         \
                )           \
            );     

#define GET_STATE_NAME(state) state##_name

#define GET_ON_ENTRY_FUNC(state) onEntry_##state
#define GET_ON_ENTRY_CALLED_TIMES_VARIABLE(state) onEntry_##state##_called_times
#define GET_CHECK_ON_ENTRY_DEFINED_VARIABLE(state) isOnEntryDefine_##state

#define GET_ON_RUN_FUNC(state) onRun_##state
#define GET_ON_RUN_CALLED_TIMES_VARIALBE(state) onRun_##state##_called_times
#define GET_CHECK_ON_RUN_DEFINED_VARIABLE(state) isOnRunDefine_##state

#define GET_ON_EXIT_FUNC(state) onExist_##state
#define GET_ON_EXIT_CALLED_TIMES_VARIABLE(state) onExit_##state##_called_times
#define GET_CHECK_ON_EXIT_DEFINED_VARIABLE(state) isOnExitDefine_##state

#define STATE_DEFINE(state) std::string GET_STATE_NAME(state) = #state; \
            State* state = nullptr; \
            bool GET_CHECK_ON_ENTRY_DEFINED_VARIABLE(state) = false; \
            bool GET_CHECK_ON_RUN_DEFINED_VARIABLE(state) = false; \
            bool GET_CHECK_ON_EXIT_DEFINED_VARIABLE(state) = false; \
            std::function<void()> GET_ON_ENTRY_FUNC(state); \
            std::function<void()> GET_ON_RUN_FUNC(state); \
            std::function<void()> GET_ON_EXIT_FUNC(state);
#define STATE_ON_ENTRY_DEFINE(state, ...) GET_CHECK_ON_ENTRY_DEFINED_VARIABLE(state) = true; \
        GET_ON_ENTRY_FUNC(state) \
                    = [__VA_ARGS__]() {
#define STATE_ON_ENTRY_DEFINE_END(state) };
#define STATE_ON_RUN_DEFINE(state, ...) GET_CHECK_ON_RUN_DEFINED_VARIABLE(state) = true; \
        GET_ON_RUN_FUNC(state) \
                    = [__VA_ARGS__]() {
#define STATE_ON_RUN_DEFINE_END(state) };
#define STATE_ON_EXIT_DEFINE(state, ...) GET_CHECK_ON_EXIT_DEFINED_VARIABLE(state) = true; \
        GET_ON_EXIT_FUNC(state) \
                    = [__VA_ARGS__]() {
#define STATE_ON_EXIT_DEFINE_END(state) };
#define INITIALIZE_STATE(state) \
    if (GET_CHECK_ON_EXIT_DEFINED_VARIABLE(state)) \
    { \
        state = new State(GET_STATE_NAME(state), \
                GET_ON_RUN_FUNC(state), \
                GET_ON_ENTRY_FUNC(state), \
                GET_ON_EXIT_FUNC(state)); \
    } \
    else if (GET_CHECK_ON_ENTRY_DEFINED_VARIABLE(state)) \
    { \
        state = new State(GET_STATE_NAME(state), GET_ON_RUN_FUNC(state), GET_ON_ENTRY_FUNC(state)); \
    } \
    else if (GET_CHECK_ON_RUN_DEFINED_VARIABLE(state)) \
    { \
        state = new State(GET_STATE_NAME(state), GET_ON_RUN_FUNC(state)); \
    } \
    else \
    { \
        state = new State(GET_STATE_NAME(state)); \
    }
    
#define RELEASE_STATE(state) delete state;