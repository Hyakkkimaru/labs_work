#include <iostream>
#include <string>
#include <vector>

class Editor {
private:
    std::string text;
    int cursorPosition;
    char deletedChar;
    std::vector<std::string> history;
    std::vector<std::string> redoHistory;

public:
    Editor() : cursorPosition(0), deletedChar(' '), history(), redoHistory() {}

    void Type(char c) {
        text.insert(cursorPosition, 1, c);
        cursorPosition++;
        history.push_back("Type");
    }

    void ShiftLeft() {
        if (cursorPosition > 0) {
            cursorPosition--;
            history.push_back("ShiftLeft");
        }
    }

    void ShiftRight() {
        if (cursorPosition < text.size()) {
            cursorPosition++;
            history.push_back("ShiftRight");
        }
    }

    void Backspace() {
        if (cursorPosition > 0) {
            deletedChar = text[cursorPosition - 1];
            text.erase(cursorPosition - 1, 1);
            cursorPosition--;
            history.push_back("Backspace");
        }
    }

    void Undo() {
        if (!history.empty()) {
            if (history.back() == "Type") {
                text.erase(cursorPosition - 1, 1);
                cursorPosition--;
            }
            else if (history.back() == "ShiftLeft") {
                cursorPosition++;
            }
            else if (history.back() == "ShiftRight") {
                cursorPosition--;
            }
            else if (history.back() == "Backspace") {
                text.insert(cursorPosition, 1, deletedChar);
                cursorPosition++;
            }
            redoHistory.push_back(history.back());
            history.pop_back();
        }
    }

    void Redo() {
        if (!redoHistory.empty()) {
            if (redoHistory.back() == "Type") {
                text.insert(cursorPosition, 1, ' ');
                cursorPosition++;
            }
            else if (redoHistory.back() == "ShiftLeft") {
                cursorPosition--;
            }
            else if (redoHistory.back() == "ShiftRight") {
                cursorPosition++;
            }
            else if (redoHistory.back() == "Backspace") {
                text.erase(cursorPosition - 1, 1);
                cursorPosition--;
            }
            history.push_back(redoHistory.back());
            redoHistory.pop_back();
        }
    }

    const std::string& GetText() const {
        if (text.empty()) {
            throw std::runtime_error("Error: Text is empty.");
        }
        return text;
    }
};

int main() {
    Editor editor;
    editor.Type('I');
    editor.Type('T');
    editor.Type('c');
    editor.Type('o');
    editor.Type('l');
    editor.Type('l');
    editor.Type('e');
    editor.Type('g');
    editor.Type('e');

    std::cout << "Text: " << editor.GetText() << std::endl;

    editor.ShiftLeft();
    editor.Backspace();

    std::cout << "Text after backspace: " << editor.GetText() << std::endl;

    editor.Undo();

    std::cout << "Text after undo: " << editor.GetText() << std::endl;

    editor.Redo();

    std::cout << "Text after redo: " << editor.GetText() << std::endl;
}
