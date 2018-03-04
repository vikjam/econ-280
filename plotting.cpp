#include "GNUPlot.h"
#include "GNUPlot.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <armadillo>
#include <string.h>

using namespace std;
using namespace arma;


void save_data(mat ys, string fn){

    ofstream out(fn);
    int n_rows = ys.n_rows;
    int n_cols = ys.n_cols;

    for (int r_i = 0; r_i < n_rows; r_i++){
        for (int c_i = 0; c_i < n_cols; c_i++)
            if (c_i != n_cols - 1)
                out << ys(r_i, c_i) <<" ";
            else
                out << ys(r_i, c_i) ;
        if (r_i != n_rows - 1)
            out << "\n";
    }
    out.close();
}

int plot_from_file(string data_fn, vector<int> data_ind, vector<string> labels, string title){

    vector<string> script;
    script.push_back("reset");
    script.push_back("set title \"" + title +"\"");
    for (int i = 0; i < data_ind.size(); i++){
        string ind = to_string(data_ind[i]+1);
        string label = labels[i];
        if (i == 0)
            script.push_back("plot \"" + data_fn + "\" using 1:"+ ind +" w l" +" title \""+label +"\"");
        else
            script.push_back("replot \"" + data_fn + "\" using 1:"+ ind +" w l"+" title \""+label +"\"");
    }
    
    GNUPlot plotter;
    plotter.open();
    plotter.execute(script);
    
    getchar(); // prevent graph to close
    
    plotter.write("exit");
    plotter.flush();
    plotter.close();
}

int plot(mat x, mat ys, vector<int> data_ind, vector<string> labels, string title){
    string temp_data_fn = "data";
    mat saved = join_rows(x, ys);
    save_data(saved, temp_data_fn);
    plot_from_file(temp_data_fn, data_ind, labels, title);
    remove(temp_data_fn.c_str());
}

int plot(mat x, mat ys, vector<int> data_ind, vector<string> labels){
    plot(x, ys, data_ind, labels, "");
}
