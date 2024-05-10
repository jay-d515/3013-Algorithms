/*************************************************************
* Name:
*       Jadyn Dangerfield
*
* Class: 
*       CMPS 3013 - Advanced Structures and Algorithms
*
* Program:
*       Optional Program 1 - Vector Class
*
* Files: 
*       main.cpp | driver file
*       dat.txt | input file
*       out.txt | output file
* 
* Description:
*		This program creates a vector class that can be used to push, pop,
*       find, and print elements from listVector objects.
*
*************************************************************/
#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    // stores integer values associated with nodes
    int element;
    // a pointer to the next node
    Node* next;

    // parameterized constructor
    Node(int e)
    {
        // initializes 'element' to 'e'
        element = e;
        // sets the next member variable to NULL
        next = nullptr;
    }
};

// function prototype
void printHeading(ofstream &outfile);

class listVector {
    private:
        //declaring private member variables
        Node* front;
        Node* rear;
    public:
        //declaring constructors
        listVector();
        listVector(const int arr[], const int& size);
        listVector(ifstream &infile);
        listVector(listVector &other);

        //declaring all push functions
        void pushFront(const int &value);
        void pushFront(listVector &other);
        void pushRear(const int &value);
        void pushRear(listVector &other);
        void pushAt(const int &loc, const int &value);
        void inOrderPush(const int &value);

        //declaring all pop functions
        int popFront();
        int popRear();
        int popValue(const int &loc);
        int find(const int &value);

        void printVector(ofstream &outfile);
        void sortVector();
        int vectorSize();
};

int main() {
    // open input and output files
    ifstream infile;
    infile.open("dat.txt");
    ofstream outfile;
    outfile.open("out.txt");
    printHeading(outfile);

    int x = 0;

    // creates a list based vector
    listVector v1;
    //  pushes 3 values to the front of v1.
    v1.pushFront(11);
    v1.pushFront(39);                           
    v1.pushFront(34);
    //  pushes 3 values to the rear of v1.
    v1.pushRear(19);
    v1.pushRear(66);
    v1.pushRear(42);

    // prints v1
    v1.printVector(outfile);                               

    // creates an array of size 5 for a list-based vector.
    int arr[] = {33,41,49,56,64,70};
    //  creates a list-based vector for an array named v2.
    listVector v2(arr,6);
    // prints v2;
    v2.printVector(outfile);                                

    //  pushes 3 values onto v2
    v2.pushFront(2);
    v2.inOrderPush(55);
    v2.pushRear(23);

    // prints v2 after values were pushed
    v2.printVector(outfile);                                

    // pushing v2 to the rear of v1
    v1.pushRear(v2);
    // prints v1 after v2 was pushed to the rear of v1
    v1.printVector(outfile);

    // pops 3 values off of v1
    x = v1.popFront();
    x = v1.popFront();
    x = v1.popFront();

    // prints v1 after values were popped
    v1.printVector(outfile);

    // printing the last front value of v1
    cout<<x<<endl;
    outfile << x << endl;

    // popping 3 values off the rear of v1
    x = v1.popRear();
    x = v1.popRear();
    x = v1.popRear();

    // prints v1 after 3 values were popped
    v1.printVector(outfile);

    // prints the last rear value of v1
    cout<<x<<endl;
    outfile << x << endl;

    // pops the values at index 3 in v2
    x = v2.popValue(3);
    // prints v2 after the value was popped
    v2.printVector(outfile);

    // prints the values that was popped in v2
    cout<<x<<endl;
    outfile << x << endl;

    // finds the value 41 in v2
    x = v2.find(41);
    // prints the index of 41
    cout<<x<<endl;
    outfile << x << endl;

    // finds the value 8 in v2
    x = v2.find(8);
    // prints the index of 8
    cout<<x<<endl;
    outfile << x << endl;

    // creates a list-based vector using v1 as input
    listVector v3(v1);
    // prints v3
    v3.printVector(outfile);

    // pushes v2 to the front of v3
    v3.pushFront(v2);
    // prints v3 after v2 was pushed to the front of v3
    v3.printVector(outfile);
    
    // creates a list-based vector for an array named v4 using input values.
    listVector v4(infile);
    // pushes v4 to the rear of v3
    v4.pushRear(v3); 
    // prints v4 after v3 was pushed to the rear of v4
    v4.printVector(outfile);
}

/*
* function : printHeading
*
* Description:
*      This method prints my name, assignment, semester, and class to an
*      output file.
* Parameters:
*      ofstream &outfile | output file stream
*
* Returns:
*      void
*/
void printHeading(ofstream &outfile) {
    // prints my name, assignment, semester, and class to an output file.
    outfile << "Jadyn Dangerfield" << endl;
    outfile << "Optional Program 1: Vector Class" << endl;
    outfile << "Spring 2024";
    outfile << "3013 Advanced Algorithms and Structures\n\n" << endl;
}

/*
* default constructor : listVector
*
* Description:
*      This is the default constructor for the listVector class which sets the *      front and rear pointers to nullptr.
* Parameters:
*      None
*
* Returns:
*      Nothing
*/
listVector::listVector() {
    // sets front and rear to nullptr
    front = nullptr;
    rear = nullptr;
}

/*
* parameterized constructor : listVector
*
* Description:
*      This is a parameterized constructor for the listVector class which    *      uses an array as input.
* Parameters:
*      const int arr[] | array used to create the listVector
*      const int& size | size of the array
*
* Returns:
*      Nothing
*/
listVector::listVector(const int arr[], const int& size) {
    // ssets front and rear to nullptr
    front = nullptr;
    rear = nullptr;

    // traverse the array
    for(int i = 0; i < size; i++) {
        // if the front and rear are NULL...
        if(!front && !rear) {
            // push the value to the front
            pushFront(arr[i]);
        }
        // if the front and rear are not NULL...
        else {
            // push the value to the rear
            pushRear(arr[i]);
        }
    }
}

/*
* parameterized constructor : listVector
*
* Description:
*      This is a parameterized constructor for the listVector class which 
*      uses an input file as input.
* Parameters:
*      ifstream &infile | input file stream
*
* Returns:
*      Nothing
*/
listVector::listVector(ifstream &infile)
{
    // sets front and rear to nullptr
    front = nullptr;
    rear = nullptr;
    // creates a temporary variable to store the values from the file
    int val = 0;

    // while the file is not empty...
    while(!infile.eof()) {
        // reads in value from the input file
        infile >> val;
        // if the front and rear are NULL...
        if(!front && !rear) {
            // push the value to the front
            pushFront(val);
        }
        // if the front and rear are not NULL...
        else {
            // push the value to the rear
            pushRear(val);
        }
    }
}

/*
* copy constructor : listVector
*
* Description:
*      This is the copy constructor for the listVector class which 
*      uses another listVector as input.
* Parameters:
*      listVector &other | listVector used to create the listVector
*
* Returns:
*      Nothing
*/
listVector::listVector(listVector &other) {
    // sets front and rear to nullptr
    front = nullptr;
    rear = nullptr;
    // sets travel to the front of the other listVector
    Node* travel = other.front;

    // if front and rear are NULL...
    if(!front && !rear) {
        // push the first element in the other listVector to the front
        // of the currentlistVector
        pushFront(travel->element);
        // traverse other listVector
        travel = travel->next;
        }

    // while travel is not NULL...
    while(travel) {
        // push the element to the rear of the current listVector
        pushRear(travel->element);
        // traverse the other list vector
        travel = travel->next;
    }
}

/*
* class method : pushFront
*
* Description:
*      This method pushes an integer value to the front of the listVector.
* Parameters:
*      const int &value | integer being pushed to the front
*
* Returns:
*      void
*/
void listVector::pushFront(const int &value) {
    // creates a new temporary node
    Node* temp = new Node(value);
    // adds temporary node to the front of the listVector
    temp->next = front;
    // sets front to the new Node
    front = temp;
}

/*
* class method : pushFront
*
* Description:
*      This method pushes a listVector to the front of the listVector.
* Parameters:
*      listVector &other | listVector being pushed to the front
*
* Returns:
*      void
*/
void listVector::pushFront(listVector &other) {
    // creates a travel Node equal to the front of the other listVector
    Node* travel = other.front;
    // 
    int index = 0;
    // while the travel Node is not NULL...
    while(travel) {
        
        int tempVal = travel->element;
        // pushes the value of the other listVector to the value index being
        // incremented
        pushAt(index, tempVal);
        // traverse the other listVector
        travel = travel->next;
        // increments index
        index++;
    }
}

/*
* class method : pushRear
*
* Description:
*      This method pushes a value to the rear of the listVector.
* Parameters:
*      const int &value | integer being pushed to the rear
*
* Returns:
*      void
*/
void listVector::pushRear(const int &value) {
    // creates a temporary Node
    Node* temp = new Node(value);
    // creates a travel Node
    Node* travel = front;

    // if the front is NULL...
    if(front == NULL) {
        // pushes a new node to the front
        front = temp;
        rear = temp;
    }
    // while the Node is not NULL...
    while(travel->next != NULL) {
        // traverse listVector until the rear is reached
        travel = travel->next;
    }
    // sets the rear to the new Node
    travel->next = temp;
    rear = temp;
}

/*
* class method : popRear
*
* Description:
*      This method traverses pushes a listVector to the rear of the listVector.
* Parameters:
*      listVector &other | listVector being pushed to the rear
*
* Returns:
*      void
*/
void listVector::pushRear(listVector &other) {
    // create a new node equal to the front of the other listVector
    Node* travel = other.front;

    // while the travel Node is not NULL...
    while(travel) {
        // push the value of the other listVector to the rear
        pushRear(travel->element);
        // traverse the other listVector
        travel = travel->next;
    }
}

/*
* class method : pushAt
*
* Description:
*      This method pushes a value at a specific index into the listVector.
* Parameters:
*      const int &loc | location of the value being pushed
*      const int &value | value being pushed
*
* Returns:
*      void
*/
void listVector::pushAt(const int &loc, const int &value) {
    // creating new nodes
    Node* temp = new Node(value);
    Node* previous = front;
    Node* travel = front;

    // if the loaction is at the front...
    if(loc == 0) {
        // push the node to the front
        temp->next = front;
        front = temp;
        // break out
        return;
    }  
    // if the location is not at the front...
    if(loc != 0) {
        // traverse listVector until the locaion is reached
        for(int i = 0; i < loc; i++) {
            // if the travel Node is NULL...
            if(travel == nullptr) {
                // print out that the location cannot be accessed
                cout << "unable to access location " << loc << endl;    
                // break out
                return;
            }
            // if the travel Node is not NULL...
            else {
                // continue traversing the listVector
                previous = travel;
                travel = travel->next;
            }
        }
    } 
    // if pushing rear...
    if(previous == rear) {
        // push the node to the rear
        temp->next = travel;
        previous->next = temp;
        // update rear
        rear = temp;
    }
    // if not front or rear...
    // update value at specified index
    temp->next = travel;
    previous->next = temp;
}

/*
* class method : inOrderPush
*
* Description:
*      This method sort listVector and pushes values in order.
* Parameters:
*      const int &value | value being pushed
*
* Returns:
*      void
*/      
void listVector::inOrderPush(const int &value)
{
    // sorts listVector
    sortVector();
    Node* t1 = front;
    // initialize values
    int key = value;
    int count = 0;

    // while t1 is not null...
    while(t1) {
        // if the key is greater than t1's element...
        if(key > t1->element) {
            // continue traversing
            t1 = t1->next;
            // increment count by 1 
            count++;
        }
        // if the key is less than t1's element...
        else if(key < t1->element) {
            // push the value at that index
            pushAt(count, value);
            // break out
            break;
        }
            // if the key is equal to t1's element...
        else if(key == t1->element) {
            // push the value at that index
            pushAt(count, value);
            // break out 
            break;
        }
    }

    // if t1 is NULL...
    if(t1 == NULL) {
        // push the value to the rear
        pushRear(value);
    }
}

/*
* class method : popFront
*
* Description:
*      This method traverses pops the front element
* Parameters:
*      none
*
* Returns:
*      int | value at the front
*/
int listVector::popFront() {
    // if front and rear are equal to NULL...
    if(!front && !rear) {
        // return the front element
        return front->element;
    }
    // if front and rear are not equal to NULL...
    // pop the front element and update front
    int tempVal = front->element;
    front = front->next;
    return tempVal;
}

/*
* class method : popRear
*
* Description:
*      This method traverses listVector and pops the rear element.
* Parameters:
*      none
*
* Returns:
*      int | value at the rear
*/ 
int listVector::popRear() {
    // create traversal Node
    Node* travel = front;

    // while the next 2 Nodes are not NULL...
    while(travel->next->next != NULL) {
        // traverse listVector
        travel = travel->next;  
    }
    // store the rear value
    rear = travel->next;
    // set traversal Node to NULL
    travel->next = NULL;
    // store rear value at temporary variable
    int tempVal = rear->element;
    // set rear to travel Node
    rear = travel;
    // return the rear value
    return tempVal;
}

/*
* class method : popValue
*
* Description:
*      This method traverses listVector at a specific index and pops the
*      value at that location.
* Parameters:
*      const int &loc | location of the value being popped
*
* Returns:
*      int | value at the index 
*/         
int listVector::popValue(const int &loc) {
    // create traversal nodes
    Node* previous = front;
    Node* travel = front;

    // if the location is 0...
    if(loc == 0) {
        // pop the front value
        return popFront();
    }

    // if the location is not 0...
    if(loc != 0) {
        // traverse the listVector until the index is found
        for(int i = 0; i < loc; i++) {
            // if the travel Node is NULL...
            if(travel->next == NULL) {
                // breack out of the loop
                return -1;
            }
            // if the travel Node is not NULL...
            else {
                // continue traversing the listVector
                previous = travel;
                travel = travel->next;
            }
        }
    } 

    // if the index is equal to the rear....
    if(previous == rear) {
        // pop the rear value
        int tempVal = popRear();
        // update the rear value
        previous = rear;
        // return rear
        return tempVal;
    }
    // if the index is not equal to the rear or the front...
    // update previous and next Nodes
    previous->next = travel->next;
    return travel->element;
    // return the value at the index
    delete travel;
}

/*
* class method : find
*
* Description:
*      This method traverses listVector, searches for a value, and returns
*      the index of the value.
* Parameters:
*      const int &value | value being searched for
*
* Returns:
*      int | index of the value being search for 
*/     
int listVector::find(const int &value) {
    // create traversal node
    Node* travel = front;
    // value to hold index
    int key = value;
    // index increment 
    int indexCount = 0;
    
    // while travel is not NULL...
    while(travel) {
        // if the value is found...
        if(travel->element == key) {
            // return the index
            return indexCount;
        }
        // if the value is not found...
        else {
            // increment the index
            indexCount++;
            // traverse the listVector
            travel = travel->next;
        }
    }
    // return -1, if the value is not found
    return -1;
}

/*
* class method : printVector
*
* Description:
*      This method prints listVector to the console and an output file.
* Parameters:
*      ofstream &output | output file stream
*
* Returns:
*      void
*/
void listVector::printVector(ofstream &outfile) {
    // create traversal Node
    Node* travel = front;
    // formats output
    cout << '[';
    outfile << '[';
    
    // while travel is not NULL...
    while(travel) {
        // print the element at the index
        cout<<travel->element;
        outfile << travel->element;
        if(travel->next) {
            // formats output
            cout<<", ";
            outfile << ", ";
        }
        // traverses listVector
        travel = travel->next;
    }
    // formats output
    cout << ']';
    outfile << ']';
    cout<<endl;
    outfile << endl;
}

/*
* class method : sortVector
*
* Description:
*      This method traverses an array and sorts the elements.
* Parameters:
*      none
*
* Returns:
*      void
*/
void listVector::sortVector() {
    // create travel nodes
    Node* t1 = front;
    Node* t2 = front;

    // traverse the listVector
    for(int i = 0; i < vectorSize(); i++) {
        for(int j = 0; j < vectorSize(); j++) {
            // if the element at t1 is greater than the element at t2...
            if(t1->element < t2->element) {
                // swap the elements
                int tempVal = t1->element;
                t1->element = t2->element;
                t2->element = tempVal;
            }
            // update travel node
            t2 = t2->next;
        }
        // update travel node
        t2 = front;
        t1 = front->next;
        // keeps t1 from being null
        for(int k = 0; k < i; k++) {
            t1 = t1->next;
        }
    }
}

/*
* class method : vectorSize
*
* Description:
*      This method traverses listVector and increaments a count variable
*      which holds the size.
* Parameters:
*      none
*
* Returns:
*      int | the size of the listVector
*/
int listVector::vectorSize() {
    // create traversal Node
    Node* travel = front;
    // stores the size of the listVector
    int s = 0;
    
    // while travel is not NULL...
    while(travel) {
        // increments size of listVector
        s++;
        // updates travel Node
        travel = travel->next;
    }
    // returns the size of the listVector
    return s;
}