## Laboratory work in C++
### Description of this repository:
In this lab, we create a class with interface simplified text editor.
### Functionality:
1. The Type(char) c method inserts the character at the cursor position into the buffer.
2. The ShiftLeft() and ShiftRight() methods move the cursor. The cursor is never
may go beyond the buffer boundaries.
3. The Backspace() method removes the character to the left of the cursor.
4. The Undo() method rolls back the last action listed above.
5. The Redo() method reapplies the action that was canceled.
6. The const std::string &GetText() method returns the current state
buffers;
