#include "search.h"

int BM(const string &text, const string& pattern)
{
    if (text.size() == 0 && pattern.size() == 0)
        return 0;
    else if(text.size() == 0 || pattern.size() == 0)
        return -1;

    vector<size_t> slide = slides(pattern);

    int patternLen = static_cast<int>(pattern.size());
    int textLen = static_cast<int>(text.size());

    int i = patternLen - 1;
    int j = i;
    int k = i;
    while (j >= 0 && i <= textLen - 1)
    {
        j = patternLen - 1;
        k = i;
        while (j >= 0 && text.at(k) == pattern.at(j))
        {
            k--;
            j--;
        }
        i += slide.at(text.at(i));
    }
    if (k >= textLen - patternLen)
    {
        return -1;
    }
    else
    {
        return k + 1;
    }
}

vector<size_t> slides(const string &pattern)
{
    vector<size_t> slide(SYMB_NUMBER, pattern.size());
    for (unsigned int i = 0; i < pattern.size() - 1; ++i)
    {
        slide.at(pattern.at(i)) = pattern.size() - i - 1;
    }
    return slide;
}

vector<size_t> preffix(const string &substring)
{
    vector<size_t> fail(substring.size());
    fail[0] = 0;
    for (unsigned int i = 1; i < substring.size(); ++i)
    {
        size_t temp = fail[i - 1];
        while ((temp > 0) && (substring[temp] != substring[i]))
        {
            temp = fail[temp - 1];
        }
        if (substring[temp] == substring[i])
        {
            ++temp;
        }
        fail[i] = temp;
    }
    return fail;
}

int KMP(const string &text, const string& substring)
{
    if (text.size() == 0 && substring.size() == 0)
        return 0;
    else if(text.size() == 0 || substring.size() == 0)
        return -1;

    // Префикс-функция
    vector<size_t> fail = preffix(substring);

    // Поиск
    for (unsigned long k = 0, i = 0; i < text.size(); ++i)
    {
        while ((k > 0) && (substring[k] != text[i]))
        {
            k = fail[k - 1];
        }
        if (substring[k] == text[i])
        {
            ++k;
        }
        if (k == substring.size())
        {
            return static_cast<int>(i - substring.size() + 1);
        }
    }
    return -1;
}
