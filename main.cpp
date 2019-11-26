#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;










struct edge
{
    string root1;
    string root2;
    int weight;
};

struct root
{
    string name;
    bool check;
    root(string t){name=t; check= false;}
};

int find_set(vector <vector <edge> > ws ,string name);
void make_set(vector <vector <edge> > *ws, edge ed);
void union_sets(vector <vector <edge> > *ws, size_t first, size_t second);
int processing(vector <vector <edge> > ws, edge ed);


int main()
{
    setlocale(LC_ALL, "Russian");
    string input_filename;
    string buff;
    vector <edge> data;
    vector <edge> answer;
    vector <vector <edge> > ws;
    vector <string> roots;
    cout << "input file name: ";
    // C:\Users\Nicetas\Documents\Cruskal\in.txt
    // C:\Users\Nicetas\Desktop\WS\in.txt
    cin >> input_filename;
    ifstream fin;
    fin.open(input_filename);
    if (!fin.is_open())
    {
        cout << "wrong file name!";
        return 1;
    }
    else
    {
        cout << "file opened" << endl;
    }
    while(getline(fin,buff))
    {
        stringstream ss;
        edge tmp;
        ss << buff;
        ss >> tmp.root1;
        ss >> tmp.root2;
        ss >> tmp.weight;
        data.push_back(tmp);

    }



    for (size_t i=0; i<data.size()-1; i++)
        for (size_t j=data.size()-1; j>i; j--)
            if (data[j-1].weight > data[j].weight)
                swap(data[j],data[j-1]);

    for(size_t i = 0; i<data.size();i++)
    {
        switch (processing(ws,data[i]))
        {
        case 0:
            {
            make_set(&ws,data[i]);
            break;
            }
        case 1: break;
        case 2:
            {
            ws[find_set(ws,data[i].root2)].push_back(data[i]);
            break;
            }
        case 3:
            {
            ws[find_set(ws,data[i].root1)].push_back(data[i]);
            break;
            }
        case 4:
            {
            union_sets(&ws,find_set(ws,data[i].root1),find_set(ws,data[i].root2));
            ws[find_set(ws,data[i].root1)].push_back(data[i]);
            break;
            }
        default: return-1;
        }

    }
    if (ws.size()>1)
    {
        cout << "ooops" << endl;
        return -2;
    }

    answer=ws[0];

    for (size_t i=0; i<answer.size()-1; i++)
        for (size_t j=answer.size()-1; j>i; j--)
            if (answer[j-1].root2 > answer[j].root2)
                swap(answer[j],answer[j-1]);

    for (size_t i=0; i<answer.size()-1; i++)
        for (size_t j=answer.size()-1; j>i; j--)
            if (answer[j-1].root1 > answer[j].root1)
                swap(answer[j],answer[j-1]);


    int full_weight=0;
    for (int i=0; i<answer.size(); i++)
    {
        cout << answer[i].root1 << " " << answer[i].root2 << " " << answer[i].weight << endl;
        full_weight+=answer[i].weight;
    }
    cout << "full weight: " << full_weight << endl;


    return 0;
}



int find_set(vector <vector <edge> > ws ,string name)
{
    for (size_t i=0; i<ws.size(); i++)
        for (size_t j = 0; j < ws[i].size(); j++)
            if ((ws[i][j].root1==name)||(ws[i][j].root2==name)) return (int)i;
    return -1;
}

void make_set(vector <vector <edge> > *ws, edge ed)
{
    vector <edge> tmp;
    tmp.push_back(ed);
    (*ws).push_back(tmp);
}

void union_sets(vector <vector <edge> > *ws, size_t first, size_t second)
{
    for (size_t i=0; i<(*ws)[second].size(); i++)
    {
        (*ws)[first].push_back((*ws)[second][i]);
    }
    swap((*ws)[second],(*ws).back());
    (*ws).pop_back();
}

int processing(vector <vector <edge> > ws, edge ed)
{
    if (find_set(ws,ed.root1)==find_set(ws,ed.root2))
    {
        if (find_set(ws,ed.root1)==-1) return 0; //если никого нет в списке
        else return 1;//оба есть в одном и том же списке (т.е. будет цикл)
    }
    if (find_set(ws,ed.root1)==-1) return 2;//первого узла нет в списках а второй есть
    if (find_set(ws,ed.root2)==-1) return 3;//второго узла нет в списках а первый есть
    return 4;//оба узла есть, но в разных списках

}
