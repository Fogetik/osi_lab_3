#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <thread>


using std::stack;
using std::map;
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using ull = unsigned long long;

bool check_mistake(const string&);

string del_space(const string&);

vector<char> take_all_var(const string&);

string postfix(const string&);

string to_binary(int, ull);

vector <int> tab_truth(string&);

void firstTask();

int alu(int f_0, int f_1, int a, int b, int enA, int enB, int invA, int& transfer);

string alu8(int, int, string, string, int);

void task_4();

void dLatch(bool choice);

void dLatch1(bool choice);

int main()
{
//    firstTask();
//    string line1, line2;
//    cout << "First expression: ";
//    std::getline(cin, line1);
//    std::transform(line1.begin(), line1.end(), line1.begin(), tolower);
//    line1 = del_space(line1);
//
//    vector<int> result_1 = tab_truth(line1);
//    for (int d : result_1){
//        cout << d << endl;
//    }
//
//    cout << "Second expression: ";
//    std::getline(cin, line2);
//    std::transform(line2.begin(), line2.end(), line2.begin(), tolower);
//
//    line2 = del_space(line2);
//
//    vector<int> result_2 = tab_truth(line2);
//    for (int d : result_2){
//        cout << d << endl;
//    }
//
//    if (result_1 == result_2)
//        cout << "Equality" << endl;
//    else
//        cout << "Not equality" << endl;
//    (!(A+(B*C)+(A+C)))*(!B*!C*(A+!B))
    task_4();
    return 0;
}

bool check_mistake(const string& line) {
    int count{ 0 };
    for (auto sym : line) {
        if (sym == '(')
            count++;
        else if (sym == ')')
            count--;
    }

    if (count)
        return false;

    for (ull i = 0; i < line.size(); i++)
    {
        if (line[i] == '(')
        {
            if ((line[i + 1] == ')')||(line[i + 1] == '+')||(line[i + 1] == '*'))
                return false;

        }
        else if (line[i] == ')')
        {
            if (line[i + 1] == '(')
                return false;
        }
        else if ((line[i] == '+') || (line[i] == '*') || (line[i] == '!'))
        {
            if ((i + 1 == line.size()) || (line[i + 1] == ')') ||
                (line[i + 1] == '+') || (line[i + 1] == '*'))
                return false;

            if ((line[i] != '!') && ((i == 0) || (line[i - 1] == '+') || (line[i - 1] == '*')))
                return false;

        }

    }

    return true;
}

string del_space(const string& line)
{
    string res;
    for (auto sym : line)
        if ((sym != ' ')&&(sym != '\t'))
            res += sym;

    return res;
}

vector<char> take_all_var(const string& line)
{
    vector<char> dictionary;
    for (auto sym : line)
    {
        if ((sym < 'a') || (sym > 'z'))
            continue;

        if (std::count(dictionary.cbegin(), dictionary.cend(), sym) == 0)
            dictionary.push_back(sym);
    }

    return dictionary;
}

string postfix(const string& line) {
    string res;
    stack <char> st;
    for (auto sym : line)
        if (sym == '(')
            st.push(sym);
        else if (sym == ')')
        {
            while (st.top() != '(')
            {
                res += st.top();
                st.pop();
            }

            st.pop();
        }
        else if (sym == '!')
        {
            while ((!st.empty()) && (st.top() == '!'))
            {
                res += st.top();
                st.pop();
            }

            st.push(sym);
        }
        else if (sym == '*')
        {
            while ((!st.empty()) && ((st.top() == '*') || (st.top() == '!')))
            {
                res += st.top();
                st.pop();
            }

            st.push(sym);
        }
        else if (sym == '+')
        {
            while ((!st.empty()) && ((st.top() == '+') || (st.top() == '*') || (st.top() == '!')))
            {
                res += st.top();
                st.pop();
            }

            st.push(sym);
        }
        else
            res += sym;

    while (!st.empty())
    {
        res += st.top();
        st.pop();
    }

    return res;
}

string to_binary(int count, ull d_size)
{
    string res;
    while (count)
    {
        res.insert(0, "0" + std::to_string(count % 2));
        count /= 2;
    }

    while (res.size() < d_size)
    {
        res.insert(0, "0");
    }

    return res;
}

vector <int> tab_truth(string& line)
{
    bool cos = false;
    vector<char> dictionary;
    dictionary = take_all_var(line);
    line = postfix(line);

    vector<int> table;
    map<char, bool> dic_v2;
    string bin;
    bool var_1, var_2, var_3, p_var_1, p_var_2, p_var_3;
    bool var_4, p_var_4;
    int count = static_cast<int>(dictionary.size());
    for (int i = 0; i < pow(2,count); i++)
    {
        var_1 = false; var_2 = false; var_3 = false; var_4 = false;
        p_var_1 = false; p_var_2 = false; p_var_3 = false; p_var_4 = false;

        bin = to_binary(i, dictionary.size());

        for (ull pos = 0; pos < dictionary.size(); pos++)
        {
            dic_v2[dictionary[pos]] = static_cast<bool>(bin[pos] - '0');
        }

        for (auto sym : line)
        {
            if ((sym != '*') && (sym != '+') && (sym != '!'))
            {
                cos = false;
                if (!p_var_1)
                {
                    if ((sym == '0') || (sym == '1'))
                        var_1 = static_cast<bool>(sym - '0');
                    else
                        var_1 = dic_v2[sym];

                    p_var_1 = true;
                }
                else if (!p_var_2)
                {
                    cos = true;
                    if ((sym == '0') || (sym == '1'))
                        var_2 = static_cast<bool>(sym - '0');
                    else
                        var_2 = dic_v2[sym];

                    p_var_2 = true;

                }
                else if (!p_var_3)
                {
//                    var_3 = var_1;
                    if ((sym == '0') || (sym == '1'))
                        var_3 = static_cast<bool>(sym - '0');
                    else
                        var_3 = dic_v2[sym];

                    p_var_3 = true;
                }
                else if (!p_var_4)
                {
//                    var_3 = var_1;
                    if ((sym == '0') || (sym == '1'))
                        var_4 = static_cast<bool>(sym - '0');
                    else
                        var_4 = dic_v2[sym];

                    p_var_4 = true;
                }


            }
            else
            {
                if (sym == '!')
                {

                    if (p_var_4){
                        var_4 = !var_4;
                    }
                    else if (p_var_3){
                        var_3 = !var_3;
                    }
                    else if (p_var_2){
                        var_2 = !var_2;
                    }
                    else if (p_var_1){
                        var_1 = !var_1;
                    }


                }
                else if (sym == '*')
                {

                    if (p_var_3 && p_var_4){
                        p_var_4 = false;
                        var_3 = var_3 && var_4;
                    }
                    else if (p_var_2 && p_var_3){
                        p_var_3 = false;
                        var_2 = var_2 && var_3;
                    }
                    else if (p_var_1 && p_var_2){
                        p_var_2 = false;
                        var_1 = var_1 && var_2;
                    }






                }
                else
                {
                    if (p_var_3 && p_var_4){
                        p_var_4 = false;
                        var_3 = var_3 || var_4;
                    }
                    else if (p_var_2 && p_var_3){
                        p_var_3 = false;
                        var_2 = var_2 || var_3;
                    }
                    else if (p_var_1 && p_var_2){
                        p_var_2 = false;
                        var_1 = var_1 || var_2;
                    }


                }

                cos = false;
            }

        }

        dic_v2.clear();


//        if (!p_res_1)
//            res_1 = var_1;

        if (var_1)
            table.push_back(1);
        else
            table.push_back(0);
    }


    return table;
}

void firstTask(){
    string line1, line2;
    cout << "First expression: ";
    std::getline(cin, line1);
    line1 = del_space(line1);
    cout << endl;
    cout << "Second expression: ";
    std::getline(cin, line2);
    line2 = del_space(line2);
    cout << endl;
    if (line1.empty())
    {
        cout << "Null first string" << endl;
        return;
    }
    else if (line2.empty())
    {
        cout << "Null second string" << endl;
        return;
    }

    if (!check_mistake(line1))
    {
        cout << "There is a mistake in the first expression" << endl;
        return;
    }
    else if (!check_mistake(line2))
    {
        cout << "There is a mistake in the second expression" << endl;
        return;
    }


    vector<int> result_1 = tab_truth(line1);
    vector<int> result_2 = tab_truth(line2);
    if (result_1 == result_2)
        cout << "Equality" << endl;
    else
        cout << "Not equality" << endl;
}

bool decoder1(bool f0, bool f1){
    return !f0 & !f1;
}

bool decoder2(bool f0, bool f1){
    return !f0 & f1;
}

int decoder3(bool f0, bool f1){
    return f0 & !f1;
}

bool decoder4(bool f0, bool f1){
    return f0 & f1;
}

int alu(int f_0, int f_1, int a, int b, int enA, int enB, int invA, int& transfer){
    int l1, l2, l3, l4;
    l1 = decoder1(f_0, f_1) & ((b&enB)&((a&enA)xor invA));
    l2 = decoder2(f_0, f_1) & ((b&enB)|((a&enA)xor invA));
    l3 = decoder3(f_0, f_1) & (!(b&enB));
    l4 = decoder4(f_0, f_1) & (((b&enB)xor((a&enA)xor invA))xor transfer);
    transfer = (decoder4(f_0, f_1) & (b&enB) & ((a&enA)xor invA)) |
            (decoder4(f_0, f_1) & ((b&enB)xor((a&enA)xor invA)) & transfer);
    return (l1|l2|l3|l4);

}

string alu8(int f0, int f1, string a, string b, int inC){
    string res;
    for (int i = 7; i >= 0; i--){
        res = std::to_string(alu(f0, f1, a[i] - '0', b[i] - '0', 1, 1, 0, inC)) + res;
    }

    return res;
}

int d_latch = 0;

void task_4(){
    std::thread tA(dLatch1, false);
    std::thread tB(dLatch1, true);
    tA.join();
    tB.join();
}

void dLatch(bool choice){
    if (choice) {
        int q, no_q;
        q = 1;
        no_q = 0;
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> fp_ms{};
        std::chrono::steady_clock::time_point end;
        point:
        end = std::chrono::steady_clock::now();
        fp_ms = end - begin;
        if (fp_ms.count() >= 1000){
            begin = end;
            if (d_latch == 1) {
                no_q = 0;
                q = 1;
            } else if (d_latch == 0){
                no_q = 1;
                q = 0;
            }

            cout << q << " : " << no_q << endl;
            goto point;
        }
        else if (d_latch != -1)
            goto point;



    }
    else{
        while (true){
            cin >> d_latch;
            if (d_latch == -1)
                break;
        }
    }
}


void dLatch1(bool choice){
    if (choice) {
        int d_latch1 = 0;
        int q, no_q, p;
        q = 1;
        no_q = 0;
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> fp_ms{};
        std::chrono::steady_clock::time_point end;
        point:
        end = std::chrono::steady_clock::now();
        fp_ms = end - begin;
        if (fp_ms.count() >= 1000){
            p = 1;
            begin = end;

        }
        no_q = !((d_latch1 && p) || q);
        q = !((!d_latch1 && p) || no_q);
        no_q = !((d_latch1 && p) || q);
        cout << q << " : " << no_q << endl;
        p = 0;
        usleep(250000);
        goto point;



    }
    else{
        while (true){
            cin >> d_latch;
            if (d_latch == -1)
                break;
        }
    }
}