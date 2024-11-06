#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Command.h"

using namespace std;

class Input
{
    void start_lines();
    string next_line();

    std::string m_infile;
    std::vector<std::string> m_lines;
    std::vector<std::string>::iterator m_at_line;
    std::istream& input_stream;


public:
    Input(std::istream& input);
    void parse_and_store();
    shared_ptr<Command> world;
    vector< shared_ptr<Command> > start;
    vector< shared_ptr<Command> > steps;
    std::string outfile;
    vector<string> asserts;

    static shared_ptr<Command> parse_command(string line);
};

