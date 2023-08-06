#pragma once
#include <fsm.hpp>


#define MOCK_TRIGGER_VARIABLE(fromState, toState) mock_##fromState##_to_##toState##_variable

#define MOCK_TRIGGER_DEFINE(fromState, toState)                 \
            bool MOCK_TRIGGER_VARIABLE(fromState, toState) = false;\
            TRIGGER_DEFINE(fromState, toState, this) \
                return MOCK_TRIGGER_VARIABLE(fromState, toState); \
            TRIGGER_DEFINE_END(fromState, toState)

#define MOCK_STATE_DEFINE(state) \
            STATE_DEFINE(state) \
            int GET_ON_ENTRY_CALLED_TIMES_VARIABLE(state) = 0; \
            int GET_ON_RUN_CALLED_TIMES_VARIALBE(state) = 0; \
            int GET_ON_EXIT_CALLED_TIMES_VARIABLE(state) = 0;

#define MOCK_STATE_RESET(state) \
            STATE_ON_ENTRY_DEFINE(state, this) \
                GET_ON_ENTRY_CALLED_TIMES_VARIABLE(state)++; \
            STATE_ON_ENTRY_DEFINE_END(state) \
            STATE_ON_RUN_DEFINE(state, this) \
                GET_ON_RUN_CALLED_TIMES_VARIALBE(state)++; \
            STATE_ON_RUN_DEFINE_END(state) \
            STATE_ON_EXIT_DEFINE(state, this) \
                GET_ON_EXIT_CALLED_TIMES_VARIABLE(state)++; \
            STATE_ON_EXIT_DEFINE_END(state) \
            GET_ON_ENTRY_CALLED_TIMES_VARIABLE(state) = 0; \
            GET_ON_RUN_CALLED_TIMES_VARIALBE(state) = 0; \
            GET_ON_EXIT_CALLED_TIMES_VARIABLE(state) = 0; \
            INITIALIZE_STATE(state) \

#define MOCK_STATE_RESET_AND_CONFIG(state, parentState) MOCK_STATE_RESET(state) \
            parentState->RegisterState(state);

