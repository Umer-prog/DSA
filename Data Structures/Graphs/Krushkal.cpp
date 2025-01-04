#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

//================================================structs======================================
struct Vertex {
    char data;
    struct Vertex* Next;
    struct Edge* Elist;
};
struct Edge {
    int weight;
    struct Vertex* ToVertex;
    struct Edge* next;
};

struct Weight { // for array
    int weight;
    Vertex* source;
    Vertex* desti;
};

struct Vertex* Cstart = NULL;


//=========================================Insert=============================================
int Vcount = 0; // counts no of vertex
void InsertVertex(char c) {
    struct Vertex* temp = new Vertex;
    temp->data = c;
    temp->Next = NULL;
    temp->Elist = NULL;
    Vcount += 1;
    if (Cstart == NULL) {
        Cstart = temp;
    }
    else {
        struct Vertex* current = Cstart;
        while (current->Next != NULL) {
            current = current->Next;
        }
        current->Next = temp;
    }
}

int Ecount = 0; //number of connections
void InsertEdge(char c) {
    Vertex* curr1 = Cstart;// for if the vertex exist from which we want to connect
    while (curr1 != NULL) {
        if (curr1->data == c) {
            char sub;
            cout << "Enter the vertex you want to connect to: ";
            cin >> sub;
            Ecount += 1;// counting number of edges
            Vertex* curr2 = Cstart;// for if the vertex which we want to connect to exists
            while (curr2 != NULL)
            {
                if (curr2->data == sub)
                {
                    Edge* temp = new Edge;
                    temp->ToVertex = curr2;
                    temp->next = NULL;
                    cout << "Enter weight ";
                    cin >> temp->weight;           // Entering weight
                    if (curr1->Elist == NULL) {
                        curr1->Elist = temp;
                        cout << "Edge is successfully connected with vertex" << endl;
                        return;
                    }
                    else {
                        struct Edge* Ecurr = curr1->Elist;
                        while (Ecurr->next != NULL) {
                            Ecurr = Ecurr->next;
                        }
                        Ecurr->next = temp;
                        cout << "Edge successfully connected with the vertex" << endl;
                        return;
                    }

                }
                curr2 = curr2->Next;
            }
            if (curr2 == NULL)
            {
                cout << "the other vertex is not in list...\n";
                return;
            }
        }
        curr1 = curr1->Next;
    }
    if (curr1 == NULL) {
        cout << "Vertex not found" << endl;
        return;
    }

}

void DeleteEdge(char source, char desti) {
    Vertex* main = Cstart; // points the vertex 
    while (main != NULL) { // runs till the main pointer is null
        if (main->data == source)
        {
            Edge* sub = main->Elist; // points edges
            
            if (sub == NULL) // checks for vertex with no edges
            {
                cout << "there are no such edges in this vertex\n";
                return;
            }

            if (sub->ToVertex->data == desti) // checks for first edge
            {
                main->Elist = sub->next;
                free(sub);
                return;
            }

            Edge* Sprev = main->Elist; // points to 1 edge previous to main sub pointer
            sub = sub->next;

            while (sub != NULL)// for edges in between
            {
                if (sub->ToVertex->data == desti) {
                    Sprev->next = sub->next;
                    free(sub);
                    cout << "Edge deleted\n";
                    return;
                }
                sub = sub->next;
                Sprev = Sprev->next;

            }
        }
        main = main->Next;
    }
    if (main == NULL)
    {
        cout << "Given vertex dosent exist...\n";
        return;
    }

}

//=========================================Krushkal working===================================
void printarr(Weight* arr) {
    for (int i = 0; i < Ecount ; i++)
    {
        cout << "source: " << arr[i].source->data << endl;
        cout << "Destination: " << arr[i].desti->data << endl;
        cout << "Weight: " << arr[i].weight << endl;
    }
}

int Hashfn(char b) {
    int a = (int)b - 97;
    return(a);
}

void Dfs(Vertex* node, int* arr) {
    if (node = NULL)
    {
        return;
    }
    arr[Hashfn(node->data)] = 1;   // this vertex is visited
    Edge* sub = node->Elist;
    while (sub != NULL)
    {
        if (arr[Hashfn(sub->ToVertex->data)] != 1)
        {
            Dfs(sub->ToVertex, arr); 
        }
        sub = sub->next;
    }
}

void AscWeight() {
    Weight* arr = new Weight[Ecount]; // array for edges and their weights
    
    //checks visited vertex
    /*int* Visited = new int[Vcount];
    for (int i = 0; Visited[i]; i++) {
        Visited[i] = 0;
    }*/

    // read all the edges of each vertex
    Vertex* main = Cstart;
    int i = 0; // for array
    while (main != NULL) // for vertex
    {
        Edge* sub = main->Elist;
        while (sub != NULL) //  for sub list
        {
            // store them in array
            arr[i].source = main;
            arr[i].desti = sub->ToVertex;
            arr[i].weight = sub->weight;
            i += 1;
            sub = sub->next;
        }
        main = main->Next;
    }
    cout << "before sort\n";
    printarr(arr);

    // sort array
    for (int i = 0; i < Ecount - 1; i++) {
        for (int j = 0; j < Ecount - 1; j++) {
            if (arr[j].weight > arr[j + 1].weight) {
                swap(arr[j], arr[j + 1]);
                //cout << "swapped\n";
                
            }

        }
    }
    cout << "after sort\n";
    printarr(arr);

    
    for (int i = 0; i < Ecount; i++)
    {
        // giving index
        //int source = Hashfn(arr[i].source->data);
        //int desti = Hashfn(arr[i].desti->data);

        ////checking values at that index
        //if (Visited[source] != 1 || Visited[desti] != 1)
        //{
        //    Visited[source] = 1;
        //    Visited[desti] = 1;
        //    continue;
        //}


        DeleteEdge(arr[i].source->data, arr[i].desti->data);
        //Visited[desti] = 0;
    }
    /*for (int i = 0; i < Vcount; i++)
    {
        cout << char(97 + i) << " : " << Visited[i] << endl;
    }*/
    cout << "end\n";
    printarr(arr);
}

//=========================================printing===========================================
void printgraph() {
    struct Vertex* current = Cstart;
    if (current == NULL) {
        cout << "Linked List is empty";
    }
    else {
        while (current != NULL) {
            cout << "Vertex : " << current->data << endl;
            struct Edge* ECurr = current->Elist;
            while (ECurr != NULL)
            {
                cout << "Edge: " << (ECurr->ToVertex->data) << endl;
                ECurr = ECurr->next;
            }

            current = current->Next;
        }
    }
}

int main() {
    int a = 0;
    char c;
    InsertVertex('a');
    InsertVertex('b');
    InsertVertex('c');
    InsertVertex('d');
    
    while (a != 10) {
        cout << "press 1 for inserting a vertex, 2 for inserting a Edge, 3 for printing course list, 4 Array, 5 for exit" << endl;
        cin >> a;
        if (a == 1) {
            cout << "Enter your vertex: ";
            cin >> c;
            InsertVertex(c);
        }
        if (a == 2) {
            cout << "Enter on which vertex you want to make a connection: ";
            cin >> c;
            InsertEdge(c);
        }
        if (a == 3) {
            printgraph();
        }
        if (a == 4) {
            //cout << "Enter the vertex where you want to delete an edge: ";
            //cin >> c;
            AscWeight();
            
            //sort(arr[0].weight, arr[Ecount - 1].weight);
            
        }
        if (a == 5)
        {
            int* Visited = new int[Vcount];
            for (int i = 0; i<Vcount; i++) {
                Visited[i] = 0;
            }
            Dfs(Cstart, Visited);
            for (int i = 0; i < Vcount; i++)
            {
                cout << char(97 + i) << " : " << Visited[i] << endl;
            }
        }
        if (a == 6) {
            cout << "Exiting";
            break;
        }

    }
}