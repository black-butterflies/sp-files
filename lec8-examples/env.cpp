#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    using namespace std;

    char *env_cpath = getenv("CPATH");
    string cpath;
    if (env_cpath)
        cpath = string(env_cpath);
    else
        cpath = "Not available";
    cout << "Path = " << cpath << endl;

    char *crawler = getenv("CRAWLER_THREADS");
    int crawlers_number;
    if (crawler)
        crawlers_number = stoi(crawler);
    else
        crawlers_number = 2;
    cout << "Number of threads = " << crawlers_number << endl;
}