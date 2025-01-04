#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

//================================================structs======================================
struct Vertex {
    char data;
    int weight = -1;
    struct Vertex* Next;
    struct Edge* Elist;
};

struct Edge {
    int weight;
    struct Vertex* ToVertex;
    struct Edge* next;
};

struct Arr {
    Vertex* vertex;
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
// for undirected graph edge
void InsertEdge(char c, char sub , int w) {
    Vertex* curr1 = Cstart;// for if the vertex exist from which we want to connect
    while (curr1 != NULL) {
        if (curr1->data == c) {
            Ecount += 1;// counting number of edges
            Vertex* curr2 = Cstart;// for if the vertex which we want to connect to exists
            while (curr2 != NULL)
            {
                if (curr2->data == sub)
                {
                    Edge* temp = new Edge;
                    temp->ToVertex = curr2;
                    temp->next = NULL;
                    temp->weight = w;           // Entering weight
                    if (curr1->Elist == NULL) {
                        curr1->Elist = temp;
                        cout << "Edge is successfully linked with vertex" << endl;
                        cout << "when null\n";
                        return;
                    }
                    else {
                        struct Edge* Ecurr = curr1->Elist;
                        while (Ecurr->next != NULL) {
                            Ecurr = Ecurr->next;
                        }
                        Ecurr->next = temp;
                        cout << "Edge is successfully enrolled in course" << endl;
                        cout << "when not null\n";
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

//for directed graph edge
void InsertEdgeDirected(char vertex, char b, int weight) {//Directed graph 
    Vertex* curr = Cstart;
    while (curr != NULL) { // finding connection to vertex
        if (curr->data == b) {
            cout << "vertex found" << endl;
            break;
        }
        curr = curr->Next;
    }
    if (curr == NULL) {
        cout << "vertex not found" << endl;
        return;
    }

    Vertex* current = Cstart;
    while (current != NULL) { // for finding connection from vertex
        if (current->data == vertex) {
            Edge* temp = new Edge;
            temp->weight = weight;
            temp->ToVertex = curr;
            temp->next = NULL;

            if (current->Elist == NULL) {
                current->Elist = temp;
                cout << "Edge is successfully enrolled in course" << endl;
                return;
            }
            else {
                struct Edge* curren = current->Elist;
                while (curren->next != NULL) {
                    curren = curren->next;
                }
                curren->next = temp;
                cout << "Edge is successfully enrolled in course" << endl;
                return;
            }
        }
            current = current->Next;
    }
        if (current == NULL)cout << "invalid Main vertex number" << endl;
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

//=========================================Djikstra working===================================

int Hashfn(char c) {
    int a = (int)c - 97;
    return(a);
}

void Djikstra(char source, char desti) {
    int* arr = new int[26];//check
    for (int i = 0; arr[i]; i++) {// initializing array
        arr[i] = 0;
    }
    Vertex* main = Cstart;
    // checks given source
    while (main != NULL) {
        if (main->data == source) {
            cout << "found vertex" << endl;
            break;
        }
        main = main->Next;
    }
    if (main == NULL) {
        cout << "source doesnt exist" << endl;
        return;
    }
    // updates visited array
    arr[Hashfn(main->data)] = 1;

    int n = 0;
    Arr* ar = new Arr[Vcount];// for storing vertex
    //stores first(source) vertex
    main->weight = 0;
    ar[0].vertex = main;
    Vertex* lowest = NULL;
    int weight = main->weight;// to save final weight // not saving it correctly bec. it gives weight to b
    int w;
    while (true) {
        Edge* sub = main->Elist;

        while (sub != NULL) {   // giving weights to every vertex connected with current 1
            if (sub->ToVertex->weight == -1) {
                sub->ToVertex->weight = main->weight + sub->weight;
                cout << sub->ToVertex->weight;
            }
            sub = sub->next;
        }

        // finding the least weight vertex out of all the children of all already visited vertex

        int save = 99999999999999999; // to save lowest vertex

        for (int i = 0; i < n + 1; i++) {// to access all visited vertex
            Edge* sub2 = ar[i].vertex->Elist;
            while (sub2 != NULL) {// accessing all the sublist of vertex
                if ((sub2->ToVertex->weight < save) && arr[Hashfn(sub2->ToVertex->data)] != 1) {
                    lowest = sub2->ToVertex;
                    save = lowest->weight;
                    weight = ar[i].vertex->weight + sub2->weight;
                }
                sub2 = sub2->next;
            }
        }
        main = lowest;
        cout << lowest->data << endl;
        /*cout << main->vertex;
        cout << "\t" << main->weight2<<endl;*/
        if (main->data == desti) {// if destination is matched
            cout << "Weight is : " << weight << endl;
            cout << "source found" << endl;
            return;
        }
        arr[Hashfn(main->data)] = 1;
        n++;
        ar[n].vertex = main;
    }
    /*the problem is the destination gives wrong weight sometimes which effects the total cost
    every other node give correct weight*/
}


// hassan one which he clain is correct
void Djikstra2(char source, char desti) {
    int* Visited = new int[26];//check
    for (int i = 0; Visited[i]; i++) {// initializing array
        Visited[i] = 0;
    }
    Vertex* main = Cstart;
    while (main != NULL) {// finding source
        if (main->data == source) {
            cout << "found vertex" << endl;
            break;
        }
        main = main->Next;
    }
    if (main == NULL) {
        cout << "source doesnt exist" << endl;
        return;
    }

    Visited[Hashfn(main->data)] = 1;// makes source visited

    int n = 0;
    Arr* ar = new Arr[Vcount];// for storing vertex(that are enroute to the shortest)
    main->weight = 0;
    ar[0].vertex = main;// storing source vertex
    Vertex* lowest = NULL;
    int weight = main->weight;// to save final weight

    while (true) {
        Edge* sub = main->Elist;
        //cout << main->vertex<<endl;
        while (sub != NULL) {// giving weights to every vertex connected with current one
            if (sub->ToVertex->weight == -1) {//arr[Hashfn(sub->tovertex->vertex)] != 1
                sub->ToVertex->weight = main->weight + sub->weight;
                //cout <<"weight " << sub->tovertex->weight2<<endl;
            }
            sub = sub->next;
        }
        // finding the least weight vertex out of all the children of all already visited vertex

        int save = 99999999999999999; // to save lowest vertex

        for (int i = 0; i < n + 1; i++) {// to access all visited vertex
            Edge* sub2 = ar[i].vertex->Elist;

            while (sub2 != NULL) { // accessing all the sublist of vertex
                if ((sub2->ToVertex->weight < save) && Visited[Hashfn(sub2->ToVertex->data)] != 1) {
                    lowest = sub2->ToVertex;
                    save = lowest->weight;
                }
                sub2 = sub2->next;
            }
        }
        main = lowest;
        cout << lowest->data << endl;
        /*cout << main->vertex;
        cout << "\t" << main->weight2<<endl;*/
        if (main->data == desti) { // if destination is reached
            cout << "Weight is: " << weight << endl;
            cout << "source found" << endl;
            return;
        }
        weight = main->weight;
        Visited[Hashfn(main->data)] = 1;
        n++;
        ar[n].vertex = main;
    }
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
    InsertVertex('a');
    InsertVertex('b');
    InsertVertex('c');
    InsertVertex('d');
    InsertVertex('e');
    InsertVertex('f');
    InsertVertex('g');
    InsertVertex('h');
    InsertVertex('i');
    InsertVertex('j');
    InsertVertex('k');
    InsertVertex('l');
    InsertEdge('j', 'i', 1);
    InsertEdge('j', 'l', 1);
    InsertEdge('j', 'k', 5);
    InsertEdge('l', 'i', 1);
    InsertEdge('j', 'g', 2);
    InsertEdge('i', 'g', 2);
    InsertEdge('j', 'e', 6);
    InsertEdge('g', 'h', 2);
    InsertEdge('e', 'f', 2);
    InsertEdge('e', 'd', 2);
    InsertEdge('d', 'a', 2);
    InsertEdge('d', 'f', 3);
    InsertEdge('a', 'b', 2);
    InsertEdge('h', 'b', 5);
    InsertEdge('g', 'c', 1);
    InsertEdge('c', 'a', 3);
        
    int a = 0;
    int d;
    char c, b;
    while (a != 20) {
        cout << "1 insert vertex, 2 insert edge, 3 Djikstra , 4 print graph, 5 insert edge for directed, 6 Exit," << endl;
        cin >> a;
        if (a == 1) {
            cin >> c;
            InsertVertex(c);
        }
        if (a == 2) {
            cout << "Enter Vertex: ";
            cin >> b;
            cout << "Enter edge: ";
            cin >> c;
            cout << "Enter weight";
            cin >> d;
            InsertEdge(b, c, d);
        }
        if (a == 3) {
            cout << "Enter source: ";
            cin >> c;
            cout << "Enter destination: ";
            cin >> b;
            Djikstra(c, b);
        }
        if (a == 4) {
            printgraph();
        }
        if (a == 5) {
            cout << "Enter Vertex: ";
            cin >> b;
            cout << "Enter edge: ";
            cin >> c;
            cout << "Enter weight";
            cin >> d;
            InsertEdgeDirected(b, c, d);
        }

        if (a == 6) {
            cout << "Exiting";
            break;
        }

    }
}