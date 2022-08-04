#include "driver.hh"
#include "parser.hh"
#include <sstream>
driver::driver (){}

driver::~driver ()
{
}

CompUnit* driver::parse (const std::string &f)
{
    file = f;
    instream.open(file);
    std::istringstream  poss_stringstream(preprocess());
    lexer.switch_streams(&poss_stringstream,0);
    yy::parser parser (*this);
    parser.parse ();
    scan_end ();
    return this->root;
}

void driver::error (const yy::location& l, const std::string& m)
{
    std::cerr << l << ": " << m << std::endl;
}

void driver::error (const std::string& m)
{
    std::cerr << m << std::endl;
}


void driver::scan_begin()
{
    // Try to open the file:
    instream.open(file);
    if( instream.good() ) {
        lexer.switch_streams(&instream, 0);
    } else if( file == "-" ) {
        lexer.switch_streams(&std::cin, 0);
    } else {
        error ("Cannot open file '" + file + "'.");
        exit (EXIT_FAILURE);
    }
}

void driver::scan_end ()
{
    instream.close();
}
std::string driver::preprocess() {
    std::string poss;

    int line_pos = 0;
    std::string line;
    std::string word;

    while (getline(instream, line, '\n')) {
        line_pos++;
        // std::cout << line<< std::endl;
        std::stringstream s;
        s << line;

        while (getline(s, word, ' ')) {
            int tab_num;
            tab_num = word.find_first_not_of("\t");
            word.erase(0, tab_num);
            //
            for (int i = 0; i < tab_num; i++) {
                poss += "\t";
            }

            if (word == "starttime();") {
                poss += "_sysy_starttime(";
                poss += std::to_string(line_pos);
                poss += "); ";
            } else if (word == "stoptime();") {
                poss += "_sysy_stoptime(";
                poss += std::to_string(line_pos);
                poss += "); ";
            } else {
                poss += word;
                poss += " ";
            }
        }
        poss += "\n";
    }
    // std::cerr<<poss<<std::endl;
    return poss;
}