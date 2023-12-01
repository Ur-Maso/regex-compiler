#include "exprs.h"
struct group_t {
    int lineID = 0;
    enum class Kind { 
        regex, string
    } kind = Kind::string;
    char openC = '"';
    string value = "";
    map<string, string> vars {
        { "s", " " },
        { "id", "[a-zA-Z][a-zA-Z0-9_]*" },
        { "int", "(-|\\+)?[0-9]+" },
        { "uint", "\\+?[0-9]+" },
        { "double", "%int([.,][0-9]+)?" },
        { "udouble", "%uint([.,][0-9]+)?" }
    };
};
typedef map<string, group_t> groupsData;
groupsData parse(std::ifstream& file) {
    groupsData d;
    string groupName;
    group_t current;
    size_t spaceOffset = 0;
    struct {
        bool insideVar = false;
        size_t spaceOffset;
        string name = "";
        string val = "";
        void clear(void) {
            insideVar = false;
            name.clear(), val.clear();
            // we may don't touch spaceOffset
        }
    } var;
    for (size_t i = 0; !file.eof(); i++) { // main
        std::smatch result;
        string line;
        std::getline(file, line);
        debug("Got line: ", line);
        if (std::regex_search(line, result, regex_group)) {
            if (!groupName.empty()) d[groupName] = current;
            var.clear();
            current.lineID = i;
            spaceOffset = result[1].str().size();
            current.kind = result[2] == "regex" ? group_t::Kind::regex : group_t::Kind::string;
            if (result[3] != "") current.openC = result[3].str()[0];
            groupName = result[4];
        } else if (groupName.empty()) {
            continue;
        } else if (var.insideVar) {
            // handle multiline variable
            size_t j = 0;
            for (size_t size = line.size(); j < size; j++) {
                if (line[j] != ' ') break;
            }
            if (j < var.spaceOffset) {
                current.vars[var.name] = var.val;
                var.clear();
            } else {
                var.val += line;
                continue;
            }
        }
        /*
            We check here for regex group value
            It must be at least at one space over than group declares
        */
        bool wasC;
        // check if the line space offset is bigger than group declaration offset
        size_t j = 0;
        for (; j <= spaceOffset; j++) {
            if (line[j] != ' ') goto end;
        }
        // use the previous j to cycle onto rest of string
        wasC = false; // needs to check if there was non-space character previously (information for var decls)
        for (size_t size = line.size(); j < size; j++) {
            const char& c = line[i];
            if      (c == ' ')  continue;     // skip spaces
            else if (c == '#')  break;        // skip comments
            else if (var.insideVar) {
                if (c == '=') {
                    // well, the variable is rest of line
                    line.erase(line.begin(), line.begin() + j + 1 /* excluding current '=' */ );
                    current.vars[var.name] = line;
                    var.clear();
                    // end for current line
                    break;
                } else if (c == ':') {
                    // multiline variable
                    // same as above but without data clearing
                    line.erase(line.begin(), line.begin() + j + 1 /* excluding current ':' */ );
                    current.vars[var.name] = line;
                    break;
                }
                // this character is name of variable
                if (!std::isalnum(c)) err(i, ", ", j, ": Incorrect var name");
                var.name += c;
            } else if (c == '$') {
                debug("Found variable declaration: ", i, ":", j);
                if (!wasC) {
                    // variable declaration
                    var.spaceOffset = j;
                    char firstC = '\0'; // \0 means line is ended before any character encountered
                    for (; j < size; j++) {
                        if (line[j] != ' ')
                            firstC = line[j]; break; // first character of name
                    }
                    // \0
                    if      (!firstC)     warning(i, ", ", j, ": This could be incorrect variable declaration");
                    else if (!isalpha(c)) err    (i, ", ", j, ": Incorrect var name");
                    var.name += firstC;
                }
                // else just a terminate character
            } else wasC = true;     // tell that there were characters before '$'
        }
        end:
        continue; // to avoid warning: label at end of compound ...
    } // main
    d[groupName] = current;
    return d;
}