#include "./utils.h"

bool isFileExists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

string formatDurationFileName(int size, string algo)
{
    return "./resultats/" + algo + "_serie" + to_string(size) + ".csv";
}

string formatMatrixFileName(string rawFileName)
{
    return "./exemplaires/" + rawFileName;
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

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);

    return elems;
}

float stringToFloat(const string &str)
{
    return atof(str.c_str());
}

vector<vector<float>> formatMatrixFromRaw(const string &rawMatrix)
{
    vector<vector<float>> matrix;
    vector<string> rows = split(rawMatrix, '\n');

    for (size_t rowIdx = 1; rowIdx < rows.size(); rowIdx++)
    {
        vector<string> rawNumbers = split(rows[rowIdx], '\t');
        vector<float> numbers;

        for (size_t numberIdx = 0; numberIdx < rawNumbers.size(); numberIdx++)
        {
            numbers.push_back(atof(rawNumbers[numberIdx].c_str()));
        }
        matrix.push_back(numbers);
    }

    return matrix;
}

vector<float> getDurations(int size, string &algo)
{
    vector<float> durations;
    string fileName = formatDurationFileName(size, algo);

    string rawContent = readFileRaw(fileName);
    vector<string> rawDurations = split(rawContent, '\n');

    for (size_t rowIdx = 0; rowIdx < rawDurations.size(); rowIdx++)
    {
        durations.push_back(stringToFloat(rawDurations[rowIdx]));
    }

    return durations;
}

vector<vector<float>> readMatrixFromFile(const string &filePath)
{
    string rawMatrix = readFileRaw(filePath);
    return formatMatrixFromRaw(rawMatrix);
}

void printMatrix(vector<vector<float>> &matrix)
{
    cout << matrix.size() << endl;
    for (size_t rowIdx = 0; rowIdx < matrix.size(); rowIdx++)
    {

        for (size_t numberIdx = 0; numberIdx < matrix[rowIdx].size(); numberIdx++)
        {
            cout << matrix[rowIdx][numberIdx] << '\t';
        }
        cout << endl;
    }
}

float mean(vector<float> &durations)
{
    float m = 0;
    for (float d : durations)
        m += d;
    return m / durations.size();
}