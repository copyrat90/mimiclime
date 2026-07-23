#include "ctrl/resources_edits.h"

#include "model/resources.h"

#include <ImGuiNotify.hpp>

#include <cstddef>
#include <utility>

namespace mcedit::ctrl
{

namespace
{

constexpr std::size_t MAX_UNDOS = 1024;

void remove_overflown_notification()
{
    if (ImGui::notifications.size() >= NOTIFY_RENDER_LIMIT)
        ImGui::RemoveNotification(0);
}

} // namespace

resources_edits::resources_edits(model::resources& resources) : _resources(resources)
{
}

void resources_edits::update()
{
    if (ImGui::Shortcut(ImGuiMod_Ctrl | ImGuiKey_Z, ImGuiInputFlags_RouteGlobal))
        undo();

    if (ImGui::Shortcut(ImGuiMod_Ctrl | ImGuiKey_Y, ImGuiInputFlags_RouteGlobal) ||
        ImGui::Shortcut(ImGuiMod_Ctrl | ImGuiMod_Shift | ImGuiKey_Z, ImGuiInputFlags_RouteGlobal))
        redo();

    if (ImGui::Shortcut(ImGuiMod_Ctrl | ImGuiKey_S, ImGuiInputFlags_RouteGlobal))
        save();
}

bool resources_edits::has_undo() const
{
    return !_undos.empty();
}

bool resources_edits::has_redo() const
{
    return !_redos.empty();
}

void resources_edits::add(resource_edit_ptr&& edit)
{
    IM_ASSERT(edit && "edit can't be nullptr");

    try
    {
        edit->apply(_resources);

        _redos.clear();
        if (_undos.size() >= MAX_UNDOS)
            _undos.pop_front();

        _undos.push_back(std::move(edit));

        _subject.notify(event_kind::ADD);
    }
    catch (const std::exception& ex)
    {
        remove_overflown_notification();
        ImGui::InsertNotification({ImGuiToastType::Error, ex.what()});
    }
}

void resources_edits::undo()
{
    if (_undos.empty())
    {
        ImGuiToast toast(ImGuiToastType::Info, "Nothing to undo.");
        toast.setTitle("No undo");
        remove_overflown_notification();
        ImGui::InsertNotification(toast);
        return;
    }

    try
    {
        _undos.back()->undo(_resources);

        _redos.push_back(std::move(_undos.back()));
        _undos.pop_back();

        ImGuiToast toast(ImGuiToastType::Success);
        toast.setTitle("Undo");
        toast.setContent(_redos.back()->undo_message().c_str());

        remove_overflown_notification();
        ImGui::InsertNotification(toast);

        _subject.notify(event_kind::UNDO);
    }
    catch (const std::exception& ex)
    {
        remove_overflown_notification();
        ImGui::InsertNotification({ImGuiToastType::Error, ex.what()});
    }
}

void resources_edits::redo()
{
    if (_redos.empty())
    {
        ImGuiToast toast(ImGuiToastType::Info, "Nothing to redo.");
        toast.setTitle("No redo");
        remove_overflown_notification();
        ImGui::InsertNotification(toast);
        return;
    }

    try
    {
        _redos.back()->apply(_resources);

        _undos.push_back(std::move(_redos.back()));
        _redos.pop_back();

        ImGuiToast toast(ImGuiToastType::Success);
        toast.setTitle("Redo");
        toast.setContent(_undos.back()->redo_message().c_str());
        remove_overflown_notification();
        ImGui::InsertNotification(toast);

        _subject.notify(event_kind::REDO);
    }
    catch (const std::exception& ex)
    {
        remove_overflown_notification();
        ImGui::InsertNotification({ImGuiToastType::Error, ex.what()});
    }
}

void resources_edits::clear()
{
    _undos.clear();
    _redos.clear();

    _subject.notify(event_kind::CLEAR);
}

void resources_edits::save()
{
    try
    {
        _resources.save_changes();

        ImGuiToast toast(ImGuiToastType::Success, "Saved changes.");
        toast.setTitle("Saved");
        remove_overflown_notification();
        ImGui::InsertNotification(toast);
    }
    catch (const std::exception& ex)
    {
        remove_overflown_notification();
        ImGui::InsertNotification({ImGuiToastType::Error, ex.what()});
    }
}

void resources_edits::attach_observer(decltype(_subject)::observer_t& observer)
{
    _subject.attach(observer);
}

void resources_edits::detach_observer(decltype(_subject)::observer_t& observer)
{
    _subject.detach(observer);
}

} // namespace mcedit::ctrl
