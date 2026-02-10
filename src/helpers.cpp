#include <complex>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <pwd.h>
#include <sys/types.h>
#include "include/helpers.hpp"


std::string expandPath(const std::string &path) {
    if (path.empty() || path[0] != '~') {
        return path;
    }

    if (path.size() >= 1 || path[1] == '/') {
        const char* home = getenv("HOME");

        if (!home) {
            struct passwd* pw = getpwuid(getuid());
            home = pw ? pw->pw_name : ".";
        }

        if (path.length() == 1) {
            return (std::string)home;
        }
        return std::string(home) + path.substr(1);
    }
}

std::string expandEnvVars(std::string &token) {
    std::string env_var;
    std::size_t i = 0;

    while (i < token.length()) {
        if (token[i] == '$') {
            i++;
            std::string var_name = "";

            if (token[i] == '{') {
                i++;

                while (i < token.size() && token[i] != '}') {
                    var_name += token[i];
                }

                if (i < token.size()) i++;
            }

            else {
                while (i < token.size() && (std::isalnum(token[i]) || token[i] == '_')) {
                    var_name += token[i++];
                }
            }

            if (!var_name.empty()) {
                const char* val = std::getenv(var_name.c_str());
                if (val) {
                    env_var += val;
                }
            }
        }

        else {
            env_var += token[i];
            i++;
        }
    }
    return env_var;
}


