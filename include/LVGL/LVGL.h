#include "display/lv_core/lv_obj.h"
#include "display/lvgl.h"
#include <initializer_list>
#include <stdexcept>
#include <vector>
#include <functional>
#include <string>
using namespace std;

class ToggleButton {
private:
    lv_obj_t* obj;
    lv_obj_t* label;
    int x, y, w, h;
    string name;
    lv_res_t (*func)(lv_obj_t*);

public:
    ToggleButton(
        string n, 
        int x, 
        int y, 
        int w, 
        int h,
        lv_res_t (*functest)(lv_obj_t*)
    ) : name(n), x(x), y(y), w(w), h(h), func(functest) {};

    void setText (string newText);
    void setPos (int newX=-1, int newY=-1);
    void setSize (int newW=-1, int newH=-1);

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
    vector<ToggleButton> buttons;
    vector<Text> texts;
    
public:
    View () = default;
    View (initializer_list<ToggleButton> buttons, initializer_list<Text> texts) : buttons(buttons), texts(texts) {};
    void derender ();
    void render ();
};