#include "SelectionUI.h"
#include <iostream>
#include "../Utils/constants.h"

SelectionUI::SelectionUI(COORD coords) : CONSOLE_COORDS(coords), selectionIndex(0) {
    CURR_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
}

void SelectionUI::SetOptions(std::vector<std::string> options) {
    this->options = options;
}

void SelectionUI::AddOption(std::string option) {
    options.push_back(option);
}

void SelectionUI::Render() const {
    for (size_t i = 0; i < options.size(); i++) {
        SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, static_cast<SHORT>(CONSOLE_COORDS.Y + i)});
        if (i == selectionIndex) {
            SetConsoleTextAttribute(CURR_HANDLE, Constants::SELECTED_COLOR);
            std::cout << options[i] << '\n';
            SetConsoleTextAttribute(CURR_HANDLE, Constants::DEFAULT_COLOR);
            continue;
        }
        std::cout << options[i] << '\n';
    }
}

void SelectionUI::MoveSelection(bool direction) {
    if (direction && selectionIndex < options.size() - 1) {
        selectionIndex++;
        Render();
    } else if (!direction && selectionIndex > 0) {
        selectionIndex--;
        Render();
    }
}

//getters
unsigned SelectionUI::GetSelectionIndex() const {
    return selectionIndex;
}
std::string SelectionUI::GetOption(unsigned selectionIndex) const {
    return options[selectionIndex];
}
std::vector<std::string> SelectionUI::GetOptions() const {
    return options;
}
