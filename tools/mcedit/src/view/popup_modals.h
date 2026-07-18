#pragma once

#include <string>

namespace mcedit::model
{
struct resources;
}

namespace mcedit::view
{

class popup_modals final
{
private:
    std::string _resources_error_message;

public:
    void update(model::resources&);
};

} // namespace mcedit::view
