#pragma once
#include <initializer_list>
#include <memory>
#include "settings.hpp"

class ISettingsUpdater
{
public:
    virtual void settings_update(const ray_casting_settings&) = 0;
    virtual ~ISettingsUpdater() = default;
};

class Settings_Updater
{
public:

    void update(const ray_casting_settings&);

    void add_updater(std::unique_ptr<ISettingsUpdater>);

private:
    std::vector<std::unique_ptr<ISettingsUpdater>> objs;
};