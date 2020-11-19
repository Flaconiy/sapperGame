#ifndef MINER_H
#define MINER_H
#include "cell.h"
#include "clock_shape.h"
//#include "../fltk_win64/include/FL/Fl_Double_Window.h"

static constexpr int cell_size = 40;
static constexpr int margin_left = 40;
static constexpr int margin_top = 40;
static constexpr int side_bar = 250;
static constexpr int button_h = 50;
static constexpr int button_w = 200;
//template<class T>
//class Vector_ref_cl : public Graph_lib::Vector_ref<T>{
//public:
//    Vector_ref_cl(): Graph_lib::Vector_ref<T>() {}
//    void clear(){
//        Graph_lib::Vector_ref<T>.v.clear();
//        Graph_lib::Vector_ref<T>.owned.clear();
//    }
//};


class Sapper : public Graph_lib::Window{
public:
    Sapper(Graph_lib::Point p);
    void set_img(std::string, int);
private:

    bool first_click{true};
    void set_bombs(int n, int ii, int jj);
    void new_game(int n);
    void quit();
    void clicked(void* widget);
    void new_game_menu();
    void new_game_show();
    void update_cells_around(int, int);
    void open_area (int i, int j);

    void end_game(int, int);

    static void cb_clicked(void* widget, void* win);
    static void cb_new_game(void* widget, void* win);
    static void cb_quit(void* widget, void* win);
    static void cb_size_10(void* widget, void* win);
    static void cb_size_15(void* widget, void* win);
    static void cb_size_20(void* widget, void* win);

    unsigned int num_of_bombs{0};
    unsigned int flags_counter{0};
    int num_of_rows{10};
//    void output(int n);

    Vector_ref_cl<Vector_ref_cl<Cell> > cells;
    Button_with_pw btn_quit;
    Button_with_pw btn_new_game;
    Button_with_pw btn_size_10;
    Button_with_pw btn_size_15;
    Button_with_pw btn_size_20;
    Graph_lib::Image* first_flag_counter{nullptr};
    Graph_lib::Image* second_flag_counter{nullptr};
    Clock_shape game_time;
};

bool is_consist (std::vector<std::tuple<int, int> > v, std::tuple<int, int> el);

#endif // MINER_H
