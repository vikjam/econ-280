
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
                         