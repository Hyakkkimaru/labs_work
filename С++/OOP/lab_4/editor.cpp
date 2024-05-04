#include <iostream>
#include <string>
#include <stack>

class Command {
public:
    virtual void Execute() = 0;
    virtual void Undo() = 0;
};

class TypeCommand : public Command {
private:
    std::string& buffer;
    char ch;
    size_t pos;

public:
    TypeCommand(std::string& buf, char c, size_t p) : buffer(buf), ch(c), pos(p) {}

    void Execute() override {
        buffer.insert(pos, 1, ch);
    }

    void Undo() override {
        buffer.erase(pos, 1);
    }
};

class DeleteCommand : public Command {
private:
    std::string& buffer;
    size_t pos;
    char deletedChar;

public:
    DeleteCommand(std::string& buf, size_t p, char ch) : buffer(buf), pos(p), deletedChar(ch) {}

    void Execute() override {
        deletedChar = buffer[pos - 1];
        buffer.erase(pos - 1, 1);
    }

    void Undo() override {
        buffer.insert(pos - 1, 1, deletedChar);
    }
};

class TextEditor {
private:
    std::string buffer;
    size_t cursorPos;
    std::stack<Command*> undoStack;
    std::stack<Command*> redoStack;

public:
    TextEditor() : cursorPos(0) {}

    void Type(char ch) {
        Command* cmd = new TypeCommand(buffer, ch, cursorPos);
        cmd->Execute();
        undoStack.push(cmd);
        cursorPos++;
    }

    void ShiftLeft() {
        if (cursorPos > 0) {
            cursorPos--;
        }
    }

    void ShiftRight() {
        if (cursorPos < buffer.size()) {
            cursorPos++;
        }
    }

    void Backspace() {
        if (cursorPos > 0) {
            Command* cmd = new DeleteCommand(buffer, cursorPos, buffer[cursorPos - 1]);
            cmd->Execute();
            undoStack.push(cmd);
            cursorPos--;
        }
    }

    void Undo() {
        if (!undoStack.empty()) {
            Command* cmd = undoStack.top();
            cmd->Undo();
            redoStack.push(cmd);
            undoStack.pop();
        }
    }

    void Redo() {
        if (!redoStack.empty()) {
            Command* cmd = redoStack.top();
            cmd->Execute();
            undoStack.push(cmd);
            redoStack.pop();
        }
    }

    const std::string& GetText() const {
        return buffer;
    }
};

int main() {
    TextEditor editor;
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

    return 0;
}
