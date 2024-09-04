#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <utility>
#include "graph.cpp"
using namespace std;

// finding the shortest path between the locations
void dijkstra1(int dest, vector<int> &vis, vector<int> &dist, set<pair<int, int>> &st, vector<int> &parent)
{
    while (st.size() != 0)
    {
        auto node = *st.begin();
        st.erase(st.begin());
        int source = node.second;
        int distance = node.first;
        vis[source] = 1;
        dist[source] = distance;
        for (auto i : g[source])
        {
            if (vis[i.first])
                continue;
            if (dist[i.first] > distance + i.second)
            {
                dist[i.first] = distance + i.second;
                parent[i.first] = source;
                st.insert({dist[i.first], i.first});
            }
        }
    }
    return;
}
// print the path of the journey using the parent vector
void printPath(vector<int> &parent, int dest)
{
    stack<int> path;
    while (parent[dest] != -1)
    {
        path.push(dest);
        dest = parent[dest];
    }
    path.push(dest);
    while (!path.empty())
    {
        cout << stops[path.top()] << " ";
        path.pop();
    }
    return;
}
// check for the non alpabet characters int the input
bool isAlpha(string s)
{
    for (auto i : s)
    {
        if (!isalpha(i))
            return false;
    }
    return true;
}

int main()
{
    cout << "************welcome to Gujarat*************" << endl;
    int choice = 1;
    string sourceStop;
    string destStop;
    do
    {
        set<pair<int, int>> st;    /*to store the graph nodes in ascending order as their distance from the source*/
        vector<int> vis(40, 0);    /*to mark visited to a node to avoid infinite loop*/
        vector<int> parent(40, 0); /*to store parents of the node for the path*/
        // vector<int> ans;
        vector<int> dist(40, INT32_MAX);
        int s, d;

        do
        {
            int j;
            int onlyAlpha = 1;
            do
            {
                if (onlyAlpha != 1)
                {
                    cout << "Enter Only ALPHABETS" << endl;
                }
                cout << "Please Enter Your Source Location: " << endl;
                cin >> sourceStop;
                onlyAlpha = 0; /* to check for non alphabets in the input*/
            } while (!isAlpha(sourceStop));
            for (auto &x : sourceStop)
            {
                x = tolower(x); /* converting the input to lower case as the data is in lower case*/
            }
            for (j = 0; j < 40; j++)
            {
                if (stops[j] == sourceStop)
                    break; /*checking for the location in the map*/
            }
            s = j; /* storing the key of the location value in the map*/
            if (j != 40)
            {
                break; /* if the location is found then break the loop*/
            }
            else
            {
                cout << "Please Enter a Valid Location" << endl;
            }
        } while (true);

        do
        {
            int j;
            int onlyAlpha = 1;
            do
            {
                if (onlyAlpha != 1)
                {
                    cout << "Enter Only ALPHABETS" << endl;
                }
                cout << "Please Enter Your Destination Location: " << endl;
                cin >> destStop;
                onlyAlpha = 0; /* to check for non alphabets in the input*/
            } while (!isAlpha(destStop));
            for (auto &x : destStop)
            {
                x = tolower(x); /* converting the input to lower case as the data is in lower case*/
            }
            for (j = 0; j < 40; j++)
            {
                if (stops[j] == destStop)
                    break; /*checking for the location in the map*/
            }
            d = j; /* storing the key of the location value in the map*/
            if (j != 40)
            {
                break; /* if the location is found then break the loop*/
            }
            else
            {
                cout << "Please Enter a Valid Location" << endl;
            }
        } while (true);

        cout << "Please choose how do you want to reach to your destination: " << endl;
        cout << "1-> FASTEST" << endl
             << "2-> CHEAPEST" << endl
             << "3-> EXIT" << endl;
        // taking input as a string to prevent misbehaviour
        // to take input as a char and convert in to integer
        char cAlpha;
        cin >> cAlpha;
        choice = cAlpha - '0';
        if (choice == 1 || choice == 2)
        {
            st.insert({0, s});
            parent[s] = -1;
            dijkstra1(s, vis, dist, st, parent);
            cout << dist[d] << endl;
            printPath(parent, d);
            if (choice == 2)
            {
                cout <<endl<< "We are really sorry but for now we have same route for the Fastest and Cheapest journies";
            }
            cout << endl;
        }
    } while (choice != 3);

    return 0;
}