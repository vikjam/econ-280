#include <iostream>
#include <armadillo>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>

using namespace std;
using namespace arma;

extern "C"{
#include <gnuplot_i.h>
}

void plot2(double *ys1, double *ys2, int T, char *filename, char *title1, char *title2){
    gnuplot_ctrl * g = gnuplot_init();


    gnuplot_cmd(g, "set terminal png");
    gnuplot_cmd(g, filename);
    gnuplot_setstyle(g, "lines");
    gnuplot_plot_x(g, ys1, T, title1);
    gnuplot_setstyle(g, "lines");
    gnuplot_plot_x(g, ys2, T, title2);
    gnuplot_close(g);
}

void plot(double *ys, int T, char *filename, char *title){
    gnuplot_ctrl * g = gnuplot_init();
    gnuplot_cmd(g, "set terminal png");
    gnuplot_cmd(g, filename);
    gnuplot_setstyle(g, "lines");
    gnuplot_plot_x(g, ys, T, title);
    gnuplot_close(g);
}

template<typename Num_type>
vector<vector<Num_type> > Getdata(string filename, size_t ignore_line_num = 0){
    ifstream reading_file;
    reading_file.open(filename, ios::in);
    if(!reading_file){
        throw invalid_argument(filename + string(" could not be opened."));
        exit(0);
    }

    string reading_line_buffer;
    
    //skip first ignore_line_num rows
    for(size_t line = 0; line < ignore_line_num; line++){
        getline(reading_file, reading_line_buffer);
        if(reading_file.eof()) break;
    }
        
    Num_type num;
    char comma;

    vector<vector<Num_type> > data;
        
    while(!reading_file.eof()){
        vector<Num_type> temp_data;
        getline(reading_file, reading_line_buffer);
        istringstream is(reading_line_buffer);
        while(!is.eof()){
            is >> num >> comma;
            temp_data.push_back(num);
        }
        data.push_back(temp_data);
    }

    return data;
}


//test                                                                       
int main(){
    //読み込みデータ格納先2次元vectorを用意する、今回の数値型はなんでも良い
    vector<vector<double>> data;

    string filename = "US_Data.csv";
    
    //read csv file by Getdata
    cout << "reading " << filename << "..." << endl;
    data = Getdata<double>(filename);

    int T = data.size(); 
    mat y(T, 1);
    mat X = ones<mat>(T, 2);
    for (int t = 0; t < T; t++){
        y(t, 0) = data[t][0];
        X(t, 1) = t+1;
    }
    
    mat param = solve(trans(X)*X, trans(X)*y);
    cout << "estimated coefficients" << endl;
    param.print();

    double y_tr [T];
    double y_array [T];
    for (int t = 0; t < T; t++){
        y_tr[t] = param[0] + param[1]*(t+1);
        y_array[t] = y[t];
    }
    plot2(y_array, y_tr, T,  "set output \"exercise04_d.png\"", "y", "ytr");
    
    double y_c [T];
    for (int t = 0; t < T; t++){
        y_c[t] = y[t] - y_tr[t];
    }
    plot(y_c, T,  "set output \"exercise04_e.png\"", "cyclical component");

    cin.get();

    return 0;
}