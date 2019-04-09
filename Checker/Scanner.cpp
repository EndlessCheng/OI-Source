#include "Scanner.hpp"
#include "Platforms/Platform.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
using DirIter = fs::directory_iterator;
std::vector<Data> scanData() {
    fs::path dir = fs::temp_directory_path() / "data";
    std::map<fs::path, fs::path> in, out;
    std::vector<Data> res;
    for(auto it : DirIter(dir)) {
        it.refresh();
        if(!it.is_regular_file())
            continue;
        auto cp = it.path(), name = cp.stem(),
             ext = cp.extension();
        if(!cp.has_extension() || ext == ".in") {
            if(out.count(name))
                res.push_back(Data(cp, out[name]));
            else
                in[name] = cp;
        } else if(ext == ".out" || ext == ".a" ||
                  ext == ".ans") {
            if(in.count(name))
                res.push_back(Data(in[name], cp));
            else
                out[name] = cp;
        }
    }
    std::sort(res.begin(), res.end());
    line("Auto Scan Result");
    std::cout << "task count:" << res.size()
              << std::endl;
    {
        uintmax_t maxInput = 0, maxOutput = 0;
        for(auto d : res) {
            maxInput = std::max(
                maxInput, fs::file_size(d.input));
            maxOutput = std::max(
                maxOutput, fs::file_size(d.output));
        }
        std::cout << "maxInput:"
                  << maxInput / 1048576.0 << " MB"
                  << std::endl;
        std::cout << "maxOutput:"
                  << maxOutput / 1048576.0 << " MB"
                  << std::endl;
    }
    return res;
}
fs::path scanExec() {
    std::set<fs::path> blacklist{ "checker",
                                  "charCounter" };
    fs::file_time_type mft;
    fs::path res;
    for(auto it : DirIter(fs::current_path())) {
        it.refresh();
        if(!it.is_regular_file())
            continue;
        auto cp = it.path(), name = cp.stem(),
             ext = cp.extension();
        if(ext != ".out" || blacklist.count(name))
            continue;
        auto cft = fs::last_write_time(cp);
        if(cft > mft)
            mft = cft, res = cp;
    }
    return fs::relative(res);
}
bool needUpdate() {
    fs::path self = selfPath();
    auto selfTime = fs::last_write_time(self);
    auto srcDir = readConfig("CheckerSrcDir");
    if(srcDir.empty()) {
        std::cout << "\033[33mPlease specify the "
                     "source code's path in "
                     "checker.config\033[0m"
                  << std::endl;
        return false;
    }
    for(auto p :
        fs::recursive_directory_iterator(srcDir)) {
        p.refresh();
        if(p.is_regular_file() &&
           p.last_write_time() > selfTime)
            return true;
    }
    return false;
}
