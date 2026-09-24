#include <iostream>
#include <filesystem>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <chrono>
#include <cctype>
#include <algorithm>
#include <future>
//--[NameSpaces]--
namespace fs = std::filesystem;

//--[structs]--
struct sizedPath
{
    fs::path Path;
    uintmax_t size;
    fs::file_time_type lastOpened;
};

//--[MethodDeclaration]--
uintmax_t getDirSize(const fs::path &dir);
void findUnityLibs(const fs::path &dir, std::vector<sizedPath> &allPaths, uintmax_t &counter);
void asciiArt();
std::string shortSize(uintmax_t size);
bool argCheck(int argc, char *argv[]);
bool isUnityProj(const fs::path &dir);
std::string shortSize(uintmax_t size);
void printVector(const std::vector<sizedPath> &paths);
std::string toLower(const std::string &s);
void addSizeToDirs(std::vector<sizedPath> &paths);

//--[globalVars]--
const std::vector<std::string> skipDirs = {
    "$recycle.bin", "system volume information", "windows",
    "program files", "program files (x86)", "programdata",
    "$winreagent", "recovery",
    "steamapps", "steam", "epicgames", "battle.net",
    "origin games", "gog games",
    "node_modules", ".git", ".svn", "venv", ".venv",
    "__pycache__", ".gradle", ".nuget", "vendor",
    "obj"};
//--[real stuff]--
int main(int argc, char *argv[])
{

    std::vector<sizedPath> allPaths = {};
    uintmax_t counter = 0;
    if (!argCheck(argc, argv))
    {
        return EXIT_FAILURE;
    }
    asciiArt();
    findUnityLibs(argv[1], allPaths, counter);
    addSizeToDirs(allPaths);
    printVector(allPaths);

    return EXIT_SUCCESS;
}

bool isUnityProj(const fs::path &dir)
{

    if (fs::exists(dir / "Assets") && fs::exists(dir / "ProjectSettings" / "ProjectVersion.txt"))
    {
        return true;
    }
    return false;
}

void findUnityLibs(const fs::path &dir, std::vector<sizedPath> &allPaths, uintmax_t &counter)
{
    std::error_code er;

    for (auto const &d : fs::directory_iterator{dir, fs::directory_options::skip_permission_denied, er})
    {

        if(counter % 1000 == 0){
        std::cout << "searched:  " << counter << " - " << allPaths.size() << " projects found\r" << std::flush;
        }
        if (std::find(skipDirs.begin(), skipDirs.end(), toLower(d.path().filename().string())) != skipDirs.end())
        {
            continue;
        }
        if (!d.is_symlink() && d.is_directory())
        {

            if (isUnityProj(d))
            {

                allPaths.push_back({d, 0, fs::last_write_time(d.path() / "Assets")});
                   std::cout << "searched:  " << counter << " - " << allPaths.size() << " projects found\r" << std::flush;
            }
            else
            {
                findUnityLibs(d, allPaths, counter);
            }
        }
        counter++;
    }
}

bool argCheck(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: need a filepath as arg" << std::endl;
        return false;
    }
    if (!fs::is_directory(argv[1]))
    {
        std::cerr << "Error: " << argv[1] << " is not a dircetory" << std::endl;
        return false;
    }
    return true;
}

uintmax_t getDirSize(const fs::path &dir)
{
    uintmax_t size = 0;
    if (fs::is_symlink(dir))
    {
        return size;
    }
    if (fs::is_regular_file(dir))
    {
        return fs::file_size(dir);
    }
    if (!fs::is_directory(dir))
    {
        return 0;
    }
    std::error_code er;
    for (auto const &f : fs::recursive_directory_iterator{dir, fs::directory_options::skip_permission_denied, er})
    {

        if (f.is_regular_file())
        {
            size += f.file_size();
        }
    }
    return size;
}

void addSizeToDirs(std::vector<sizedPath> &path)
{

    std::vector<std::future<uintmax_t>> tempVector;
    for (auto &p : path)
    {
        tempVector.push_back(std::async(std::launch::async, getDirSize, p.Path / "Library"));
    }
    for (std::size_t i = 0; i < tempVector.size(); i++)
    {
        path[i].size = tempVector[i].get();
    }
}

void printVector(const std::vector<sizedPath> &paths)
{

    for (auto const &e : paths)
    {
        auto timeDiff = fs::file_time_type::clock::now() - e.lastOpened;
        auto dagar = (std::chrono::duration_cast<std::chrono::hours>(timeDiff)) / 24;
        std::cout << "Path: " << e.Path << " size: " << shortSize(e.size) << " last written: " << dagar.count() << " days ago\n";
    }
}
std::string shortSize(uintmax_t size)
{

    std::string sizes[] = {"B", "KiB", "MiB", "GiB", "TiB"};
    std::size_t c = 0;
    const double dividerAmount = 1024;
    double d = size;
    while (d >= dividerAmount && c < std::size(sizes) - 1)
    {
        d /= dividerAmount;
        c++;
    }

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << d;
    return stream.str() + " " + sizes[c];
}
std::string toLower(const std::string &s)
{
    std::string out = s;
    for (char &c : out)
    {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return out;
}
void asciiArt()
{
    std::string art = R"(
                             _             _             
 __________                 | |           | |            
/ ##       \  ___ _ __   ___| |_   _ _ __ | | _____ _ __                     
| <()> <()>| / __| '_ \ / _ \ | | | | '_ \| |/ / _ \ '__|      
|  #   >  #| \__ \ |_) |  __/ | |_| | | | |   <  __/ |         
\__________/ |___/ .__/ \___|_|\__,_|_| |_|_|\_\___|_|   
                 | |                                     
                 |_|                                       
)";
    std::cout << art;
}