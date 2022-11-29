/// @author Camillus
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

namespace camillus {

    namespace colors {
        const string black = "\e[30m";
        const string red = "\e[31m";
        const string green = "\e[32m";
        const string yellow = "\e[33m";
        const string blue = "\e[34m";
        const string purple = "\e[35m";
        const string cyan = "\e[36m";
        const string none = "\e[0m";
    }  // namespace colors

/// @attention you can change colors here
    auto string_color = colors::green;
    auto char_color = colors::green;
    auto number_color = colors::cyan;
    auto variable_color = colors::purple;

    map<string, vector<char>> symbols_color;

    string highlighted(string expr) {
/// @attention you can change colors here
        symbols_color[colors::yellow] = {',', ';'};
        symbols_color[colors::purple] = {'$'};

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

            result += current_color;
            result += expr[i];
            result += colors::none;
        }
        result += colors::none;
        return result;
    }

/// @brief basic types
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
    template<typename... Args>
    string print(const pair<Args...> &A);

    template<typename T, size_t N>
    string print(const T (&A)[N]);

    template<typename T, size_t N>
    string print(const array<T, N> &A);

    template<typename T>
    string printIterable(const T &A);

    template<typename T>
    string printMapped(const T &A);

    template<typename... Args>
    string print(const vector<Args...> &A);

    template<typename... Args>
    string print(const deque<Args...> &A);

    template<typename... Args>
    string print(stack<Args...> A);

    template<typename T, typename... Args>
    string print(priority_queue<T, Args...> A);

    template<typename... Args>
    string print(const set<Args...> &A);

    template<typename... Args>
    string print(const unordered_set<Args...> &A);

    template<typename key, typename comp>
    string
    print(const __gnu_pbds::tree<key, __gnu_pbds::null_type, comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> &A);

    template<typename key, typename mapped, typename comp>
    string
    print(const __gnu_pbds::tree<key, mapped, comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> &A);

    template<typename... Args>
    string print(const map<Args...> &A);

    template<typename... Args>
    string print(const unordered_map<Args...> &A);

    template<typename... Args>
    string print(const __gnu_pbds::gp_hash_table<Args...> &A);

    template<typename... Args>
    string print(const __gnu_pbds::cc_hash_table<Args...> &A);

/// @brief definitions
    template<typename... Args>
    string print(const pair<Args...> &A) {
        string res;
        res += '(';
        res += camillus::print(A.first);
        res += ", ";
        res += camillus::print(A.second);
        res += ')';
        return res;
    }

    template<typename T, size_t N>
    string print(const T (&A)[N]) {
        string res;
        res += '[';
        for (size_t i = 0; i < N; i++) {
            res += camillus::print(A[i]);
            if (i + 1 == N) {
                res += ']';
            } else {
                res += ", ";
            }
        }
        return res;
    }

    template<typename T, size_t N>
    string print(const array<T, N> &A) {
        string res;
        res += '[';
        for (size_t i = 0; i < N; i++) {
            res += camillus::print(A[i]);
            if (i + 1 == N) {
                res += ']';
            } else {
                res += ", ";
            }
        }
        return res;
    }

    template<typename T>
    string printIterable(const T &A) {
        string res;
        res += '{';
        for (auto it = A.begin(); it != A.end(); it++) {
            res += camillus::print(*it);
            if (next(it) != A.end()) {
                res += ", ";
            }
        }
        res += '}';
        return res;
    }

    template<typename T>
    string printMapped(const T &A) {
        string res;
        res += "{\n";
        for (auto it = A.begin(); it != A.end(); it++) {
            res += '\t';
            res += camillus::print(it->first);
            res += ":\t";
            res += camillus::print(it->second);
            if (next(it) == A.end()) {
                res += "\n}";
            } else {
                res += ",\n";
            }
        }
        return res;
    }

    template<typename... Args>
    string print(const vector<Args...> &A) {
        string res = camillus::printIterable(A);
        res.front() = '[';
        res.back() = ']';
        return res;
    }

    template<typename... Args>
    string print(const deque<Args...> &A) {
        string res = camillus::printIterable(A);
        res.front() = '[';
        res.back() = ']';
        return res;
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
        return camillus::print(B);
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
        string res = camillus::print(B);
        res.front() = '{';
        res.back() = '}';
        return res;
    }

    template<typename... Args>
    string print(const set<Args...> &A) {
        return camillus::printIterable(A);
    }

    template<typename... Args>
    string print(const unordered_set<Args...> &A) {
        return camillus::printIterable(A);
    }

    template<typename key, typename comp>
    string
    print(const __gnu_pbds::tree<key, __gnu_pbds::null_type, comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> &A) {
        return camillus::printIterable(A);
    }

    template<typename key, typename mapped, typename comp>
    string
    print(const __gnu_pbds::tree<key, mapped, comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> &A) {
        return camillus::printMapped(A);
    }

    template<typename... Args>
    string print(const __gnu_pbds::gp_hash_table<Args...> &A) {
        return camillus::printMapped(A);
    }

    template<typename... Args>
    string print(const __gnu_pbds::cc_hash_table<Args...> &A) {
        return camillus::printMapped(A);
    }

/// @brief many arguments
    template<typename T, typename... Args>
    string print(const T &first, const Args &... args) {
        if (sizeof...(args)) {
            return camillus::print(first) + ", " + camillus::print(args...);
        } else {
            return camillus::print(first);
        }
    }

    string get() {
        return "";
    }

    template<typename... Args>
    string get(const Args &... args) {
        if (sizeof...(args)) {
            return (string) " = " + camillus::print(args...);
        }
    }
}  // namespace camillus

#define debug(x...) cout << camillus::highlighted((string)"$ " + #x + camillus::get(x)) << endl













/// @note I want 404 rows in code
