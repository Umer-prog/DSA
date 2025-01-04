#include <iostream>
#include <stdlib.h>
#include <queue>
#include <stack>
using namespace std;

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

struct loop {
    Vertex* parent;
    Vertex* child;
};

struct Weight { // for array
    int weight;
    Vertex* source;
    Vertex* desti;
};

struct Vertex* Cstart = NULL;

//=======================================insert functions====================================
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
void InsertEdge(char c, char sub, int w) {
    Vertex* curr1 = Cstart;// for if the vertex exist from which we want to connect
    //int w = 0;
    while (curr1 != NULL) {
        if (curr1->data == c) {
            Vertex* curr2 = Cstart;// for if the vertex which we want to connect to exists
            while (curr2 != NULL)
            {
                if (curr2->data == sub)
                {
                    Edge* temp1 = new Edge;
                    temp1->ToVertex = curr2;
                    temp1->next = NULL;
                    /*cout << "Enter weight ";
                    cin >> w;*/
                    temp1->weight = w;
                    Ecount += 1; // counting edges
                    Edge* temp2 = new Edge;
                    temp2->ToVertex = curr1;
                    temp2->next = NULL;
                    temp2->weight = w;

                    // for first node
                    if (curr1->Elist == NULL) {
                        curr1->Elist = temp1;
                        cout << "vertex " << curr1->data << " connected with " << curr2->data << endl;
                    }
                    else {
                        struct Edge* Ecurr1 = curr1->Elist;
                        while (Ecurr1->next != NULL) {
                            Ecurr1 = Ecurr1->next;
                        }
                        Ecurr1->next = temp1;
                        cout << "vertex " << curr1->data << " connected with " << curr2->data << endl;
                    }

                    // for second node
                    if (curr2->Elist == NULL)
                    {
                        curr2->Elist = temp2;
                        cout << "vertex " << curr2->data << " connected with " << curr1->data << endl;
                        return;
                    }
                    else
                    {
                        struct Edge* Ecurr2 = curr2->Elist;
                        while (Ecurr2->next != NULL) {
                            Ecurr2 = Ecurr2->next;
                        }
                        Ecurr2->next = temp2;
                        cout << "vertex " << curr2->data << " connected with " << curr1->data << endl;
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
//=====================================printing functions==============================================
void PrintVertex() {
    Vertex* ptr = Cstart;
    if (ptr == NULL) cout << "empty" << endl;
    while (ptr != NULL) {
        cout << ptr->data << endl;
        ptr = ptr->Next;
    }
}

void PrintEdge() {
    char vertex;
    cout << "Enter the vertex number: ";
    cin >> vertex;
    Vertex* current = Cstart;
    if (current == NULL) {
        cout << "vertex does not exist" << endl;
    }
    while (current != NULL) {
        if (current->data == vertex) {
            Edge* ptr = current->Elist;
            if (ptr == NULL) {
                cout << "empty" << endl;
                return;
            }
            while (ptr != NULL) {
                cout << ptr->ToVertex->data << endl;
                ptr = ptr->next;
            }
            return;
        }
        current = current->Next;
        if (current == NULL)cout << "course does not exist" << endl;
    }
}

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
//=======================================delete functions===================================
void DeleteEdge(char c, char edgeChar) {
    Vertex* main = Cstart; // points the vertex 
    Vertex* main2 = Cstart;
    while (main2 != NULL)
    {
        if (main2->data == edgeChar)
        {
            break;                      //captures the other vertex
        }
        main2 = main2->Next;
        if (main2 == NULL)
        {
            cout << "there are no such edges in this vertex\n";
            return;
        }
    }

    // for first edge
    while (main != NULL) { // runs till the main pointer is null
        if (main->data == c)
        {
            Edge* sub = main->Elist; // points edges 
            //if (sub == NULL) // checks for vertex with no edges
            //{
            //    cout << "there are no such edges in this vertex\n";
            //    return;
            //}

            if (sub->ToVertex->data == edgeChar) // checks for first edge
            {
                main->Elist = sub->next;
                free(sub);
                cout << "Edge deleted from vertex : " << main->data << endl;
                break;
            }

            Edge* Sprev = main->Elist; // points to 1 edge previous to main sub pointer
            sub = sub->next;

            while (sub != NULL)// for edges in between
            {
                if (sub->ToVertex->data == edgeChar) {
                    Sprev->next = sub->next;
                    free(sub);
                    cout << "Edge deleted from vertex : " << main->data << endl;
                    goto breakhere;
                }
                sub = sub->next;
                Sprev = Sprev->next;
            }
        }
        main = main->Next;
        if (main == NULL)
        {
            cout << "Given vertex dosent exist...\n";
            return;
        }
    }
    breakhere:
    //for second edge deletion
    Edge* sub2 = main2->Elist; // points edges             
    while (sub2 != NULL)
    {
        if (sub2->ToVertex->data == c) // checks for first edge
        {
            main2->Elist = sub2->next;
            free(sub2);
            cout << "Edge deleted from vertex : " << main2->data << endl;
            return;
        }

        Edge* Sprev2 = main2->Elist; // points to 1 edge previous to main sub pointer
        sub2 = sub2->next;

        while (sub2 != NULL)// for edges in between
        {
            if (sub2->ToVertex->data == c) {
                Sprev2->next = sub2->next;
                free(sub2);
                cout << "Edge deleted from vertex : " << main2->data << endl;
                return;
            }
            sub2 = sub2->next;
            Sprev2 = Sprev2->next;
        }
    }
}

void DeleteVertex(char c) {
    Vertex* cmain = Cstart; // main pointer for vertex
    Vertex* Pmain = Cstart; // previous main for vertex
    //check if the vertex exists that you want to delete
    while (cmain != NULL)
    {
        if (cmain->data == c)
        {
            cout << "vertex exists\n";
            break;
        }
        cmain = cmain->Next;
    }
    if (cmain == NULL)
    {
        cout << "The vertex you want to delete dosent exist..\n";
        return;
    }
    //first delete the reference of that vertex from other vertexes and maintain link
    Vertex* main = Cstart;
    while (main != NULL)
    {
        if (main->data != c)
        {
            Edge* sub = main->Elist; //going in edges of every vertex
            if (sub == NULL)
            {
                main = main->Next;
                continue;
            }
            if (sub->ToVertex->data == c) //if reference is in the start of the list
            {
                main->Elist = sub->next;
                free(sub);
                main = main->Next;
                continue;
            }
            Edge* Psub = sub;// previous of sub pointer
            sub = sub->next;
            while (sub != NULL)// find reference in between list
            {
                if (sub->ToVertex->data == c)
                {
                    Psub->next = sub->next;
                    free(sub);
                    break;
                }
                sub = sub->next;
                Psub = Psub->next;
            }
        }
        main = main->Next;
    }
    cout << "Deleted all refrences.\n";
    // second delete all the edges in the vertex you want to delete
    //now deleting the vertex along with its sub list
    main = cmain;
    Edge* sub = NULL;
    Edge* sub2;


    sub2 = sub;//next
    while (sub != NULL) { // deleting sub list
        sub2 = sub2->next;
        free(sub);
        sub = sub2;
    }
    main = Cstart;
    // finally delete the vertex and maintain link
    if (sub == NULL) {
        if (main->data == c) { //if the vertex is at the start
            Cstart = main->Next;
            //sub = main->Elist;
            free(main);
        }
        else {
            Vertex* main2 = Cstart->Next; //next
            while (main2 != NULL) { // if the vertex is in the middle or end
                if (main2->data == c) {
                    main->Next = main2->Next;
                    //sub = main2->Elist;
                    free(main2);
                    break;
                }
                main = main->Next;
                main2 = main2->Next;
            }
        }
    }

    cout << "deleted the vertex" << endl;
    return;
}
//========================================path===============================================
int Hashfn(char b) {
    int a = (int)b - 97;
    return(a);
}

void pathFinder(char b) {
    int* arr = new int[26];
    for (int i = 0; arr[i]; i++) {
        arr[i] = 0;
    }
    queue <Vertex*> q1;
    Vertex* main = Cstart;
    q1.push(main);
    cout << main->data << " -> ";
    int index = Hashfn(main->data);
    arr[index] = 1;
    while (!q1.empty()) {
        Vertex* output = q1.front();
        q1.pop();
        cout << output->data << " <- ";
        if (output->Elist == NULL) {
            continue;
        }
        Edge* sub = output->Elist;

        while (sub != NULL) {
            if (sub->ToVertex->data == b) {
                cout << sub->ToVertex->data << "path exist" << endl;
                int ind = Hashfn(sub->ToVertex->data);
                arr[ind] = 1;
                for (int i = 0; i < 26; i++) {
                    cout << arr[i] << "\t";
                }
                cout << endl;
                return;
            }
            int ind = Hashfn(sub->ToVertex->data);
            if (arr[ind] == 0) {
                q1.push(sub->ToVertex);
                cout << sub->ToVertex->data << " -> ";
                arr[ind] = 1;
            }

            sub = sub->next;
        }

    }
    cout << "path not exist" << endl;
}

// loop for checking which vertex are connected
void Allcon(Vertex* node, int* arr) {
    // when the node dosent exist
    if (node == NULL) {
        cout << "the give node dosent exist\n";
        return;
    }
    // if there are no edges in a vertex
    if (node->Elist == NULL)
    {
        Allcon(node->Next, arr);
        return;
    }
    // if vertex is visited , the array is updated
    arr[Hashfn(node->data)] = 1;

    //when links exists
    Edge* sub = node->Elist;
    while (sub != NULL) {
        if (arr[Hashfn(sub->ToVertex->data)] != 1) {
            Allcon(sub->ToVertex, arr);

        }
        sub = sub->next;
    }
}

int cdfs = 0;// it  gets 1 when path found (checkdepthfirstsearch)

// depth first 
void Dfs(Vertex* node, int* arr, char c) {
    // when the node dosent exist
    if (node == NULL) {
        cout << "the given node dosent exist\n";
        return;
    }

    // if vertex is visited , the array is updated
    arr[Hashfn(node->data)] = 1;

    //when links exists
    Edge* sub = node->Elist;
    while (sub != NULL && cdfs == 0) {
        if (sub->ToVertex->data == c)
        {
            cout << "Path exist!\n";
            cdfs = 1;
            return;
        }
        // when the vertex is not found
        if (arr[Hashfn(sub->ToVertex->data)] != 1 && cdfs == 0) {
            Dfs(sub->ToVertex, arr, c);
        }
        sub = sub->next;
    }
}

// breath first
void Bfs(char c) {
    // array
    int* arr = new int[Vcount];
    for (int i = 0; arr[i]; i++) {
        arr[i] = 0;
    }
    queue <Vertex*> q1;
    // root is pushed
    Vertex* main = Cstart;
    q1.push(main);
    cout << main->data << " -> ";
    int index = Hashfn(main->data);
    // root is visited
    arr[index] = 1;
    while (!q1.empty()) {
        Vertex* output = q1.front();
        q1.pop();
        cout << output->data << " <- ";
        if (output->Elist == NULL) {
            continue;
        }
        Edge* sub = output->Elist;

        while (sub != NULL) {
            if (sub->ToVertex->data == c) {
                cout << sub->ToVertex->data << "path exist" << endl;
                int ind = Hashfn(sub->ToVertex->data);
                arr[ind] = 1;
                for (int i = 0; i < Vcount; i++) {
                    cout << arr[i] << "\t";
                }
                cout << endl;
                return;
            }
            int ind = Hashfn(sub->ToVertex->data);
            if (arr[ind] == 0) {
                q1.push(sub->ToVertex);
                cout << sub->ToVertex->data << " -> ";
                arr[ind] = 1;
            }

            sub = sub->next;
        }

    }
    cout << "path not exist" << endl;
}

int LoopDetect(Vertex* main) {
    // array
    int* arr = new int[Vcount];
    for (int i = 0; arr[i]; i++) {
        arr[i] = 0;
    }

    queue <loop*> q1;

    // setting parent because using bfs
    loop* relation = new loop;
    relation->parent = main;
    relation->child = main;
    q1.push(relation);
    int index = Hashfn(main->data);
    // root is visited
    arr[index] = 1;
    while (!q1.empty()) {
        loop* output = q1.front();
        q1.pop();

        if (output->child->Elist == NULL) {// if the sub list is empty
            continue;
        }
        Edge* sub = output->child->Elist;

        while (sub != NULL) {// traversing sublist
            // if already visited and the parent is not the prev vertex
            if (arr[Hashfn(sub->ToVertex->data)] == 1 && sub->ToVertex->data != output->parent->data) {//found the vertex through path
                cout << "loop exist" << endl;
                cout << "loop exist between " << output->parent->data << " and " << sub->ToVertex->data << endl;
                return(1);
            }

            // if not already visited
            if (arr[Hashfn(sub->ToVertex->data)] == 0)
            {
                // updading parent and child
                loop* relation2 = new loop;
                relation2->parent = output->child;
                relation2->child = sub->ToVertex;
                q1.push(relation2);
                int index = Hashfn(sub->ToVertex->data);
                // root is visited
                arr[index] = 1;
            }
            sub = sub->next;
        }
    }
    cout << "loop not found \n";
    return(0);
}
//==========================================krushkal======================================
// printing all edges stored in array
void printarr(Weight* arr) {
    for (int i = 0; i < Ecount; i++)
    {
        cout << "source: " << arr[i].source->data << endl;
        cout << "Destination: " << arr[i].desti->data << endl;
        cout << "Weight: " << arr[i].weight << endl;
    }
}

// yeh thora kharab hai
void ArrayStore(Vertex* main, Weight* store) {
    // array
    int* arr = new int[Vcount];
    for (int i = 0; arr[i]; i++) {
        arr[i] = 0;
    }
    int j = 0; // for array
    queue <loop*> q1;
    loop* relation = new loop;
    relation->parent = main;
    relation->child = main;
    q1.push(relation);
    // root is visited
    arr[Hashfn(main->data)] = 1;
    while (!q1.empty()) {
        loop* output = q1.front();
        q1.pop();

        cout << "ok" << endl;
        if (output->child->Elist == NULL) {// if the sub list is empty
            continue;
        }

        Edge* sub = output->child->Elist;

        while (sub != NULL) {// traversing sublist
            if (sub->ToVertex->data != output->parent->data) {//found the vertex through path
                store[j].source = output->child;
                store[j].desti = sub->ToVertex;
                store[j].weight = sub->weight;
                j += 1;
            }
            if (arr[Hashfn(sub->ToVertex->data)] == 0)
            {
                loop* relation2 = new loop;
                relation2->parent = output->child;
                relation2->child = sub->ToVertex;
                q1.push(relation2);
                int index = Hashfn(sub->ToVertex->data);
                // root is visited
                arr[index] = 1;
            }
            sub = sub->next;
        }
    }
}

// converts undirected graph into directed
void DeleteEdgeDirected(char source, char destination) { //deleting an edge from a specific vertex

    Vertex* current = Cstart;
    while (current != NULL) {
        if (current->data == source) { // vertex

            Edge* prev = current->Elist;
            if (prev == NULL) {
                cout << "no Edge" << endl;
                return;
            }

            if (prev->ToVertex->data == destination) {
                current->Elist = prev->next;
                free(prev);
                return;
            }
            Edge* curr = current->Elist;
            curr = curr->next;
            while (curr != NULL) {
                if (curr->ToVertex->data == destination) {
                    prev->next = curr->next;
                    free(curr);
                    return;
                }
                prev = prev->next;
                curr = curr->next;
            }
            cout << "Edge not found" << endl;
            return;
        }
        current = current->Next;
    }
    cout << "Vertex not found" << endl;
}

void krushkal() {
    // first converting undirected to directed graph(deleting double sides of edge)

    Vertex* main1 = Cstart;
    while (main1 != NULL) {
        Edge* sub = main1->Elist;
        while (sub != NULL) {
            DeleteEdgeDirected(sub->ToVertex->data, main1->data);

            sub = sub->next;
        }
        main1 = main1->Next;
    }


    // read all the edges of each vertex
    Weight* arr = new Weight[Ecount]; // array for edges and their weights


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

    // deleting all graph
    int saveEcount = Ecount;
    for (int z = 0; z < saveEcount; z++) {
        DeleteEdgeDirected(arr[z].source->data, arr[z].desti->data);
    }
    Ecount = 0;
    cout << "\n";
    cout << "after deletion" << endl;
    printgraph();
    cout << "\n";

    // Now Making min spanning tree
    for (int i = 0; i < saveEcount; i++) {

        int* Visited = new int[Vcount];
        for (int j = 0; j < Vcount; j++) {
            Visited[j] = 0;
        }
        Allcon(Cstart, Visited);// telling which vertex are visited

        int check = 0;
        for (int k = 0; k < Vcount; k++) {
            if (Visited[k] == 0)check = 1;
        }

        if (check == 1) {
            InsertEdge(arr[i].source->data, arr[i].desti->data, arr[i].weight);
            if (LoopDetect(arr[i].source) == 1) { // Checking and deleting if the inserted edge made a loop
                DeleteEdge(arr[i].source->data, arr[i].desti->data);
                cout << "deleted" << arr[i].source->data << "\t" << arr[i].desti->data << endl;
            }
        }
        /*Add a weight variable which sums the weight of all correct edges here^*/
    }
}


//============================================main========================================
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

    InsertEdge('a', 'c', 3);
    InsertEdge('a', 'b', 2);
    InsertEdge('h', 'b', 5);
    InsertEdge('a', 'd', 2);
    InsertEdge('c', 'g', 1);
    InsertEdge('g', 'h', 7);
    InsertEdge('g', 'i', 3);
    InsertEdge('g', 'j', 2);
    InsertEdge('j', 'k', 9);
    InsertEdge('d', 'e', 6);
    InsertEdge('d', 'f', 3);
    InsertEdge('e', 'f', 7);
    //InsertEdge('h', 'd', 11);
    InsertEdge('e', 'j', 6);

    int a = 0;
    int b = 0;
    char c;
    while (a != 12) {
        cout << "1) Inserting , 2) Printing Graph, 3) Delete , 4) find path, 5) loop, 6) all connected, 7) krushkal, 8) Exit" << endl;
        cin >> a;
        if (a == 1) {
            cout << "1) Vertex insertion, 2) Edge insertion: ";
            cin >> b;
            if (b == 1)
            {
                cout << "Enter your vertex: ";
                cin >> c;
                InsertVertex(c);
            }
            if (b == 2)
            {
                char c1;
                char c2;
                int weight;
                cout << "Enter on which vertex you want to make a connection: ";
                cin >> c1;
                cout << "Input the vertex you want to make a connection to: ";
                cin >> c2;
                cout << "Enter weight: ";
                cin >> weight;
                InsertEdge(c1, c2, weight);
            }
        }
        if (a == 2) {
            printgraph();
        }
        if (a == 3) {
            cout << "1) Vertex deletion, 2) Edge deletion: ";
            cin >> b;
            if (b == 1)
            {
                cout << "Enter the vertex you want to delete: ";
                cin >> c;
                DeleteVertex(c);
            }
            /*if (b == 2)
            {
                char c1;
                char c2;
                cout << "Enter the vertex where you want to delete an edge: ";
                cin >> c1;
                cout << "Enter the vertex of connection";
                cin >> c2;
                DeleteEdge(c1,c2);
            }*/
        }
        if (a == 4) {
            cout << "Enter the vertex of which you want the path of: ";
            cin >> c;
            pathFinder(c);
        }
        if (a == 5) {
            LoopDetect(Cstart);
        }
        if (a == 6) {
            Vertex* node = Cstart;
            int* Visited = new int[Vcount];
            for (int i = 0; i < Vcount; i++) {
                Visited[i] = 0;
            }
            Allcon(node, Visited);
            for (int i = 0; i < Vcount; i++) {
                cout << Visited[i] << endl;
            }
        }
        if (a == 7) {
            krushkal();
        }
        //if (a == 8) {
        //    int* Visited = new int[Vcount];
        //    for (int i = 0; i < Vcount; i++) {
        //        Visited[i] = 0;
        //    }

        //    cout << "Enter from which vertex you want to start: ";
        //    cin >> c;

        //    cout << "Enter the vertex you want to find: ";
        //    cin >> c;

        //    // must do setup for dfs
        //    // or can do all this in a function
        //    Vertex* main = Cstart;
        //    while (main != NULL) {
        //        if (main->data == c) {
        //            break;
        //        }

        //        main = main->Next;
        //    }

        //    if (main == NULL) {
        //        cout << "starting vertex doesn't exist" << endl;
        //        continue;
        //    }

        //    Dfs(main, Visited, c);

        //    if (cdfs == 0)
        //    {
        //        cout << "path doesnt exist" << endl;
        //    }
        //    cdfs = 0;
        //}
        //if (a == 9) {
        //    cout << "Enter the vertex you want to find: ";
        //    cin >> c;
        //    Bfs(c);
        //}
        
        if (a == 8) {
            cout << "Exiting";
            break;
        }
    }
}