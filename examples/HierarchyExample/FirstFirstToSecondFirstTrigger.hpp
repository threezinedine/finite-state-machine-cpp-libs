#pragma once
#include <fsm.hpp>
#include "FirstFirstChildState.hpp"
#include "SecondFirstChildState.hpp"


TRIGGER_DEFINE(firstFirstChildState, secondFirstChildState)
    return true;
TRIGGER_DEFINE_END(firstFirstChildState, secondFirstChildState)