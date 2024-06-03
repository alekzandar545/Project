#pragma once
#include <windows.h>
#include <vector>
#include <string>

/**
 * @class SelectionUI
 * @brief Represents a user interface for selecting options.
 * 
 * The SelectionUI class provides functionality for rendering a selection menu
 * and managing user input for selecting options.
 */
class SelectionUI {
public:
    /**
     * @brief Constructs a SelectionUI object with the specified coordinates.
     * @param coords The coordinates of the selection UI on the console.
     */
    SelectionUI(COORD coords);

    /**
     * @brief Constructs a SelectionUI object by copying another SelectionUI object.
     * @param other The SelectionUI object to be copied.
     */
    SelectionUI(const SelectionUI& other) = default;

    /**
     * @brief Default destructor.
     */
    ~SelectionUI() = default;

    /**
     * @brief Sets the options available for selection.
     * @param options A vector of strings representing the available options.
     */
    void SetOptions(std::vector<std::string> options);

    /**
     * @brief Adds an option to the list of available options.
     * @param option The option to be added.
     */
    void AddOption(std::string option);

    /**
     * @brief Renders the selection UI on the console.
     */
    virtual void Render() const;

    /**
     * @brief Moves the selection up or down based on the specified direction.
     * @param direction If true, moves the selection down. If false, moves the selection up.
     */
    virtual void MoveSelection(bool direction);

    /**
     * @brief Gets the index of the currently selected option.
     * @return The index of the currently selected option.
     */
    unsigned GetSelectionIndex() const;

    /**
     * @brief Gets the option at the specified selection index.
     * @param selectionIndex The index of the option to retrieve.
     * @return The option at the specified selection index.
     */
    std::string GetOption(unsigned selectionIndex) const;

    /**
     * @brief Gets all the available options.
     * @return A vector of strings representing all the available options.
     */
    std::vector<std::string> GetOptions() const;

protected:
    HANDLE CURR_HANDLE; /**< The handle to the console output buffer. */
    unsigned selectionIndex; /**< The index of the currently selected option. */
    std::vector<std::string> options; /**< The available options. */
    COORD CONSOLE_COORDS; /**< The coordinates of the selection UI on the console. */
};