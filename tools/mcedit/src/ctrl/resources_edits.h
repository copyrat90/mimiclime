#pragma once

#include "ctrl/resource_edit.h"

#include "util/observer.h"

#include <cstdint>
#include <deque>

namespace mcedit::ctrl
{

class resources_edits final
{
public:
    enum class event_kind : std::uint8_t
    {
        ADD,
        UNDO,
        REDO,
        CLEAR,
    };

private:
    model::resources& _resources;
    util::subject<void(event_kind)> _subject;

    std::deque<resource_edit_ptr> _undos;
    std::deque<resource_edit_ptr> _redos;

public:
    resources_edits(model::resources&);

    void update();

    bool has_undo() const;
    bool has_redo() const;

    void add(resource_edit_ptr&&);

    void undo();
    void redo();

    void clear();

    void save();

    void attach_observer(decltype(_subject)::observer_t& observer);
    void detach_observer(decltype(_subject)::observer_t& observer);
};

} // namespace mcedit::ctrl
