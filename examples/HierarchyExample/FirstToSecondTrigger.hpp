#pragma once
#include <fsm.hpp>
#include "FirstChildState.hpp"
#include "SecondChildState.hpp"


TRIGGER_DEFINE(firstChildState, secondChildState)
    return true;
TRIGGER_DEFINE_END(firstChildState, secondChildState)