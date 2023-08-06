#pragma once
#include <functional>

class State;

enum RegisterResult
{
    RegisterResult_OK,
    RegisterResult_DUPLICATION,
    RegisterResult_NULL_STATE,
    RegisterResult_FROM_STATE_NULL_PTR,
    RegisterResult_TRIGGER_FUNC_NULL,
    RegisterResult_TO_STATE_NULL_PTR,
    RegisterResult_NOT_REGISTER_YET,
};

struct Transition 
{
    State* fromState;
    State* toState;
    std::function<bool()> triggerFunc;
};