#include <iostream>
#include <string>
using namespace std;

//Testing errors

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

#ifdef BUG_LEAK
    ~NodeList() {}
#else
    ~NodeList() {
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            delete curr;
            curr = next;
        }
    }
#endif

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
            cout << "[" << curr->id << ": " << curr->name << "] -> ";
            curr = curr->next;
        }
        cout << "null" << endl;
    }

    ListNode* getHead() { return head; }
};

int main() {
    NodeList list;
    list.addNode(1, "Router");
    list.addNode(2, "Switch");
    list.addNode(3, "Firewall");
    list.display();

#ifdef BUG_DOUBLE_FREE
    ListNode* node = list.getHead();
    delete node;
    delete node;

#elif defined(BUG_USE_AFTER_FREE)
    ListNode* node = list.getHead();
    delete node;
    cout << "ID after free: " << node->id << endl;

#else
    list.removeNode(2);
    list.display();
#endif

    return 0;
}