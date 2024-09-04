#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "filecompressor.cpp"

using namespace std;

int encodeFile(huffman h, string s, string cmp)
{
    int err= h.huffTree(s);
    if(err == 0){
        cout<<"Error while opening the File."<<endl;
        cout<<"Please make sure that the file is in the same folder as the HUFFMAN COMPRESSOR"<<endl;
        return 0;
    }
    h.traverseHTree(h.huffRoot, "");
    err = h.saveEncodedFile(s, cmp);
    if(err == 0){
        cout<<"Error while opening the File."<<endl;
        cout<<"Please make sure that the file is in the same folder as the HUFFMAN COMPRESSOR"<<endl;
        return 0;
    }
    return 1;
}
int decodeFile(huffman h, string cmp)
{
    int err = h.decodedTree(cmp);
    if(err == 0){
        cout<<"Error while opening the File."<<endl;
        cout<<"Please make sure that the file is in the same folder as the HUFFMAN COMPRESSOR"<<endl;
        return 0;
    }
    err = h.saveDecodedFile(cmp);
    if(err == 0){
        cout<<"Error while opening the File."<<endl;
        cout<<"Please make sure that the file is in the same folder as the HUFFMAN COMPRESSOR"<<endl;
        return 0;
    }
    return 1;
}

int main()
{

    cout << "------------WELCOME TO MY FILE COMPRESSOR-----------" << endl;
    int choose;
    do
    {
        cout << "Please chose one of the following operations: " << endl;
        cout << "1 -> compress the txt file" << endl
             << "2 -> decompress the .cmprssd file" << endl
             << "0 -> EXIT" << endl;
        string cChoose;
        cin >> cChoose;
        choose = cChoose[0] - '0';
        huffman h;
        string s;
        string inputFile;
        if (choose == 1)
        {
            cout << "Please enter the file name you want to compress" << endl;
            int swt;
            do
            {
                swt = 1;
                cin >> s;
                int n = s.size();
                if (s.size() > 4)
                {
                    if (s.substr(n - 4, 4) == ".txt")
                    {
                        inputFile = s.substr(0, n - 4);
                        swt = 0;
                    }
                }
                if (swt)
                {
                    cout << "Please enter a .txt file only" << endl;
                }
            } while (swt);
            string cmp = inputFile + ".cmprssd";
            int rslt = encodeFile(h, s, cmp);
            if(rslt){
                cout << "The file has been compressed by the name of " << cmp << endl;
            }
        }
        else if (choose == 2)
        {
            cout << "Please enter the file name you want to Decompress" << endl;
            int swt;
            do
            {
                swt = 1;
                cin >> s;
                int n = s.size();
                if (s.size() > 8)
                {
                    if (s.substr(n - 8, 8) == ".cmprssd")
                    {
                        inputFile = s.substr(0, n - 8);
                        swt = 0;
                    }
                }
                if (swt)
                {
                    cout << "Please enter a .cmprssd file only" << endl;
                }
            } while (swt);
            string cmp = inputFile + ".cmprssd";
            int rslt = decodeFile(h, cmp);
            if(rslt){
                cout << "Your file has been decompressed " << endl;
            }
        }else{
            if(choose != 0){
                cout<<"Please Enter a Valid Numerical Option"<<endl;
            }
        }

    } while (choose != 0);
    return 0;
}