#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

class node
{
public:
    char c;
    unsigned freq;
    node *left;
    node *right;
    node(char t, unsigned f)
    {
        this->c = t;
        this->freq = f;
        this->left = NULL;
        this->right = NULL;
    }
};

//operator to compare nodes in priorityqueue
class compare
{
public:
    bool operator()(node *l, node *r)
    {
        return (l->freq > r->freq);
    }
};

//to comvert an 8 bit decimal value of a character to its binary value as a string
string decToBin(unsigned num)
{
    string tempS = "";
    while (num > 0)
    {
        if (num % 2 == 0)
        {
            tempS += '0';
        }
        else
        {
            tempS += '1';
        }
        num = num / 2;
    }
    int sz = tempS.size();
    for (int i = 0; i < 8 - sz; i++)
    {
        tempS += '0';
    }
    reverse(tempS.begin(), tempS.end());
    return tempS;
}

//to convert 8 bit binary value to its equivalent decimal value of a character
int binToDec(string str)
{
    int ans = 0;
    for (auto i : str)
    {
        ans = ans * 2 + i - '0';
    }
    return ans;
}

class huffman
{
    vector<string> arr;

public:
    long long btcount;
    unsigned nodeCount;
    node *huffRoot;
    node *newHTRoot;
    huffman()
    {
        this->arr = vector<string>(128, "");
        this->nodeCount = 0;
    }

    void traverseHTree(node *root, string outStr)
    {
        if (root->left == NULL && root->right == NULL)
        {
            arr[root->c] = outStr;
            return;
        }
        traverseHTree(root->left, outStr + '0');
        traverseHTree(root->right, outStr + '1');
    }

    string traverseToDecode(node *root, string path, string encoded)
    {
        for (int i = 0; i < path.size(); i++)
        {
            node *rt = root;
            while (rt->left != NULL && rt->right != NULL && i <= path.size())
            {
                if (path[i] == '0')
                {
                    rt = rt->left;
                }
                else if (path[i] == '1')
                {
                    rt = rt->right;
                }
                i++;
            }
            i--;
            encoded += rt->c;
        }
        return encoded;
    }

    // collecting the frequencies of the characters in the input file
    int huffTree(string s)
    {
        vector<unsigned> arr(128, 0);
        ifstream inputFile;
        inputFile.open(s);
        if (inputFile.is_open())
        {
            char c;
            inputFile.get(c);
            while (!inputFile.eof())
            {
                arr[c]++;
                inputFile.get(c);
            }
            inputFile.close();
            // adding the nodes into min heap
            priority_queue<node *, vector<node *>, compare> pq;
            for (int i = 0; i < 128; i++)
            {
                if (arr[i] == 0)
                    continue;
                nodeCount++;
                node *root = new node(i, arr[i]);
                pq.push(root);
            }
            // making the huffman tree for the given file
            while (pq.size() != 1)
            {
                node *lft = pq.top();
                pq.pop();
                node *rgt = pq.top();
                pq.pop();
                huffRoot = new node('$', 0);
                huffRoot->freq = lft->freq + rgt->freq;
                huffRoot->left = lft;
                huffRoot->right = rgt;
                pq.push(huffRoot);
            }
            // root of the huffman tree saved in the object element huffRoot
            huffRoot = pq.top();
            pq.pop();
            return 1;
        }else{
            return 0;
        }
    }

    int saveEncodedFile(string s, string cmp)
    {
        string enco = "";
        string tmp = "";
        string htencoded = "";
        // encoding the huffman tree for the decoding of the encoded file at the beginning if the encoded file
        enco += (char)nodeCount;
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] == "")
                continue;
            unsigned sz = arr[i].size();
            // first saved the size of huff code of the character in loop
            htencoded += (char)sz;
            // appended '0' if the code is not multipe of 8
            if(sz%8 !=0){
                arr[i].append(8 - sz % 8, '0');
            }
            // saved the code and the character
            for (int j = 0; j < arr[i].size(); j++)
            {
                htencoded += (char)binToDec(arr[i].substr(j, 8));
                j += 7;
            }
            htencoded += (char)i;
            if(sz%8 != 0){
                arr[i].erase(sz, 8 - sz % 8);
            }
        }
        enco += htencoded;
        // encoding the file content by converting every 8 bits to a character
        ifstream inF;
        inF.open(s);
        if (inF.is_open())
        {
            ofstream outF;
            outF.open(cmp, ios::binary | ios::out);
            char ch;
            inF.get(ch);
            while (!inF.eof())
            {
                tmp += arr[(int)ch];
                inF.get(ch);
            }
            int extra;
            for (int i = 0; i < tmp.size(); i++)
            {
                if ((tmp.size() - i) > 8)
                {
                    enco += (char)binToDec(tmp.substr(i, 8));
                    i += 7;
                }
                else
                {
                    // adding extra 0s at the end to make size of tmp multiple of 8
                    extra = 8 - (tmp.size() - i);
                    tmp.append(extra, '0');
                    enco += (char)binToDec(tmp.substr(i, 8));
                    break;
                }
            }
            enco += (char)extra;
            if (outF.is_open())
            {
                outF.write(enco.c_str(), enco.size());
                outF.close();
            }
            else
            {
                cout << "Error while Opening the File" << endl;
            }
            inF.close();
            return 1;
        }
        else
        {
            return 0;
        }
    }
    // to decode the encoded tree in the encoded file to get the huff codes for the characters
    int decodedTree(string cmp)
    {
        newHTRoot = new node('$', 0);
        ifstream inFile;
        inFile.open(cmp, ios::in | ios::binary);
        if (inFile.is_open())
        {
            char htcount;
            inFile.read((char *)&htcount, 1);
            btcount = 1;
            for (int i = 0; i < (unsigned)htcount; i++)
            {
                node *nrt = newHTRoot;
                string genCode = "";
                char t;
                char sizeOfcode;
                inFile.read((char *)&sizeOfcode, 1);
                btcount++;
                for (int j = 0; j < (unsigned)sizeOfcode; j++)
                {
                    inFile.read((char *)&t, 1);
                    btcount++;
                    genCode += decToBin((unsigned char)t);
                    j += 7;
                }
                if ((unsigned)sizeOfcode % 8 != 0)
                {
                    genCode.erase((unsigned)sizeOfcode, 8 - ((unsigned)sizeOfcode % 8));
                }
                for (auto i : genCode)
                {
                    if (i == '0')
                    {
                        if (nrt->left == NULL)
                        {
                            node *temp = new node('$', 0);
                            nrt->left = temp;
                        }
                        nrt = nrt->left;
                    }
                    else if (i == '1')
                    {
                        if (nrt->right == NULL)
                        {
                            node *temp = new node('$', 0);
                            nrt->right = temp;
                        }
                        nrt = nrt->right;
                    }
                }
                inFile.read((char *)&t, 1);
                btcount++;
                nrt->c = t;
            }
        }
        else
        {
            return 0;
        }
        inFile.close();
        return 1;
    }

    int saveDecodedFile(string cmp)
    {
        ifstream cIn;
        ofstream cOut;
        string deco = "";
        cIn.open(cmp, ios::in | ios::binary);
        if (cIn.is_open())
        {
            char extra;
            cIn.seekg(-1, ios::end);
            cIn.read((char *)&extra, 1);
            char t;
            cIn.seekg(btcount, ios::beg);
            cIn.read((char *)&t, 1);
            while (!cIn.eof())
            {
                deco.push_back(t);
                cIn.read((char *)&t, 1);
            }
            string path = "";
            for (int i = 0; i < deco.size(); i++)
            {
                if (i == deco.size() - 2)
                {
                    string ext = decToBin((unsigned char)deco[i]);
                    // deleting the extra 0s which were added at the end to make multiple of 8
                    ext.erase(8 - (int)extra, (int)extra);
                    path += ext;
                    break;
                }
                path += decToBin((unsigned char)deco[i]);
            }
            cmp.erase(cmp.end() - 8, cmp.end());
            string fileDecoded = cmp + "dcmprssd.txt";
            string fileEncoded;
            fileEncoded = traverseToDecode(newHTRoot, path, "");
            cOut.open(fileDecoded);
            if (cOut.is_open())
            {
                cOut.write(fileEncoded.c_str(), fileEncoded.size());
            }
            else
            {
                return 0;;
            }
            cOut.close();
        }
        else
        {
            return 0;
        }
        cIn.close();
        return 1;
    }
};
