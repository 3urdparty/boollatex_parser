#include "boollatex_parser.hpp"
#include <strfmt/strfmt.hpp>

string parseLatex(string word){
    return splitString(word, '.')[0];
}