#pragma once

#include <atomic>
#include <thread>

#include "system_without_console.hpp"

void start_configurator(std::atomic_bool &is_configurator_opened);