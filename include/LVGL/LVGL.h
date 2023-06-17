#include <initializer_list>
#include <vector>
using namespace std;

class Button {
public:
    void render ();
    void derender ();
};

class Text {
public: 
    void render ();
    void derender ();
};

class View {
private:
    vector<Button> buttons;
    vector<Text> texts;
    
public:
    View () = default;
    View (initializer_list<Button> buttons, initializer_list<Text> texts) : buttons(buttons), texts(texts) {};
    void derender ();
    void render ();
};