#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;
//Ahmad Mohammad   university number : 5083
//6 to 23
class Graph
{
//define the Graph class
private:
    int numVertices;
    //numVertices is the number of the nodes in this graph
    vector <vector<int>> adjacencyList;//storing the edges
    //define needed elements for DFS
    string state[100];
    int newnode;
    int dfsnum[100];
    int finishnum[100];
    int parent[100];
    int dfscount=0;
    int finishcount=0;
    //Mary Al Bishani    university number : 6559
    //25 to 36
    int comp[100];//for Gabow algorithm which represent the node that represent the strongly connected component
    int Ostack[100],Rstack[100];//for Gabow algorithm
    int R=0,O=0;
    vector <vector<int>> adjacencyListForDFS;//for the edges in DFS tree
public:
    Graph(int vertices)
    {
        numVertices=vertices;
        adjacencyList.resize(numVertices);
    }
    //Jawa Hassan    university number : 6201
    //38 to 48
    //add an edge in an undirected graph
    void addEdge(int source,int destination)
    {
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source);
    }
    //add an edge in an directed graph
    void addDirEdge(int S,int D)
    {
        adjacencyList[S].push_back(D);
    }
    //Esraa Tarraf   university number : 5711
    //50 to 61
    void printGraph()
    {
        for(int i=0; i<numVertices; i++)
        {
            cout<<"Vertex "<<i<< ": ";
            if(adjacencyList[i].empty()) cout<<"fi"<<endl;
            else
                for(int neighbor : adjacencyList[i]) cout<<neighbor<<" ";
            cout<<endl;
        }
    }//Layal Jamal   university number : 6498
     //62 to 74
    void init()
    {
        for(int i=0; i<numVertices; i++)
        {
            state[i]="new";
            dfsnum[i]=-12;
            finishnum[i]=-12;
            parent[i]=-10;
            comp[i]=-10;

        }
    }
    //Julia Mlaika   university number : 6139
    //76 to 101
    void DFS(int v)
    {
        state[v]="active";
        dfsnum[v]=dfscount;
        dfscount++;
        Ostack[O]=v;
        O++;
        Rstack[R]=v;
        R++;
        if(!adjacencyList[v].empty())
            for(int n : adjacencyList[v])
            {
                adjacencyListForDFS[n].push_back(v);


                if(state[n]=="new")
                {
                    parent[n]=v;
                    DFS(n);
                }
            }
        state[v]="finish";
        finishnum[v]=finishcount;
        finishcount++;
    }
    //Ghaith Mohammad   university number : 6537
    //103 to 127
    void DepthFirstSearch()
    {
        adjacencyListForDFS.resize(numVertices);
        this->init();
        for(int i=0; i<numVertices; i++)

            if(state[i]=="new") DFS(i);
    }
    void printDFS()
    {
        for(int i=0; i<numVertices; i++)
        {
            cout<<"vertex is "<<i<<" with dfsnum: "<<dfsnum[i]<<" and with finishnum: "<<finishnum[i];
            cout<<endl;
        }
    }

    void printparent()
    {
        for(int i=0; i<numVertices; i++)
        {
            cout<<parent[i]<<" ";
        }
    }
    //Hussein Khalifa   university number : 5912
    //Souzan Fahham   university number: 6150
    //Hanin Ibrahim    university number : 5599
    //131 to 182
    void Gabow()
    {   //run DFS on the graph
        this->init();
        for(int i=0; i<numVertices; i++)
        {
            if(state[i]=="new")
            {
                DFS(i);
                for(int n : adjacencyList[i])
                {
                    if(state[n]=="new")
                    {
                        parent[n]=i;
                        DFS(n);
                    }
                }
                for(int n : adjacencyList[i])
                {
                    if(state[n]=="new")DFS(n);

                    else
                    {   //use stacks to know the strongly connected components
                        for(int j=O-1; j>=0; j--)
                        {
                            if(Ostack[j]==n)
                            {
                                while (dfsnum[n]<dfsnum[Rstack[R-1]])
                                {
                                    Rstack[R-1]=-1;
                                    R--;
                                }
                                break;
                            }
                        }
                    }
                    state[i]="finish";
                    if(i == Rstack[R-1])
                    {
                        Rstack[R]=-1;
                        R--;
                        cout<<"YES"<<endl;
                        while(n!=i)
                        {
                            n=Ostack[O-1];
                            Ostack[O-1]=-1;
                            O--;
                            comp[n]=i;
                        }
                    }
                }
            }
            //Nagham Othman   university number : 6367
            //185 to 203
            //calculate the number of strongly connected components is the graph
            set<int> m;
            for(int i=0; i<numVertices; i++)
            {
                m.insert(comp[i]);
            }
            //comp[i] is storing a number that refer to a node that represents the strongly connected component is every index i
            if(m.size()>1)cout<<"The graph is not strongly connected"<<endl;
            else if(m.size()==1&&comp[i]==-10)cout<<"There are no articulation points so that the graph is 2-vertex biconnected graph"<<endl;
            else
            {
                cout<<"The graph is strongly connected"<<endl;
            }
        }
    }
    void Schmidt()
    {
        init();
        //make the directed graph an undireted graph
        //Ghaith Mohammad   university number : 6537
        //Julia Mlaika   university number : 6139
        //205 to 216
        for(int i=0; i<numVertices; i++)
        {
            for(auto it : adjacencyList[i])
            {
                adjacencyList[i].push_back(it);
                adjacencyList[it].push_back(i);
            }
        }
        //run DepthFirstSearch which select and store the edges that its a part of DFS tree
        DepthFirstSearch();
        //Maya Darwish   university number : 6596
        //Sedra Barood    university number : 6315
        //218 to 242
        bool t=true;
        for(int i=0; i<numVertices; i++)
        {
            for(auto it : adjacencyList[i])
            {   //add the edges that its not from the DFS tree
                t=true;
                for(int j=0; j<numVertices; j++)
                {
                    for(auto it1 : adjacencyListForDFS[i])
                    {
                        if(i==j&&adjacencyList[i]==adjacencyListForDFS[j])t=true;
                    }
                }
                if(t==false)
                {
                    adjacencyListForDFS[it].push_back(i);
                }
            }
        }
        /*we can run Gabow here because we need to know if there are articulation points and Gabow find the strongly connected components
        which they are cycles
        */
        Gabow();
    }
};
int main()
{

}
