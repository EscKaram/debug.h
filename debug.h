/// @author Camillus
#pragma once
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

namespace camillus {

    namespace colors {
        static const string black = "\033[30m";
        static const string red = "\033[31m";
        static const string green = "\033[32m";
        static const string yellow = "\033[33m";
        static const string blue = "\033[34m";
        static const string purple = "\033[35m";
        static const string cyan = "\033[36m";
        static const string none = "\033[0m";
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

        auto set_color = [&result](const string &color) {
#ifdef WINDOWS

#else
            result += color;
#endif
        };

        for (unsigned int i = 0; i < expr.size(); i++) {
            if (!in_number && !in_char && !in_string && isdigit(expr[i]) && i > 1 &&
                !(isalnum(expr[i - 1]) || expr[i - 1] == '_')) {
                set_color(number_color);
                in_number = true;
            }

            if (in_number && expr[i] != '.' && expr[i] != '\'' && expr[i] != 'e' && !isdigit(expr[i])) {
                in_number = false;
                set_color(colors::none);
            }

            if (expr[i] == '\'' && !in_string && !in_number) {
                if (in_char) {
                    in_char = false;
                    result += expr[i];
                    set_color(colors::none);
                } else {
                    in_char = true;
                    set_color(char_color);
                    result += expr[i];
                }
                continue;
            }

            if (expr[i] == '\"' && !in_char && !in_number) {
                if (in_string) {
                    in_string = false;
                    result += expr[i];
                    set_color(colors::none);
                } else {
                    in_string = true;
                    set_color(string_color);
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

            set_color(current_color);
            result += expr[i];
            set_color(colors::none);
        }
        set_color(colors::none);
        return result;
    }

    template <typename, typename = void>
    constexpr bool is_iterable{};

    template <typename T>
    constexpr bool is_iterable<
            T,
            std::void_t< decltype(std::declval<T>().begin()),
                    decltype(std::declval<T>().end())
            >
    > = true;

    template<typename T> concept IS_ITERABLE = is_iterable<T>;
    template<typename T> concept IS_ARRAY = is_array<T>()();

/// @brief declarations

    template<typename T>
    string print(const T &A);

    template<IS_ITERABLE T>
    string print(const T &A);

    template<IS_ARRAY T>
    string print(const T &A);

    template <class T, size_t... I>
    string printTuple(const T& A, std::index_sequence<I...>);

    template <class... T>
    string print(const std::tuple<T...>& A);

    template<typename... Args>
    string print(const pair<Args...> &A);

/// @brief basic types

    string print(const char &A) {
        string res;
        res += '\'';
        res += A;
        res += '\'';
        return res;
    }

    string print(const unsigned char &A) {
        return print(static_cast<short>(A));
    }

    string print(const string &A) {
        string res;
        res += '\"';
        res += A;
        res += '\"';
        return res;
    }

    string print(const char *A) {
        string res;
        res += '\"';
        res += A;
        res += '\"';
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

/// @brief definitions

    template <class T, size_t... I>
    string printTuple(const T& A, std::index_sequence<I...>) {
        stringstream s;
        s << '(';
        (..., (s << (I == 0 ? "" : ", ") << print(get<I>(A))));
        s << ')';
        return s.str();
    }

    template <class... T>
    string print(const std::tuple<T...>& A) {
        return printTuple(A, std::make_index_sequence<sizeof...(T)>());
    }

    template<typename... Args>
    string print(const pair<Args...> &A) {
        return '(' + print(A.first) + ", " + print(A.second) + ')';
    }

    template<IS_ITERABLE T>
    string print(const T &A) {
        string res;
        res += '{';
        for (const auto &item : A) {
            res += print(item);
            res += ", ";
        }
        res.pop_back();
        res.back() = '}';
        return res;
    }

    template<IS_ARRAY T>
    string print(const T &A) {
        string res;
        res += '{';
        for (const auto &item : A) {
            res += print(item);
            res += ", ";
        }
        res.pop_back();
        res.back() = '}';
        return res;
    }

    template<typename T>
    string print(const T &A) {
        return (stringstream() << A).str();
    }

/// @brief many arguments

    string print() {
        return "\b\b\b\b";
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

#define debug(x...) cout << camillus::highlighted((stringstream() << "$ " << #x << " = " << camillus::print(x)).str()) << endl
