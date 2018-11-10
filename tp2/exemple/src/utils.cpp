#include "utils.h"

using namespace std;

bool isFileExists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);

    return elems;
}

string readFileRaw(const string &fileName)
{
    ifstream file(fileName);

    if (file.is_open())
    {
        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    else
        throw "File not found";
}

void parseRaw(const string &raw, Problem &p)
{
    vector<string> lines = split(raw, '\n');

    p.numberOfSticks = atoi(lines[0].c_str());
    p.weightLimit = atoi(lines[lines.size() - 1].c_str());

    for (size_t i = 1; i < lines.size() - 1; i++)
    {
        vector<string> parts = split(lines[i], '\t');
        int num = atoi(parts[0].c_str());
        int weight = atoi(parts[1].c_str());
        p.sticks.push_back(make_pair(num, weight));
    }
}

bool comparePairs(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.second > b.second;
}

void sortSticks(vector<pair<int, int>> &v)
{
    sort(v.begin(), v.end(), comparePairs);
}

void printVector(vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i];
        if (i != v.size() - 1)
            cout << " ";
    }
    cout << endl;
}

void printSticks(vector<pair<int, int>> &v)
{
    for (int i = 0; i < v.size(); i++)
        cout << "Number:\t" << v[i].first << "\tWeight:\t" << v[i].second << endl;
}

void printMatrix(vector<vector<int>> &m)
{
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[i].size(); j++)
            cout << m[i][j] << '\t';
        cout << endl;
    }
}