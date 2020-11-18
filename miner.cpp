#include "miner.h"
#include "cell.h"
#include <ctime>
#include <iostream>


const int n0 = 10;
Sapper::Sapper(Graph_lib::Point p):
    Graph_lib::Window(p,  cell_size * n0 + 2 * margin_left + side_bar, cell_size * n0 + 2*margin_top, "SAPPER"),
    num_of_rows{n0},
    flags_counter{n0},
    btn_quit{Graph_lib::Point(p.x + 2*margin_left + cell_size * num_of_rows + (side_bar - button_w)/2,
                              p.y + 2*margin_top + cell_size * num_of_rows - 2*button_h), button_w, button_h, "QUIT", cb_quit},
    btn_change_mode{Graph_lib::Point(p.x + 2*margin_left + cell_size * num_of_rows + (side_bar - button_w)/2,
                                     p.y + 2*margin_top + cell_size * num_of_rows - 3*button_h), button_w, button_h, "[click on the field]", cb_change_mode},
    btn_new_game{Graph_lib::Point(p.x + 2*margin_left + cell_size * num_of_rows + (side_bar - button_w)/2,
                                  p.y + margin_top +button_w + button_h), button_w, button_h, "NEW GAME", cb_new_game},
    curr_out{Graph_lib::Point(p.x + 2*margin_left + cell_size * num_of_rows + (side_bar - button_w)/2,
                              p.y + margin_top), button_w, button_w, ""},
    btn_size_10{Graph_lib::Point(btn_new_game.loc.x, btn_new_game.loc.y), button_w/3, button_h, "10x10", cb_size_10},
    btn_size_15{Graph_lib::Point(btn_new_game.loc.x + button_w/3, btn_new_game.loc.y), button_w/3, button_h, "15x15", cb_size_15},
    btn_size_20{Graph_lib::Point(btn_new_game.loc.x + 2* button_w/3, btn_new_game.loc.y), button_w/3, button_h, "20x20", cb_size_20}
{
    attach(btn_quit);
    attach(btn_change_mode);
    attach(btn_new_game);
    attach(curr_out);
    attach(btn_size_10);
    attach(btn_size_15);
    attach(btn_size_20);
    new_game_show();
    new_game(n0);
}

void Sapper::set_bombs(int num_of_bombs, int ii, int jj){                 //only for vector with "clear" elements!
    if (num_of_bombs < 0) {
        return;
        std::cerr<<"TOO FEW BOMBS";
    }
    flags_counter = num_of_bombs;
    int n = cells.size();
    std::srand(time(0));
    int counter = 0;
    while(counter < num_of_bombs){
        int i = rand()%n;
        int j = rand()%n;
        if(i == ii and j == jj) continue;
        if(cells[i][j].is_bombed() == false){
            cells[i][j].set_bomb(true);
            update_cells_around(i,j);
            ++counter;
        }
    }
}


void Sapper::cb_new_game(void* widget, void* win){
    Graph_lib::reference_to<Sapper>(win).new_game_menu();
}
void Sapper::cb_quit(void* widget, void* win){
    Graph_lib::reference_to<Sapper>(win).quit();
}
void Sapper::cb_change_mode(void* widget, void* win){
    Graph_lib::reference_to<Sapper>(win).change_mode();
}
void Sapper::cb_clicked(void* widget, void* win){
    Graph_lib::reference_to<Sapper>(win).clicked(widget);
}
void Sapper::cb_size_10(void* widget, void* win){
    Graph_lib::reference_to<Sapper>(win).new_game(10);
}
void Sapper::cb_size_15(void* widget, void* win){
    Graph_lib::reference_to<Sapper>(win).new_game(15);
}
void Sapper::cb_size_20(void* widget, void* win){
    Graph_lib::reference_to<Sapper>(win).new_game(20);
}
void Sapper::new_game_menu(){
    btn_new_game.hide();
    btn_size_10.show();
    btn_size_15.show();
    btn_size_20.show();
}
void Sapper::new_game_show(){
    btn_new_game.show();
    btn_size_10.hide();
    btn_size_15.hide();
    btn_size_20.hide();
}


void Sapper::new_game(int n){
    btn_change_mode.label ="[click on the field]";

    first_click = true;
    new_game_show();
    size_range(0,0, 20000,20000);
    int hh = cell_size * n + 2*margin_top;
    int ww = cell_size * n + 4 * margin_left + side_bar;
    resize(ww,hh);
    size_range(ww,hh,ww,hh);
    for(int i = 0; i < cells.size(); ++i){
        for(int j = 0; j < cells[i].size(); ++j)
            detach(cells[i][j]);
    }
    cells.clear();
    for(int i = 0; i < n; ++i){
        cells.push_back(new Vector_ref_cl<Cell>);
        for(int j = 0; j < n; ++j){
            cells[i].push_back(new Cell{Graph_lib::Point(margin_left + i*cell_size, margin_top + j*cell_size), cell_size, cb_clicked});
            attach(cells[i][j]);
        }
    }
    num_of_bombs = (n-2) * 2;
    if (n == 10 or n == 9) num_of_bombs = 16;
    if (n == 15) num_of_bombs = 30;
    if (n == 20) num_of_bombs = 50;
    curr_out.put(num_of_bombs);
}

void Sapper::quit(){
    hide();
}
void Sapper::change_mode(){
    if(btn_change_mode.label == "[click on the field]") return;
    gamemode = !(gamemode);
    if(btn_change_mode.label == "MODE: BOMB") btn_change_mode.label = "MODE: FLAG";
    else btn_change_mode.label = "MODE: BOMB";
}
void Sapper::clicked(void *widget){
    Fl_Widget& w = Graph_lib::reference_to<Fl_Widget>(widget);
    int x = w.x() - margin_left;
    int y = w.y() - margin_top;
    int i = x / cell_size;
    int j = y / cell_size;


    if(first_click){
        first_click = false;
        set_bombs(num_of_bombs, i, j);
        curr_out.put(num_of_bombs);
        btn_change_mode.label = "MODE: BOMB";
    }


    Cell& c = cells[i][j];
    if(c.is_opened()) return;
    if(!gamemode){
        if(flags_counter == 0) return;
        c.set_flag(!c.is_flaged());
        if(!c.is_flaged()) {
            ++flags_counter;
            c.get_pw()->color(fl_rgb_color(195,195,195));
        }
        else{
            --flags_counter;
            c.get_pw()->color(Graph_lib::Color::white);
        }
        curr_out.put(flags_counter);
    }
    if(gamemode){
        if(c.is_flaged()) return;
        if(c.is_bombed()) end_game();
        else start_opening(i,j);
    }


    if(flags_counter == 0){
        int closed_counter = 0;
        for(int i = 0; i < cells.size(); ++i){
            for(int j = 0; j < cells.size(); ++j){
                if(cells[i][j].is_opened() == false) ++closed_counter;
            }
        }
        if(closed_counter == num_of_bombs) {
            end_game();
            curr_out.put("YOU WIN!!!");
        }
    }
}

void Sapper::end_game(){
    for(int i = 0; i < cells.size(); ++i){
        for(int j = 0; j < cells.size(); ++j){
            cells[i][j].set_open();
            if(cells[i][j].is_bombed()) {
                cells[i][j].show_bomb();
            }
            if(cells[i][j].is_flaged() and cells[i][j].is_bombed()==false){
                cells[i][j].get_pw()->color(Graph_lib::Color::red);
            }
            if(cells[i][j].is_flaged() and cells[i][j].is_bombed()){
                cells[i][j].get_pw()->color(Graph_lib::Color::dark_green);
            }
        }
    }
    Fl::redraw();
}

void Sapper::start_opening(int i, int j){
    if(cells[i][j].is_flaged()) return;
    if(cells[i][j].is_opened()) return;
    if(cells[i][j].is_bombed()) return;
    cells[i][j].set_open();
    cells[i][j].get_pw()->color(Graph_lib::Color::yellow);
    switch (cells[i][j].bombs_around) {
    case 0:
    {
        int n = cells.size();
        if(i>0) start_opening(i-1, j);
        if(i<n-1) start_opening(i+1, j);
        if(j>0) start_opening(i, j-1);
        if(j<n-1) start_opening(i, j+1);
        if(i>0 and j>0) start_opening(i-1, j-1);
        if(i>0 and j<n-1) start_opening(i-1, j+1);
        if(i<n-1 and j>0) start_opening(i+1, j-1);
        if(i<n-1 and j<n-1) start_opening(i+1,j+1);;
        break;
    }
    case 1:
        cells[i][j].label = "1";
        break;
    case 2:
        cells[i][j].label = "2";
        break;
    case 3:
        cells[i][j].label = "3";
        break;
    case 4:
        cells[i][j].label = "4";
        break;
    case 5:
        cells[i][j].label = "5";
        break;
    case 6:
        cells[i][j].label = "6";
        break;
    case 7:
        cells[i][j].label = "7";
        break;
    case 8:
        cells[i][j].label = "8";
        break;
    default:
        cells[i][j].label = "?";
        break;
    }
    Fl:redraw();
}

void Sapper::update_cells_around (int i, int j)
{
  if (i > 0)
  {
    if (!cells[i-1][j].is_bombed())
      cells[i-1][j].bombs_around++;
    if (j > 0)
      if (!cells[i-1][j-1].is_bombed())
        cells[i-1][j-1].bombs_around++;
    if (j < cells[i].size() - 1)
      if (!cells[i-1][j+1].is_bombed())
        cells[i-1][j+1].bombs_around++;
  }
  if (i < cells[i].size() - 1)
  {
    if (!cells[i+1][j].is_bombed())
      cells[i+1][j].bombs_around++;
    if (j > 0)
      if (!cells[i+1][j-1].is_bombed())
        cells[i+1][j-1].bombs_around++;
    if (j < cells[i].size() - 1)
      if (!cells[i+1][j+1].is_bombed())
        cells[i+1][j+1].bombs_around++;
  }
  if (j > 0)
    if (!cells[i][j-1].is_bombed())
      cells[i][j-1].bombs_around++;
  if (j < cells[i].size() - 1)
    if (!cells[i][j+1].is_bombed())
      cells[i][j+1].bombs_around++;
}
