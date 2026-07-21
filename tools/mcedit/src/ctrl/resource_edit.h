#pragma once

#include <memory>
#include <string>

namespace mcedit::model
{
struct resources;
}

namespace mcedit::ctrl
{

class resource_edit
{
public:
    virtual ~resource_edit() = default;

    virtual void apply(model::resources&) = 0;
    virtual void undo(model::resources&) = 0;

    virtual auto undo_message() const -> std::string = 0;
    virtual auto redo_message() const -> std::string = 0;
};

using resource_edit_ptr = std::unique_ptr<resource_edit>;

} // namespace mcedit::ctrl
