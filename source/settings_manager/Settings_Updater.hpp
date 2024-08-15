#pragma once
#include <initializer_list>
#include <memory>
#include "settings.hpp"

class IConcreteSettingsUpdater
{
public:
    virtual void settings_update(const ray_casting_settings&) = 0;
    virtual ~IConcreteSettingsUpdater() = default;
};

class Settings_Updater
{
public:

    void update(const ray_casting_settings& settings)
    {
        for (auto& obj: objs) 
            obj->settings_update(settings);
    }

    void add_updater(std::unique_ptr<IConcreteSettingsUpdater> obj)
    {
        objs.push_back(std::move(obj));
    }

private:
    std::vector<std::unique_ptr<IConcreteSettingsUpdater>> objs;
};