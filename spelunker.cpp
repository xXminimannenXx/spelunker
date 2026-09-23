#include <iostream>
#include <filesystem>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <chrono>
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
void findUnityLibs(const fs::path &dir, std::vector<sizedPath> &allPaths);
void asciiArt();
std::string shortSize(uintmax_t size);
bool argCheck(int argc, char *argv[]);
bool isUnityProj(const fs::path &dir);
std::string shortSize(uintmax_t size);
void printVector(const std::vector<sizedPath> &paths);

//--[real stuff]--
int main(int argc, char *argv[])
{

    std::vector<sizedPath> allPaths = {};

    if (!argCheck(argc, argv))
    {
        return EXIT_FAILURE;
    }
    asciiArt();
    findUnityLibs(argv[1], allPaths);
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

void findUnityLibs(const fs::path &dir, std::vector<sizedPath> &allPaths)
{
    std::error_code er;
    for (auto const &d : fs::directory_iterator{dir, fs::directory_options::skip_permission_denied, er})
    {

        std::cout << "Searching in  " << d.path().filename() << " - " << allPaths.size() << " projects found\r" << std::flush;
        if (!fs::is_symlink(d) && fs::is_directory(d))
        {

            if (isUnityProj(d))
            {
                allPaths.push_back({d, getDirSize(d.path() / "Library"), fs::last_write_time(d.path() / "Assets")});
            }
            else
            {
                findUnityLibs(d, allPaths);
            }
        }
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

        if (fs::is_regular_file(f))
        {
            size += fs::file_size(f);
        }
    }
    return size;
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