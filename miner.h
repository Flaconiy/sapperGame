#ifndef MINER_H
#define MINER_H
#include "cell.h"
#include "vector_ref_cl.h"

static constexpr int cell_size = 40;
static constexpr int margin_left = 40;
static constexpr int margin_top = 40;
static constexpr int side_bar = 200;
static constexpr int button_h = 50;
static constexpr int button_w = 150;
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
private:

    bool first_click{true};
    void set_bombs(int n, int ii, int jj);
    void new_game(int n);
    void quit();
    void change_mode();
    void clicked(void* widget);
    void new_game_menu();
    void new_game_show();
    void update_cells_around(int, int);

    void end_game();
    void start_opening(int i, int j);

    static void cb_clicked(void* widget, void* win);
    static void cb_new_game(void* widget, void* win);
    static void cb_quit(void* widget, void* win);
    static void cb_change_mode(void* widget, void* win);
    static void cb_size_10(void* widget, void* win);
    static void cb_size_15(void* widget, void* win);
    static void cb_size_20(void* widget, void* win);

    unsigned int num_of_bombs{0};
    unsigned int flags_counter{0};
    bool gamemode{true};
    int num_of_rows{10};

    Vector_ref_cl<Vector_ref_cl<Cell> > cells;
    Graph_lib::Button btn_quit;
    Graph_lib::Button btn_new_game;
    Graph_lib::Button btn_change_mode;
    Graph_lib::Out_box curr_out;
    Graph_lib::Button btn_size_10;
    Graph_lib::Button btn_size_15;
    Graph_lib::Button btn_size_20;
};

#endif // MINER_H
