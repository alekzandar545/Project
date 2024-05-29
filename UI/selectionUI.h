#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <vector>

class SelectionUI{
public:
    SelectionUI(COORD coords){
        this->CONSOLE_COORDS = coords;
        selectionIndex = 0;
    }
    
    void SetOptions(std::vector<std::string> options){
        this->options = options;
    }
    void AddOption(std::string option){
        this->options.push_back(option);
    }

    virtual void Render() const{
        for (size_t i = 0; i < options.size(); i++)
        {
            SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, (short)(CONSOLE_COORDS.Y + i)});
            if(i==selectionIndex){
                SetConsoleTextAttribute(CURR_HANDLE, 22);
                std::cout << options[i] << '\n';
                SetConsoleTextAttribute(CURR_HANDLE, 8);
                continue;
            }
            std::cout << options[i] << '\n';
        }
    }
    virtual void MoveSelection(bool direction){//goes up for 0 down for 1
        if(direction && selectionIndex < options.size()-1){
            selectionIndex++;
            Render();
        }
        else if(!direction && selectionIndex > 0){
            selectionIndex--;
            Render();
        }
    }
    //getters
    unsigned GetSelectionIndex() const{//returns the index so later we use it in a switchCase for different functionalities
        return this->selectionIndex;
    }
    std::string GetOption(const unsigned selectionIndex) const{
        return options[selectionIndex];
    }
    std::vector<std::string> GetOptions() const{
        return options;
    }
protected:
    HANDLE CURR_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE); 
    unsigned selectionIndex;
    std::vector<std::string> options;
    COORD CONSOLE_COORDS = {0,0};
};
