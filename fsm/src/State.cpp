#include <iostream>
#include <string>
#include <functional>
#include <algorithm>

#include <fsm_types.hpp>
#include <State.hpp>


State::State(const std::string& name)
    : name_(name), onRun_(nullptr), onEntry_(nullptr), onExit_(nullptr)
{

} 

State::State(const std::string& name, std::function<void()> onRun)
    : name_(name), onRun_(onRun), onEntry_(nullptr), onExit_(nullptr)
{

} 

State::State(const std::string& name, std::function<void()> onRun, std::function<void()> onEntry)
    : name_(name), onRun_(onRun), onEntry_(onEntry), onExit_(nullptr)
{

} 

State::State(const std::string& name, std::function<void()> onRun, 
                    std::function<void()> onEntry, std::function<void()> onExit)
    : name_(name), onRun_(onRun), onEntry_(onEntry), onExit_(onExit)
{

}

State::~State()
{
    
}

void State::OnRun() 
{
    if (onRun_ != nullptr)
    {
        onRun_();
    }

    if (currentState_ != nullptr)
    {
        currentState_->OnRun();
        auto currentName = currentState_->GetName();

        for (auto transition: transitions_[currentName])
        {
            if (transition.triggerFunc())
            {
                currentState_->OnExit();
                currentState_ = transition.toState;
                currentState_->OnEntry();
            }
        }
    }
}

void State::OnEntry()
{
    currentState_ = defaultState_;

    if (onEntry_ != nullptr)
    {
        onEntry_();
    }

    if (currentState_ != nullptr)
    {
        currentState_->OnEntry();
    }
}

void State::OnExit()
{
    if (onExit_ != nullptr)
    {
        onExit_(); 
    }

    if (currentState_ != nullptr)
    {
        currentState_->OnExit();
    }
}

RegisterResult State::RegisterState(State* state)
{
    if (state == nullptr)
    {
        return RegisterResult_NULL_STATE;
    }

    if (!CheckExists(state))
    {
        transitions_[state->GetName()] = std::vector<Transition>();
        return RegisterResult_OK;
    }
    else 
    {
        return RegisterResult_DUPLICATION;
    }
}

bool State::CheckExists(State* state) const 
{
    if (state == nullptr)
    {
        return false;
    }
    return transitions_.find(state->GetName()) != transitions_.end();
}

RegisterResult State::RegisterDefaultState(State* state)
{
    if (state == nullptr)
    {
        return RegisterResult_NULL_STATE;
    }
    if (transitions_.find(state->GetName()) != transitions_.end())
    {
        defaultState_ = state;
        return RegisterResult_OK;
    }
    else
    {
        return RegisterResult_NOT_REGISTER_YET;
    }
}


RegisterResult State::RegisterTransition(Transition transition)
{
    if (transition.fromState == nullptr)
    {
        return RegisterResult_FROM_STATE_NULL_PTR;
    }
    if (transition.toState == nullptr)
    {
        return RegisterResult_TO_STATE_NULL_PTR;
    }
    if (transition.triggerFunc == nullptr)
    {
        return RegisterResult_TRIGGER_FUNC_NULL; 
    }

    std::string fromStateName = transition.fromState->GetName();

    for (auto tran: transitions_[fromStateName])
    {
        if (tran.toState == transition.toState)
        {
            return RegisterResult_DUPLICATION;
        }
    }

    transitions_[fromStateName].push_back(transition);
    return RegisterResult_OK;
}
