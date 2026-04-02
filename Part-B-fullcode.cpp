#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct SmartListNode {
    int id;
    string name;
    unique_ptr<SmartListNode> next;

    SmartListNode(int i, string n, unique_ptr<SmartListNode> nx)
        : id(i), name(n), next(move(nx)) {}
};

class SmartNodeList {
private:
    unique_ptr<SmartListNode> head;
    int count;

public:
    SmartNodeList() : head(nullptr), count(0) {}

    void addNode(int id, string name) {
        head = make_unique<SmartListNode>(id, name, move(head));
        count++;
    }

    void removeNode(int id) {
        unique_ptr<SmartListNode>* curr = &head;
        while (*curr && (*curr)->id != id)
            curr = &(*curr)->next;
        if (*curr) {
            *curr = move((*curr)->next);
            count--;
        }
    }
    void display() const {
        SmartListNode* curr = head.get();
        while (curr) {
            cout << "[" << curr->id << ": "
                 << curr->name << "] -> ";
            curr = curr->next.get();
        }
        cout << "null" << endl;
    }

    // No destructor needed! No copy constructor needed!
    // unique_ptr handles all cleanup automatically.
};
int main() {
    SmartNodeList list;
    list.addNode(1, "U");
    list.addNode(2, "L");
    list.addNode(3, "S");
    list.display();
    list.removeNode(2);
    list.display();
    SmartNodeList list2;
    list2.addNode(10, "Z");
    list2.addNode(20, "Y");
    list2.display();
    SmartNodeList list3 = move(list2);
    list3.display();
    list2.display();

    return 0;
}