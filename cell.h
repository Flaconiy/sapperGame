#ifndef CELL_H
#define CELL_H

#include "../Graph_lib/Graph.h"
#include "../Graph_lib/Window.h"
#include "../Graph_lib/Simple_window.h"
#include "../Graph_lib/GUI.h"
#include <string>
#include "vector_ref_cl.h"

class Button_with_pw : public Graph_lib::Button{
public:
    Button_with_pw(Graph_lib::Point p, int w, int h, const std::string& label,  Graph_lib::Callback cb);
    Fl_Widget* get_pw() const {return pw;}
};


class Cell : public Button_with_pw{
public:
    Cell(Graph_lib::Point p, int size_, Graph_lib::Callback cb);
    void set_bomb(bool bomb_)   {bombed = bomb_;}
    void set_flag(bool flag_)   {flaged = flag_;}
    void set_open()             { opened = true;}
    void attach(Graph_lib::Window &win) override;

    bool is_bombed()   const {return bombed;}
    bool is_flaged()   const {return flaged;}
    bool is_opened()    const {return opened;}
    int bombs_around {0};
    void set_img(std::string name);
    void update_attach();

    Graph_lib::Image* img_ptr {nullptr};

private:
    bool bombed     {false};
    bool flaged     {false};
    bool opened     {false};
};
#endif // CELL_H
