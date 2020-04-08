//
// Copyright (c) 2008-2020 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Utils.h"

#include <cassert>
#include <sstream>

string Trim(const string& str)
{
    size_t trimStart = 0;
    size_t trimEnd = str.length();

    while (trimStart < trimEnd)
    {
        char c = str.c_str()[trimStart];
        if (c != ' ' && c != 9)
            break;
        ++trimStart;
    }

    while (trimEnd > trimStart)
    {
        char c = str.c_str()[trimEnd - 1];
        if (c != ' ' && c != 9)
            break;
        --trimEnd;
    }

    return str.substr(trimStart, trimEnd - trimStart);
}

string GetFileName(const string& path)
{
    size_t pos = path.find_last_of("/");
    assert(pos != string::npos);
    return path.substr(pos + 1);
}

string WithoutFileName(const string& path)
{
    size_t pos = path.find_last_of("/");
    assert(pos != string::npos);
    return path.substr(0, pos);
}

bool StartsWith(const string& str, const string& value)
{
    return str.rfind(value, 0) == 0;
}

bool EndsWith(const string& str, const string& value)
{
    if (value.size() > str.size())
        return false;

    return equal(value.rbegin(), value.rend(), str.rbegin());
}

string ReplaceAll(const string& src, const string& from, const string& to)
{
    string ret;
    ret.reserve(src.length());

    size_t lastPos = 0;
    size_t findPos = src.find(from, lastPos);

    while (findPos != string::npos)
    {
        ret.append(src, lastPos, findPos - lastPos);
        ret += to;
        lastPos = findPos + from.length();
        findPos = src.find(from, lastPos);
    }

    ret += src.substr(lastPos);

    return ret;
}

vector<string> Split(const string& str, char delim)
{
    stringstream ss(str);
    string item;
    vector<string> result;

    while (getline(ss, item, delim))
        result.push_back(move(item));

    return result;
}

string CutStart(const string& str, const string& value)
{
    if (!StartsWith(str, value))
        return str;

    return str.substr(value.length());
}

string CutEnd(const string& str, const string& value)
{
    if (!EndsWith(str, value))
        return str;

    return str.substr(0, str.length() - value.length());
}

bool Contains(const string& str, const string& substr)
{
    return str.find(substr) != string::npos;
}
