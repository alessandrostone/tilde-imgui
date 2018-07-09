//

#include "PdCommonMenus.hpp"
void PdCommonFileMenu::shortcuts()
{
    shortcut(aFileNew, IUKey::Action() + IUKey::KeyN());
    shortcut(aFileOpen, IUKey::Action() + IUKey::KeyO());
    if (inPatch) {
        shortcut(aFileSave, IUKey::Action() + IUKey::KeyS());
        shortcut(aFileSaveAs, IUKey::Action() + IUKey::Shift() + IUKey::KeyS());
    }
    shortcut(aFileQuit, IUKey::Action() + IUKey::KeyQ());
}

void PdCommonFileMenu::drawContents()
{
    item("New patch window", aFileNew, IUKey::Action() + IUKey::KeyN());
    ImGui::Separator();
    item("Open patch in new window", aFileOpen, IUKey::Action() + IUKey::KeyO());
    if (inPatch) {
        item("Save patch", aFileSave, IUKey::Action() + IUKey::KeyS());
        item("Save patch as ...", aFileSaveAs, IUKey::Action() + IUKey::Shift() + IUKey::KeyS());
        item("Close patch window", aFileClose, IUKey::Action() +IUKey::KeyW());
    }
    ImGui::Separator();
    item("Quit", aFileQuit, IUKey::Action() + IUKey::KeyQ());
}

// ----------

void PdCommonWindowMenu::shortcuts()
{
    shortcut(aClearConsole, IUKey::Action() + IUKey::Shift() + IUKey::KeyL() );
}
void PdCommonWindowMenu::drawContents()
{
    item("Settings ...", aSettings);
    item("Audio / MIDI setup...", aAudioMIDI);
    ImGui::Separator();
    item("Clear console", aClearConsole, IUKey::Action() + IUKey::Shift() + IUKey::KeyL() );
}

void PdCommonMediaMenu::shortcuts()
{
    shortcut(aDSPOn,IUKey::Action() + IUKey::Slash());
    shortcut(aDSPOff,IUKey::Action() + IUKey::Dot() );
}

void PdCommonMediaMenu::drawContents()
{
    bool v;
    if (!dspOn)
        v = false;
    else
        v = *dspOn;
    item("DSP On", aDSPOn, IUKey::Action() + IUKey::Slash(), v);
    item("DSP Off", aDSPOff, IUKey::Action() + IUKey::Dot(), !v);
}

void PdCommonHelpMenu::drawContents()
{
    item("Pd Help", aHelp);
}

void PdCommonMenus::setWindowController(IUWindowController* w)
{
    menuFile.setWindowController(w);
    menuMedia.setWindowController(w);
    menuWindow.setWindowController(w);
    menuHelp.setWindowController(w);
}
