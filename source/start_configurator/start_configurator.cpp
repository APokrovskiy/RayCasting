#include "start_configurator.hpp" // TODO: Определится с названием

#include <stdexcept>

void start_configurator(std::atomic_bool& is_configurator_opened)
{
    
    if (!is_configurator_opened.load()) // если поток с конфигуратором не создан => то создать
    {
        // Создание потока с конфигуратором
        std::thread([&] {
            is_configurator_opened.store(true);
            system_without_console_output(L"python ./RayCastingConfigurator/Configurator.pyw");
            is_configurator_opened.store(false);
        }).detach();
    }
    else; // ничего ни делать
}