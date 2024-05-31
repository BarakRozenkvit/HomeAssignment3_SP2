#include <vector>
#include <fstream>
#include <iostream>

#pragma once
using namespace std;

class Graph {

    vector<vector<char>> _adjMatrix;

    public:
        Graph();
        bool setValue(char val,int i,int j);
        char getValue(int i,int j);
        int size(){return _adjMatrix.size();}
        friend ostream& operator<<(ostream& out,Graph& g){
            out << " " << " " << "         " << to_string(g._adjMatrix[0][0]) << "       " << to_string(g._adjMatrix[1][1]) << "       " << to_string(g._adjMatrix[2][2]) <<" "<< " " << " " << endl;
            out << " " << "       " << to_string(g._adjMatrix[0][3]) << "     " << to_string(g._adjMatrix[0][4]) << "  " << to_string(g._adjMatrix[1][4])<< "   " <<to_string(g._adjMatrix[1][5]) <<"  "<< to_string(g._adjMatrix[2][5]) << "     "<<to_string(g._adjMatrix[2][6])<< endl;
            out << "   " <<"    " << to_string(g._adjMatrix[3][3]) << "       " << to_string(g._adjMatrix[4][4] )<< "       " << to_string(g._adjMatrix[5][5] )<< "       " << to_string(g._adjMatrix[6][6]) <<" "<< " " << endl;
            out << "   "<< "    " << to_string(g._adjMatrix[3][7])<< "       " << to_string(g._adjMatrix[4][8])<< "       " << to_string(g._adjMatrix[5][9]) << "       " << to_string(g._adjMatrix[6][10]) << " " << endl;
            out << " " << "      " << to_string(g._adjMatrix[7][7])<< "       " << to_string(g._adjMatrix[8][8]) << "       " << to_string(g._adjMatrix[9][9]) << "       " << to_string(g._adjMatrix[10][10]) <<" "<< " " << endl;
            out << " " << "   " << to_string(g._adjMatrix[7][11])<< "    " <<  to_string(g._adjMatrix[7][12]) << "   " <<  to_string(g._adjMatrix[8][12]) <<"   " <<  to_string(g._adjMatrix[8][13]) << "   " << to_string(g._adjMatrix[9][13]) << "   " << to_string(g._adjMatrix[9][14]) << "  " << to_string(g._adjMatrix[10][14]) << "    " << to_string(g._adjMatrix[10][15]) << "   "<<endl;
            out << "   " << to_string(g._adjMatrix[11][11])<< "       " << to_string(g._adjMatrix[12][12] )<< "       " << to_string(g._adjMatrix[13][13] )<< "       " << to_string(g._adjMatrix[14][14]) << "      " << to_string(g._adjMatrix[15][15]) << " " << endl;
            out << "   " << to_string(g._adjMatrix[11][16])<< "       " << to_string(g._adjMatrix[12][17])<< "       " << to_string(g._adjMatrix[13][18])<< "       " << to_string(g._adjMatrix[14][19]) << "      " << to_string(g._adjMatrix[15][20]) << " " << endl;
            out << "   " << to_string(g._adjMatrix[16][16]) << "       " << to_string(g._adjMatrix[17][17] )<< "       " << to_string(g._adjMatrix[18][18] )<< "       " <<to_string( g._adjMatrix[19][19]) << "      " << to_string(g._adjMatrix[20][20]) << " " << endl;
            out << " "<< to_string(g._adjMatrix[16][21]) << "   " << to_string(g._adjMatrix[16][22]) << "   " << to_string(g._adjMatrix[17][22]) << "   " << to_string(g._adjMatrix[17][23]) <<"   " << to_string(g._adjMatrix[18][23]) << "   " << to_string(g._adjMatrix[18][24]) << "   " << to_string(g._adjMatrix[19][24]) << "  " << to_string(g._adjMatrix[19][25]) << "   " << to_string(g._adjMatrix[20][25]) << "   " << to_string(g._adjMatrix[20][26])<<endl;
            out << to_string(g._adjMatrix[21][21]) << "      " << to_string(g._adjMatrix[22][22] )<< "       " << to_string(g._adjMatrix[23][23]) << "       " << to_string(g._adjMatrix[24][24] )<< "      " << to_string(g._adjMatrix[25][25] )<< "       " << to_string(g._adjMatrix[26][26]) <<endl;
            out << to_string(g._adjMatrix[21][27]) << "      " << to_string(g._adjMatrix[22][28]) << "       " << to_string(g._adjMatrix[23][29])<< "       " << to_string(g._adjMatrix[24][30])<< "      " << to_string(g._adjMatrix[25][31]) << "       " << to_string(g._adjMatrix[26][32])<<endl;
            out << to_string(g._adjMatrix[27][27]) << "      " << to_string(g._adjMatrix[28][28]) << "       " << to_string(g._adjMatrix[29][29] )<< "       " << to_string(g._adjMatrix[30][30] )<< "      " << to_string(g._adjMatrix[31][31]) << "       " << to_string(g._adjMatrix[32][32])<<endl;
            out << " "<<to_string(g._adjMatrix[27][33]) << "   " << to_string(g._adjMatrix[28][33]) << "   " << to_string(g._adjMatrix[28][34]) << "   " << to_string(g._adjMatrix[29][34]) <<"   " << to_string(g._adjMatrix[29][35]) << "   " << to_string(g._adjMatrix[30][35]) << "   " << to_string(g._adjMatrix[30][36]) << "  " << to_string(g._adjMatrix[31][36]) << "   " << to_string(g._adjMatrix[31][37]) << "   " << to_string(g._adjMatrix[32][37])<<endl;
            out << "   " << to_string(g._adjMatrix[33][33]) << "       "<< to_string(g._adjMatrix[34][34] )<<  "       " << to_string(g._adjMatrix[35][35]) <<  "       " << to_string(g._adjMatrix[36][36]) << "      "<< to_string(g._adjMatrix[37][37]) << " " << endl;
            out << "   " << to_string(g._adjMatrix[33][38])<< "       " << to_string(g._adjMatrix[34][39])<< "       " << to_string(g._adjMatrix[35][40])<< "       " << to_string(g._adjMatrix[36][41]) << "      " << to_string(g._adjMatrix[37][42]) << " " << endl;
            out << "   " << to_string(g._adjMatrix[38][38]) <<  "       " << to_string(g._adjMatrix[39][39] )<< "       " << to_string(g._adjMatrix[40][40] )<< "       " << to_string(g._adjMatrix[41][41]) << "      " << to_string(g._adjMatrix[42][42]) << " " << endl;
            out << " " << "   " << to_string(g._adjMatrix[38][43]) << "    " << to_string(g._adjMatrix[39][43]) << "   " <<  to_string(g._adjMatrix[39][44]) <<"   " <<  to_string(g._adjMatrix[40][44]) << "   " << to_string(g._adjMatrix[40][45]) << "   " << to_string(g._adjMatrix[41][45]) << "  " << to_string(g._adjMatrix[41][46]) << "    " << to_string(g._adjMatrix[42][46]) << "   "<<endl;
            out << " " << "     " << to_string(g._adjMatrix[43][43]) << "        " << to_string(g._adjMatrix[44][44]) <<  "       "<< to_string(g._adjMatrix[45][45] )<< "       " << to_string(g._adjMatrix[46][46]) <<" "<< " " << endl;
            out << "   "<< "   " << to_string(g._adjMatrix[43][47])<< "        " << to_string(g._adjMatrix[44][48])<< "       " << "|" << "       " << "|" << " " << endl;
            out << " " <<"     " << to_string(g._adjMatrix[47][47]) << "       " << to_string(g._adjMatrix[48][48]) << "       " << to_string(g._adjMatrix[49][49] )<<"       "<< to_string(g._adjMatrix[50][50] )<<" "<< " " << endl;
            out << " " << "      " << "\\" << "     " << "/"<< " " << "\\"<< "    " << "/" <<"  "<< "\\" << "     "<<"/"<< endl;
            out << " " << " " <<"        " << to_string(g._adjMatrix[51][51]) << "       " << to_string(g._adjMatrix[52][52]) << "       " << to_string(g._adjMatrix[53][53]) <<" "<< " " << " " << endl;

            return out;

        }
};
