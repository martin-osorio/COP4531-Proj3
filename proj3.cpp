#define INT_MAX 2147483647

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Edge{
	char from;
	char to;
	int weight;
	bool directed;
};

struct Vertex{
	char id;
	int weightto;
	int lengthto;
};

int main(){
	string filename;
	ifstream infile;
	char source, temp;
	int w, K;
	bool directed;
	Edge E;
	bool Vertices[26] = {};
	vector<Edge> Edges;
	vector<Vertex> S, Q;	

	cout << "\nPlease input file name: " ;
	cin >> filename;
	infile.open(filename.c_str());

	while(!infile){
		cout << "\nFile name invalid.\nPlease input file name: ";
		cin >> filename;
		infile.open(filename.c_str());
	}


	infile.ignore(256,'\n');

	infile >> temp;
	if(temp == 'D')
		directed = true;
	else
		directed = false;

	infile.ignore(256,'\n');

	infile >> temp;			//get first vertex
	while(infile){
		if(Vertices[temp-65] == false)
			Vertices[temp-65] = true;

		E.from = temp;


		infile >> temp;		//get second vertex
		if(Vertices[temp-65] == false)
			Vertices[temp-65] = true;

		E.to = temp;

		
		infile >> w;		//get weight
		E.weight = w;

		if(!directed){
			Edge invE;
			invE.from = E.to;
			invE.to = E.from;
			invE.weight = E.weight;
			Edges.push_back(invE);
		}

		Edges.push_back(E);

		infile >> temp;		//get first vertex for next run
	}//done reading file

	infile.close();
	cout << "\nFinished reading file.\n\nFor Dijkstra's, please input source node: ";
	cin >> source;

//BEGIN DIJKSTRA

	Vertex V;
	for(int i = 0; i < 26; i++){
		if(Vertices[i] == true){
			V.id = i+65;
			
			if((i+65) == source)
				V.weightto = 0;
			else
				V.weightto = INT_MAX;
			
			Q.push_back(V);
		}
	}

	while(!Q.empty()){
		Vertex smallest;
		smallest.id = '*';
		smallest.weightto = INT_MAX;
		int i;
		int index;
		for(i = 0; i < Q.size(); i++){
			if(Q[i].weightto <= smallest.weightto){
				smallest.id = Q[i].id;
				smallest.weightto = Q[i].weightto;
				index = i;
			}
		}

		Vertex u = smallest;

		Q.erase(Q.begin()+index);

		for(int i = 0; i < Edges.size(); i++){		//for all edges
			if(Edges[i].from == u.id){		//if it is originating from u
				for(int v = 0; v < Q.size(); v++){
					if(Q[v].id == (Edges[i].to)){
						int newW = u.weightto + Edges[i].weight;
						if(newW < Q[v].weightto)
							Q[v].weightto = newW;
					}
				}
			}
		}

		S.push_back(u);
	}

	ofstream outfile;
	outfile.open("out.txt");
	outfile << "Dijkstra\n";
	outfile << "File: " << filename << endl;
	outfile << "Source: " << source << endl;
	for(int i = 0; i < S.size(); i++)
		outfile << "NODE " << S[i].id << " : "	<< S[i].weightto << endl;
	outfile << "End Dijkstra";

//END DIJKSTRA

//BEGIN SRPA

	cout << "\nFinished Dijkstra's.\n\nFor SRPA, please input source node: ";
	cin >> source;
	cout << "\nFor SRPA, please input K value: ";
	cin >> K;

	S.clear();
	Q.clear();

	int length = 0;

	for(int i = 0; i < 26; i++){
		if(Vertices[i] == true){
			V.id = i+65;
			
			if((i+65) == source){
				V.weightto = 0;
				V.lengthto = 0;
			}
			else
				V.weightto = INT_MAX;
			
			Q.push_back(V);
		}
	}
	
	while(!Q.empty()){
		Vertex smallest;
		smallest.id = '*';
		smallest.weightto = INT_MAX;
		smallest.lengthto = INT_MAX;
		int i;
		int index;
		for(i = 0; i < Q.size(); i++){
			if(Q[i].weightto <= smallest.weightto){
				smallest.id = Q[i].id;
				smallest.weightto = Q[i].weightto;
				smallest.lengthto = Q[i].lengthto;
				index = i;
			}
		}

		Vertex u = smallest;

		Q.erase(Q.begin()+index);

		for(int i = 0; i < Edges.size(); i++){		//for all edges
			if(Edges[i].from == u.id){		//if it is originating from u
				for(int v = 0; v < Q.size(); v++){
					if((Q[v].id == (Edges[i].to)) && (u.lengthto < K)){	//and ending at v
						int newW = u.weightto + Edges[i].weight;
						if(newW < Q[v].weightto)
							Q[v].weightto = newW;
						Q[v].lengthto = u.lengthto + 1;
					}
				}
			}
		}

		S.push_back(u);
	}

	outfile << "\n\nSRPA\n";
	outfile << "File: " << filename << endl;
	outfile << "Source: " << source << endl;
	outfile << "Value K: " << K << endl;
	for(int i = 0; i < S.size(); i++)
		outfile << "NODE " << S[i].id << " : "	<< S[i].weightto << endl;
	outfile << "End SRPA";
	outfile.close();

//END SRPA
	cout << endl;
}
