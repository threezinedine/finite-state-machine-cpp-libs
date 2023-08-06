#pragma once
#include <fsm.hpp>
#include "FirstChildState.hpp"
#include "SecondChildState.hpp"


TRIGGER_DEFINE(secondChildState, firstChildState)
    return true;
TRIGGER_DEFINE_END(secondChildState, firstChildState)