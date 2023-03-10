/// @author Camillus
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

namespace camillus {

namespace colors {
const string black = "\033[30m";
const string red = "\033[31m";
const string green = "\033[32m";
const string yellow = "\033[33m";
const string blue = "\033[34m";
const string purple = "\033[35m";
const string cyan = "\033[36m";
const string none = "\033[0m";
}  // namespace colors

/// @attention you can change colors here
auto string_color = colors::green;
auto char_color = colors::green;
auto number_color = colors::cyan;
auto variable_color = colors::purple;

map<string, vector<char>> symbols_color;

void print_highlighted(string expr) {
    /// @attention you can change colors here
    symbols_color[colors::yellow] = {',', ';'};
    symbols_color[colors::purple] = {'$'};

    if (expr == "$  = ") {
        expr = "$";
    }

    bool in_string = false;
    bool in_char = false;
    bool in_number = false;

    for (unsigned int i = 0; i < expr.size(); i++) {
        if (!in_number && !in_char && !in_string && isdigit(expr[i]) && i > 1 &&
            !(isalnum(expr[i - 1]) || expr[i - 1] == '_')) {
            cout << number_color;
            in_number = true;
        }

        if (in_number && expr[i] != '.' && expr[i] != '\'' && expr[i] != 'e' && !isdigit(expr[i])) {
            in_number = false;
            cout << colors::none;
        }

        if (expr[i] == '\'' && !in_string && !in_number) {
            if (in_char) {
                in_char = false;
                cout << expr[i];
                cout << colors::none;
            } else {
                in_char = true;
                cout << char_color;
                cout << expr[i];
            }
            continue;
        }

        if (expr[i] == '\"' && !in_char && !in_number) {
            if (in_string) {
                in_string = false;
                cout << expr[i];
                cout << colors::none;
            } else {
                in_string = true;
                cout << string_color;
                cout << expr[i];
            }
            continue;
        }

        if (in_string || in_char || in_number) {
            cout << expr[i];
            continue;
        }

        string current_color = colors::none;

        for (auto [color, symbols]: symbols_color) {
            if (find(symbols.begin(), symbols.end(), expr[i]) != symbols.end()) {
                current_color = color;
                break;
            }
        }

        if (isalnum(expr[i]) || expr[i] == '_') {
            current_color = variable_color;
        }

        cout << current_color;
        cout << expr[i];
        cout << colors::none;
    }
    cout << colors::none << endl;
}

/// @brief basic types
template <typename T>
string print(const T& A);

string print(const string& A);

string print(const char A[]);

string print(const char& A);

#ifdef __SIZEOF_INT128__
string print(__int128 A);

string print(unsigned __int128 A);
#endif

template <typename T, typename... Args>
string print(priority_queue<T, Args...> A);

template<typename T>
string print(const T &A) {
    stringstream s;
    s << A;
    return s.str();
}

string print(const string &A) {
    return '\"' + A + '\"';
}

string print(const char A[]) {
    return camillus::print((string) A);
}

string print(const char &A) {
    string res;
    res += '\'';
    res += A;
    res += '\'';
    return res;
}

#ifdef __SIZEOF_INT128__
string print(__int128 A) {
    if (A == 0) {
        return to_string(0);
    } else {
        string res;
        while (A) {
            int x = A % 10;
            res += '0' + x;
            A /= 10;
        }
        reverse(res.begin(), res.end());
        return res;
    }
}

string print(unsigned __int128 A) {
    if (A == 0) {
        return to_string(0);
    } else {
        string res;
        while (A) {
            int x = A % 10;
            res += '0' + x;
            A /= 10;
        }
        reverse(res.begin(), res.end());
        return res;
    }
}
#endif


/// @brief declarations
template<typename T, typename = void>
struct is_iterable : std::false_type {};

template<typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>())),
                                  decltype(std::end(std::declval<T>()))>> : std::true_type {};

template<typename T> concept IS_ITERABLE = is_array<T>()() || is_iterable<T>()();

template<IS_ITERABLE T>
string print(const T &A);

template<typename... Args>
string print(const pair<Args...> &A);

template<typename T, size_t... I>
string printTuple(const T &A, index_sequence<I...>);

template<typename... Args>
string print(const tuple<Args...> &A);

template<typename T, typename... Args>
string print(stack<T, Args...> A);

template<typename T, typename... Args>
string print(priority_queue<T, Args...> A);

/// @brief definitions
template<IS_ITERABLE T>
string print(const T &A) {
    string res;
    res += '{';
    for (const auto &item: A) {
        res += print(item);
        res += ", ";
    }
    res.pop_back();
    res.back() = '}';
    return res;
}

template<typename... Args>
string print(const pair<Args...> &A) {
    return '(' + print(A.first) + ", " + print(A.second) + ')';
}

template<typename T, size_t... I>
string printTuple(const T &A, index_sequence<I...>) {
    string res;
    res += '(';
    (..., (res += print(get<I>(A)) + ", "));
    res.pop_back();
    res.back() = ')';
    return res;
}

template<typename... Args>
string print(const tuple<Args...> &A) {
    return printTuple(A, make_index_sequence<sizeof...(Args)>());
}

template<typename T, typename... Args>
string print(stack<T, Args...> A) {
    if (A.empty()) {
        return "[]";
    }
    vector<T> B;
    while (!A.empty()) {
        B.push_back(A.top());
        A.pop();
    }
    reverse(B.begin(), B.end());
    return print(B);
}

template<typename T, typename... Args>
string print(priority_queue<T, Args...> A) {
    if (A.empty()) {
        return "{}";
    }
    vector<T> B;
    while (!A.empty()) {
        B.push_back(A.top());
        A.pop();
    }
    reverse(B.begin(), B.end());
    string res = print(B);
    res.front() = '{';
    res.back() = '}';
    return res;
}

/// @brief many arguments
string print() {
    return string();
}

template<typename T, typename... Args>
string print(const T &first, const Args &... args) {
    if (sizeof...(args)) {
        return camillus::print(first) + ", " + camillus::print(args...);
    } else {
        return camillus::print(first);
    }
}
}  // namespace camillus

#define debug(x...) camillus::print_highlighted((string)"$ " + #x + " = " + camillus::print(x))
