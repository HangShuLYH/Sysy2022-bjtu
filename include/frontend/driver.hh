#pragma once

// CHANGE: added <fstream> for new std::ifstream member "instream":
#include <fstream>
#include <string>
#include <map>

// Generated by bison:
#include "parser.hh"

// CHANGE: replaced `#define YY_DECL ...` here with #include of new
// lexer class:
#include "FlexLexer.hh"

// Conducting the whole scanning and parsing of Calc++.
class driver
{
public:
    driver ();
    virtual ~driver ();
    // CHANGE: add lexer object as a member
    FFlexLexer lexer;
    // CHANGE: add ifstream object as a member
    std::ifstream instream;
    // Handling the scanner.
    void scan_begin ();
    void scan_end ();
    // Run the parser on file F.
    // Return 0 on success.
    CompUnit* parse (const std::string& f);
    // The name of the file being parsed.
    // Used later to pass the file name to the location tracker.
    std::string file;
    // Error handling.
    void error (const yy::location& l, const std::string& m);
    void error (const std::string& m);

    CompUnit* root = nullptr;
};
