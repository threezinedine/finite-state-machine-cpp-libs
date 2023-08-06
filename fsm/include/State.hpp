#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <fsm_types.hpp>


class State
{
    public:
        State(const std::string& name);
        State(const std::string& name, std::function<void()> onRun);
        State(const std::string& name, std::function<void()> onRun, std::function<void()> onEntry);
        State(const std::string& name, std::function<void()> onRun, 
                    std::function<void()> onEntry, std::function<void()> onExit);
        ~State();

        void OnRun();
        void OnEntry();
        RegisterResult RegisterState(State* state);
        bool CheckExists(State* state) const;
        RegisterResult RegisterTransition(Transition transition);
        RegisterResult RegisterDefaultState(State* state);
        inline State* GetCurrentState() const { return currentState_; }

        inline std::string GetName() const { return name_; } 

        friend std::ostream& operator<< (std::ostream& os, const State& state)
        {
            os << "State name: " << state.GetName() << std::endl;
            return os;
        } 

    private:
        const std::string& name_;
        std::function<void()> onRun_;
        std::function<void()> onEntry_;
        State* currentState_ = nullptr;
        State* defaultState_ = nullptr;
        std::map<std::string, std::vector<Transition>> transitions_;
}; 
