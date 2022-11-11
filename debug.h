/// @author Camillus
/// Библиотек нужно, чтобы с помощью функции debug(...) выводить в красивом виде переменные, выражения.
/// Вы можете удобно менять цвета, для этого помотрите немного ниже ;)

#ifdef WIN32
#include "windows.h"
#endif

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

namespace __camillus__ {
    namespace colors {
        const string black = "\033[30m";
        const string red = "\033[31m";
        const string green = "\033[32m";
        const string yellow = "\033[33m";
        const string blue = "\033[34m";
        const string purple = "\033[35m";
        const string cyan = "\033[36m";
        const string none = "\033[0m";
    }

    /// все цвета, которые используются
    auto string_color = colors::green; // цвет для строк ("aboba")
    auto char_color = colors::green; // цвет для символов ('a')
    auto number_color = colors::blue; // цвет для чисел (123)
    auto sigh_color = colors::yellow; // цвет для символов, указанных в std::vector sighs
    auto variable_color = colors::purple; // цвет для переменных и типов данных (int, n)
    auto bracket_color = colors::none; // цвет для скобок, указанных в std::vector brackets
    auto dollar_color = colors::purple; // цвет для доллара

    vector<char> sighs = {',', ';'};
    vector<char> brackets = {'(', ')', '[', ']', '{', '}'};

    // функция, которая красит текст
    string highlighted(string expr) {
        bool in_string = false;
        bool in_char = false;
        bool in_number = false;
        string result;
        for (unsigned int i = 0; i < expr.size(); i++) {
            if (!in_number && !in_char && !in_string && isdigit(expr[i]) && i > 1 &&
                !(isalnum(expr[i - 1]) || expr[i - 1] == '_')) {
                result += number_color;
                in_number = true;
            }

            if (in_number && expr[i] != '.' && expr[i] != '\'' && expr[i] != 'e' && !isdigit(expr[i])) {
                in_number = false;
                result += colors::none;
            }

            if (expr[i] == '\'' && !in_string && !in_number) {
                if (in_char) {
                    in_char = false;
                    result += expr[i];
                    result += colors::none;
                } else {
                    in_char = true;
                    result += char_color;
                    result += expr[i];
                }
                continue;
            }

            if (expr[i] == '\"' && !in_char && !in_number) {
                if (in_string) {
                    in_string = false;
                    result += expr[i];
                    result += colors::none;
                } else {
                    in_string = true;
                    result += string_color;
                    result += expr[i];
                }
                continue;
            }

            if (in_string || in_char || in_number) {
                result += expr[i];
                continue;
            }


            if (find(sighs.begin(), sighs.end(), expr[i]) != sighs.end()) {
                result += sigh_color;
                result += expr[i];
                result += colors::none;
            } else if (find(brackets.begin(), brackets.end(), expr[i]) != brackets.end()) {
                result += bracket_color;
                result += expr[i];
                result += colors::none;
            } else if (isalnum(expr[i]) || expr[i] == '_') {
                result += variable_color;
                result += expr[i];
                result += colors::none;
            } else if (expr[i] == '$') {
                result += dollar_color;
                result += expr[i];
                result += colors::none;
            } else {
                result += expr[i];
            }
        }
        result += colors::none;
        return result;
    }

    // ниже написаны функции print, которые превращают переменные в текст
    template<typename key, typename comp>
    string
    print(__gnu_pbds::tree<key, __gnu_pbds::null_type, comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> A);

    template<typename T>
    string print(T A) {
        stringstream s;
        s << A;
        return s.str();
    }

    string print(string x) {
        return "\"" + x + "\"";
    }

    string print(char x) {
        string result = "\'";
        result += x;
        result += "\'";
        return result;
    }

    string print(const char *x) {
        string result = "\"";
        result += x;
        result += "\"";
        return result;
    }

    string print(bool x) {
        if (x) return "true";
        else return "false";
    }

    template<typename key, typename mapped, typename hash_fn>
    string print(__gnu_pbds::gp_hash_table<key, mapped, hash_fn> A);

    template<typename... Args>
    string print(pair<Args...> P);

    template<typename... Args>
    string print(vector<Args...> A);

    template<typename... Args>
    string print(set<Args...> A);

    template<typename... Args>
    string print(multiset<Args...> A);

    template<typename... Args>
    string print(unordered_set<Args...> A);

    template<typename T, size_t size>
    string print(const T (&array)[size]);

    template<typename... Args>
    string print(unordered_multiset<Args...> A);

    template<typename... Args>
    string print(map<Args...> A);

    template<typename... Args>
    string print(unordered_map<Args...> A);


    template<typename key, typename mapped, typename hash_fn>
    string print(__gnu_pbds::gp_hash_table<key, mapped, hash_fn> A) {
        string result;
        result += "{\n";
        for (auto it = A.begin(); it != A.end(); it++) {
            result += "\t" + __camillus__::print(it->first) + ":\t" + __camillus__::print(it->second);
            auto next = it;
            next++;
            if (next != A.end()) {
                result += ",";
            }
            result += "\n";
        }
        result += "}";
        return result;
    }

    template<class TupType, size_t... I>
    ostream &tuple_print(ostream &os,
                         const TupType &_tup, std::index_sequence<I...>) {
        os << "(";
        (..., (os << (I == 0 ? "" : ", ") << __camillus__::print(get<I>(_tup))));
        os << ")";
        return os;
    }

    template<class... T>
    std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &_tup) {
        return tuple_print(os, _tup, std::make_index_sequence<sizeof...(T)>());
    }

    template<typename... Args>
    string print(tuple<Args...> t) {
        stringstream s;
        s << t;
        return s.str();
    }

    template<typename T, size_t size>
    string print(const T (&array)[size]) {
        string result = "[";
        for (size_t i = 0; i < size; ++i) {
            result += __camillus__::print(array[i]);
            if (i != size - 1) {
                result += ", ";
            }
        }
        result += "]";
        return result;
    }

    template<typename... Args>
    string print(pair<Args...> P) {
        return "(" + __camillus__::print(P.first) + ", " + __camillus__::print(P.second) + ")";
    }

    template<typename... Args>
    string print(vector<Args...> A) {
        string result;
        result += "[";
        for (auto it = A.begin(); it != A.end(); it++) {
            result += __camillus__::print(*it);
            if (it != --A.end()) {
                result += ", ";
            }
        }
        result += "]";
        return result;
    }

    template<typename... Args>
    string print(set<Args...> A) {
        string result;
        result += "{";
        for (auto it = A.begin(); it != A.end(); it++) {
            result += __camillus__::print(*it);
            if (it != --A.end()) {
                result += ", ";
            }
        }
        result += "}";
        return result;
    }

    template<typename... Args>
    string print(multiset<Args...> A) {
        string result;
        result += "{";
        for (auto it = A.begin(); it != A.end(); it++) {
            result += __camillus__::print(*it);
            if (it != --A.end()) {
                result += ", ";
            }
        }
        result += "}";
        return result;
    }

    template<typename... Args>
    string print(unordered_set<Args...> A) {
        string result;
        result += "{";
        for (auto it = A.begin(); it != A.end(); it++) {
            result += __camillus__::print(*it);
            if (it != --A.end()) {
                result += ", ";
            }
        }
        result += "}";
        return result;
    }

    template<typename... Args>
    string print(unordered_multiset<Args...> A) {
        string result;
        result += "{";
        for (auto it = A.begin(); it != A.end(); it++) {
            result += __camillus__::print(*it);
            if (it != --A.end()) {
                result += ", ";
            }
        }
        result += "}";
        return result;
    }

    template<typename... Args>
    string print(map<Args...> A) {
        string result;
        result += "{\n";
        for (auto it = A.begin(); it != A.end(); it++) {
            result += "\t" + __camillus__::print(it->first) + ":\t" + __camillus__::print(it->second);
            if (it != --A.end()) {
                result += ",";
            }
            result += "\n";
        }
        result += "}";
        return result;
    }

    template<typename... Args>
    string print(unordered_map<Args...> A) {
        string result;
        result += "{\n";
        for (auto it = A.begin(); it != A.end(); it++) {
            result += "\t" + __camillus__::print(it->first) + ":\t" + __camillus__::print(it->second);
            auto next = it;
            next++;
            if (next != A.end()) {
                result += ",";
            }
            result += "\n";
        }
        result += "}";
        return result;
    }

    template<typename key, typename comp>
    string
    print(__gnu_pbds::tree<key, __gnu_pbds::null_type, comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> A) {
        string result;
        result += ("{");
        for (auto it = A.begin(); it != A.end(); it++) {
            result += __camillus__::print(*it);
            if (it != --A.end()) {
                result += (", ");
            }
        }
        result += ("}");
        return result;
    }

    template<typename... Args, typename T>
    string print(T first, Args... args) {
        return print(first) + ", " + __camillus__::print(args...);
    }

    template<typename... Args>
    string get(Args... args) {
        return " = " + __camillus__::print(args...);
    }

    string get() {
        return "";
    }
#ifdef WIN32
    auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    void for_windows(string text) {
        unsigned int i = 0;
        SetConsoleTextAttribute(hConsole, 15);
        auto starts = [&text](unsigned int i, string color) {
            return text.substr(i, color.size()) == color;
        };
        while (i < text.size()) {
            if (starts(i, colors::black)) {
                SetConsoleTextAttribute(hConsole, 0);
                i += colors::black.size();
            } else if (starts(i, colors::red)) {
                SetConsoleTextAttribute(hConsole, 4);
                i += colors::red.size();
            } else if (starts(i, colors::green)) {
                SetConsoleTextAttribute(hConsole, 2);
                i += colors::green.size();
            } else if (starts(i, colors::yellow)) {
                SetConsoleTextAttribute(hConsole, 6);
                i += colors::yellow.size();
            } else if (starts(i, colors::blue)) {
                SetConsoleTextAttribute(hConsole, 1);
                i += colors::blue.size();
            } else if (starts(i, colors::purple)) {
                SetConsoleTextAttribute(hConsole, 5);
                i += colors::purple.size();
            } else if (starts(i, colors::cyan)) {
                SetConsoleTextAttribute(hConsole, 3);
                i += colors::cyan.size();
            } else if (starts(i, colors::none)) {
                SetConsoleTextAttribute(hConsole, 7);
                i += colors::none.size();
            } else {
                cout << text[i];
                i += 1;
            }
            cout.flush();
        }
        SetConsoleTextAttribute(hConsole, 7);
        cout.flush();
    }
#endif
} // namespace __camillus__

#ifdef WIN32
#define debug(x...) __camillus__::for_windows(__camillus__::highlighted((string)"$ " + #x + " = " + __camillus__::get(x)) + "\n")
#else
#define debug(x...) cout << __camillus__::highlighted((string)"$ " + #x + __camillus__::get(x)) << endl
#endif
