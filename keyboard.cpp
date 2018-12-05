#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <type_traits>
const char* const key[] = {
    "continue", "friend", "true", "decltype", "goto",
    "reinterpret_cast", "try", "asm", "default", "if",
    "return", "typedef", "auto", "delete", "inline",
    "short", "typeid", "bool", "do", "int", "signed",
    "typename", "break", "double", "long", "long long",
    "sizeof", "union", "case", "dynamic_cast",
    "mutable", "static", "unsigned", "catch", "else",
    "namespace", "static_assert", "using", "char",
    "enum", "new", "static_cast", "virtual",
    "char16_t", "char32_t", "explict", "noexcept",
    "struct", "void", "export", "nullptr", "switch",
    "volatile", "class", "extern", "operator",
    "template", "wchar_t", "const", "false", "private",
    "this", "while", "constexpr", "float", "protected",
    "thread_local", "const_cast", "for", "public",
    "throw", "Impl", "ans", "merge", "read", "addEdge",
    "split", "998244353", "size", "siz", "modify",
    "query", "build", "DFS", "dinic", "MCMF", "dp",
    "mod", "powm", "solve", "check", "col", "dfn",
    "low", "sub", "write", "output", "input", "FFT",
    "init", "pre", "NTT", "alloc", "create", "icnt",
    "ecnt", "ccnt", "cnt", "id", "find", "getRandom",
    "splay", "push", "update", "topSort", "extend",
    "gcd", "lucas", "inv", "fac", "std", "sort",
    "unique", "lower", "upper", "_bound", "root", "fa",
    "LCA", "son", "len", "fabs", "sqrt", "vector",
    "map", "set", "multi", "erase", "priority_queue",
    "unordered_", "prev", "next", "nxt", "iterator",
    "freopen", "getchar", "scanf", "printf", "string",
    "push_back", "pop_back", "insert", "erase",
    "count", "clear", "reserve", "find", "stream",
    "arr", "top", "psiz", "gauss", "queue", "cstdio",
    "cstring", "cmath", "climits", "cstdlib",
    "algorithm", "cctype", "MST", "bid", "begin",
    "end", "Node", "val", "src", "sum", "delta", "sub",
    "memcpy", "memset", "scan", "last", "cur", "bit",
    "dst", "move", "calc", "swap", "exgcd",
    "convexHull", "Vec", "Line", "cross", "dot",
    "length", "area", "HPI", "dir", "ori", "tmp",
    "Circle", "dis", "#include", "#define", "angle",
    "[i]", "%mod", "phi", "pos", "aug", "intersect",
    "final", "override", "random_shuffle",
    "next_permutation", "nth_element", "push_heap",
    "pop_heap", "Yes", "No", "No Solution", "maxv",
    "minv", "?:", "equal", "inf", "eps", "reset",
    "pair", "first", "second", "time", "clock", "eval",
    "heap", "hash", "LUT", "clone"
                           ""
};
constexpr int size = std::extent<decltype(key)>::value,
              cnt = 10, fac = 500;
int id[size];
using Clock = std::chrono::high_resolution_clock;
int main() {
    std::random_device dev;
    for(int i = 0; i < size; ++i)
        id[i] = i;
    std::shuffle(id, id + size, dev);
    int count = 0;
    auto beg = Clock::now();
    std::cout.precision(0);
    for(int i = 0; i < size; i += cnt) {
        int end = std::min(size, i + cnt);
        std::string str;
        for(int j = i; j < end; ++j) {
            str += key[id[j]];
            str.push_back(' ');
        }
        str.pop_back();
        auto limit = 1000000LL * str.size() * fac;
        Clock::duration t;
        while(true) {
            std::cout << "P " << str << std::endl
                      << "A ";
            auto beg = Clock::now();
            std::string input;
            std::getline(std::cin, input);
            count += input.size();
            t = Clock::now() - beg;
            if(input == str && t.count() <= limit)
                break;
            std::cout << (input != str ? "WA" : "TLE")
                      << std::endl;
        }
        auto mt = t.count() * 1e-9 / 60;
        std::cout << "group " << i / cnt << " ("
                  << std::fixed << (100.0 * end / size)
                  << "%) " << (str.size() / mt)
                  << " char/min" << std::endl;
    }
    auto t = (Clock::now() - beg).count() * 1e-9 / 60;
    std::cout << std::fixed << (count / t)
              << " char/min" << std::endl;
    while(true)
        ;
    return 0;
}
