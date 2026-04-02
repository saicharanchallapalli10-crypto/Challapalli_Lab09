#include <iostream>
#include <string>
using namespace std;


struct ListNode {
    int id;
    string name;
    ListNode* next;
};

class NodeList {
private:
    ListNode* head;
    int count;

public:
    NodeList() : head(nullptr), count(0) {}

    void addNode(int id, string name) {
        ListNode* n = new ListNode{id, name, head};
        head = n;
        count++;
    }

    void removeNode(int id) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr && curr->id != id) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) return;
        if (prev) prev->next = curr->next;
        else head = curr->next;
        delete curr;
        count--;
    }

    void display() const {
        ListNode* curr = head;
        while (curr) {
            cout << "[" << curr->id << ": "
                 << curr->name << "] -> ";
            curr = curr->next;
        }
        cout << "null" << endl;
    }

    // TODO: Implement destructor, copy constructor, operator=
    // (Part A deliverable)

    ~NodeList() {
        // Your code: free all nodes
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    NodeList(const NodeList& other) : head(nullptr), count(0) {
        ListNode* curr = other.head;
        while (curr) {
            addNode(curr->id, curr->name);
            curr = curr->next;
        }
    }

    NodeList& operator=(NodeList other) {
        swap(head, other.head);
        swap(count, other.count);
        return *this;
    }
};
//added a main, so that code can compile 
int main() {
    NodeList list;
    list.addNode(1, "c");
    list.addNode(2, "B");
    list.addNode(3, "e");
    list.display();
    list.removeNode(2);
    list.display();
    NodeList copy = list;
    copy.display();

    return 0;
}