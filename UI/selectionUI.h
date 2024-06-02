#pragma once
#include <windows.h>
#include <vector>
#include <string>

class SelectionUI {
public:
    SelectionUI(COORD coords);
    void SetOptions(std::vector<std::string> options);
    void AddOption(std::string option);
    virtual void Render() const;
    virtual void MoveSelection(bool direction);
    //getters
    unsigned GetSelectionIndex() const;
    std::string GetOption(unsigned selectionIndex) const;
    std::vector<std::string> GetOptions() const;

protected:
    HANDLE CURR_HANDLE;
    unsigned selectionIndex;
    std::vector<std::string> options;
    COORD CONSOLE_COORDS;
};