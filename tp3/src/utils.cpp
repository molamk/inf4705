#include "./utils.h"

bool isFileExists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

std::string readFileRaw(const std::string &fileName)
{
    std::ifstream file(fileName);

    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    else
        throw "File not found";
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim))
        elems.push_back(item);

    return elems;
}

void createProblem(const std::string &filename, Problem &p)
{
    const std::string content = readFileRaw(filename);
    std::vector<std::string> lines = split(content, '\n');

    // Edges
    for (int i = 1; i < lines.size() - 2; i++)
    {
        const std::string line = lines[i];
        std::vector<std::string> stringNumbers = split(line, ' ');
        std::vector<int> intLine;
        for (std::string stringNumber : stringNumbers)
            intLine.push_back(atoi(stringNumber.c_str()));
        p.edges.push_back(intLine);
    }

    // Max duration
    p.maxDuration = atoi(lines[lines.size() - 2].c_str());

    // Vertices
    const std::string valuesString = lines[lines.size() - 1];
    std::vector<std::string> vals = split(valuesString, ' ');
    for (std::string v : vals)
        p.vertices.push_back(atoi(v.c_str()));
}

void printVector(std::vector<int> &v)
{
    for (int x : v)
        std::cout << x << '\t';
    std::cout << std::endl;
}

void printMatrix(std::vector<std::vector<int>> &m)
{
    for (std::vector<int> l : m)
        printVector(l);
}

int getTotalValue(Problem &p, std::vector<int> &s)
{
    int value = 0;
    for (const auto &x : s)
        value += p.vertices[x];

    return value;
}

int getTotalDuration(Problem &p, std::vector<int> &s)
{
    int duration = 0;
    for (int i = 0; i < s.size() - 1; i++)
        duration += p.edges[s[i]][s[i + 1]];

    return duration;
}

float getValueRatio(Problem &p, std::vector<int> &s)
{
    int maxValue = 0;
    for (const auto &x : p.vertices)
        maxValue += x;

    return (float)getTotalValue(p, s) / maxValue * 100;
}

float getDurationRatio(Problem &p, std::vector<int> &s)
{
    return (float)getTotalDuration(p, s) / p.maxDuration * 100;
}

float getValueDurationRatio(Problem &p, std::vector<int> &s)
{
    return getValueRatio(p, s) / getDurationRatio(p, s);
}