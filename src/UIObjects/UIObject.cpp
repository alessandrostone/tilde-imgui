
//
//  NodeObject.cpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#include "UIObject.hpp"

#include "IUWindowController.hpp"
#include "PdPatchViewController.hpp"

#include "AppController.hpp"

int nameChanged(ImGuiTextEditCallbackData* o)
{
    UIObject* obj = (UIObject*)o->UserData;

    //obj->enteredText = std::string(o->BufTextLen, *o->Buf);
    obj->enteredText = obj->_editText;
    obj->updated(UIObject::oAutocomplete);

    return 0;
}

#pragma mark -

void UIObject::draw()
{
    if (hidden)
        return;

    width = 75;
    height = 25;

    int mc = (data.inletCount > data.outletCount) ? data.inletCount : data.outletCount;
    width = 25 * mc;

    float text_w = ImGui::CalcTextSize(objectText.c_str()).x + 8;
    if (width < text_w)
        width = text_w;

    if (width < 50)
        width = 50;

    if (data.emptyBox) {
        _objectReplaceMode = true;
        windowController()->isEditingText = true;
    }

    UiObjectBase::draw();

    //    return;
    //    //
    //    ImGui::PushID(ImGui::GetID(id().c_str()));

    //    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    //    //
    //    draw_list->ChannelsSplit(2);
    //    draw_list->ChannelsSetCurrent(1);

    //    ImGui::BeginGroup(); // Lock horizontal position

    //    ImU32 borderColor = (this->selected) ? IM_COL32(0, 192, 255, 255) : IM_COL32(192, 192, 192, 255);

    //    if (errorBox)
    //        borderColor = IM_COL32(255, 0, 0, 255);
    //    if (emptyBox)
    //        borderColor = IM_COL32(0, 192, 255, 255);

    //    ImGui::PushItemWidth(114.0f);

    //    ImGui::SetCursorScreenPos(ImVec2(this->x + 6, this->y + 5));
    //    if (!_objectReplaceMode) {
    //        ImGui::Text("%s", (char*)objectText.c_str());
    //        if (ImGui::IsMouseHoveringRect(ImVec2(this->x + 6, this->y + 5), ImVec2(this->x + 6 + width, this->y + 25))) {
    //            if (ImGui::IsMouseDoubleClicked(0)) {
    ////                assert(windowController());
    //                windowController()->isEditingText = true;

    //                windowController()->restoreContext();
    //                ImGuiIO& io = ImGui::GetIO();
    //                io.ClearInputCharacters();
    //                io.MouseDoubleClicked[0] = false;

    //                _objectReplaceMode = true;
    //            }
    //        }
    //    } else {

    //        // FIX THAT
    //        int s = objectText.size();
    //        if (s < 0)
    //            s = 0;
    //        if (s > 64)
    //            s = 64;
    //        memcpy(_editText, objectText.c_str(), s);

    //        if (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))
    //            ImGui::SetKeyboardFocusHere(0);

    //        ImGui::PushItemWidth(width - 8);
    //        if (ImGui::InputText("##in", _editText, 64, ImGuiInputTextFlags_CallbackAlways | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll, &nameChanged, (void*)this)) {
    //            finishedEditingText();
    //        }
    //    }

    //    ImGui::EndGroup();

    //    //
    //    ImVec2 node_rect_min = ImVec2(this->x, this->y);
    //    ImVec2 node_rect_max = node_rect_min + ImVec2(width, 30); //ImGui::GetItemRectMax();

    //    draw_list->ChannelsSetCurrent(0); // Background
    //    draw_list->AddRectFilled(node_rect_min, node_rect_max, IM_COL32(75, 75, 75, 255), 4.0f);
    //    draw_list->AddRect(node_rect_min, node_rect_max, borderColor, 0.0f);

    //    // inlets
    //    for (int slot_idx = 0; slot_idx < inletCount; slot_idx++) {
    //        _drawInlet(slot_idx);
    //    }

    //    // outlets
    //    for (int slot_idx = 0; slot_idx < outletCount; slot_idx++) {
    //        _drawOutlet(slot_idx);
    //    }

    //    ImGui::PopID();

    //    draw_list->ChannelsMerge();
};

void UIObject::drawObjectContents()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    draw_list->ChannelsSetCurrent(1);

    ImGui::BeginGroup(); // Lock horizontal position

    //    ImU32 borderColor = (this->selected) ? IM_COL32(0, 192, 255, 255) : IM_COL32(192, 192, 192, 255);

    //    if (errorBox)
    //        borderColor = IM_COL32(255, 0, 0, 255);
    //    if (emptyBox)
    //        borderColor = IM_COL32(0, 192, 255, 255);

    ImGui::PushItemWidth(114.0f);

    if (AppController::fixedWidthFont())
    ImGui::PushFont(AppController::fixedWidthFont());

    ImGui::SetCursorScreenPos(ImVec2(this->x + 4, this->y + height / 6));
    if (!_objectReplaceMode) {
        ImGui::Text("%s", (char*)objectText.c_str());

//        if (ImGui::IsMouseHoveringRect(ImVec2(this->x + 6, this->y + 5), ImVec2(this->x + 6 + width, this->y + 25))) {
//            if (ImGui::IsMouseDoubleClicked(0)) {
//                //                assert(windowController());
//                windowController()->isEditingText = true;

//                windowController()->restoreContext();
//                ImGuiIO& io = ImGui::GetIO();
//                io.ClearInputCharacters();
//                io.MouseDoubleClicked[0] = false;

//                _objectReplaceMode = true;
//            }
//        }
    } else {

        ///> \todo FIX THAT
        int s = objectText.size();
        if (s < 0)
            s = 0;
        if (s > 64)
            s = 64;
        memcpy(_editText, objectText.c_str(), s);

        //if (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))
            ImGui::SetKeyboardFocusHere(0);

        enteredText = _editText;

//        ImGui::SetCursorPos(ImVec2(x+5,y+height+5));
//        ImGui::OpenPopup("_autocomplete");

        ImGui::PushItemWidth(width - 8);
        if (ImGui::InputText("##in", _editText, 64,  ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll, &nameChanged, (void*)this)) {
            finishedEditingText();
        }
        updated(UIObject::oAutocomplete);

//        ImGui::SetTooltip("menu");

        //((IUView*)_parent)->mouseEnabled = false;

    }

    if (AppController::fixedWidthFont())
    ImGui::PopFont();

    ImGui::EndGroup();
}

void UIObject::finishedEditingText()
{
    printf("edited\n");

    //((IUView*)_parent)->mouseEnabled = true;

    // fix
    windowController()->restoreContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ClearInputCharacters();
    io.MouseDoubleClicked[0] = false;
    for (int i = 0; i < 512; i++)
        io.KeysDown[i] = false;

    _objectReplaceMode = false;
    data.emptyBox = false;
    windowController()->isEditingText = false;
    objectText = _editText;

    // separate
    updated(oObjectChanged);
};

void UIObject::clearEditText()
{
    _editText[0] = '\0';
}

 void UIObject::onMouseDoubleClickEdited(ImVec2 pos)

{
    //                assert(windowController());
    windowController()->isEditingText = true;

    windowController()->restoreContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ClearInputCharacters();
    io.MouseDoubleClicked[0] = false;

    _objectReplaceMode = true;
};
