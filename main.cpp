#include <iostream>
#include <unordered_map>

using namespace std;

struct ListNode {
    long long val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(long long x) : val(x), next(nullptr) {}

    ListNode(long long x, ListNode *next) : val(x), next(next) {}
};


ListNode *LinkCollatz(long long num, unordered_map<long long, ListNode *> &m1) {
    //if we find a node in hash set, immediately return the storing nodes, in order to cut off the extra calculations.
    if (m1[num]) return m1[num];
    // This is the interesting one: when we arrive here, it means that the number is never calculated before, so we decide to calculate
    //              I test before, a m1[num] statement will create something like 0x0, which is quite same as a pointer
    // So we create a pointer and pointing it to a new ListNode, which having num/2 when num is even,  3num+1 when it was odd.
    m1[num] = new ListNode(num, (num % 2 == 0) ? LinkCollatz(num / 2, m1) : LinkCollatz(3 * num + 1, m1));
    return m1[num];
}


int main() {
    //a hashmap storing the value and the ListNode pointer having this value
    // But why don't we just store the pointer in a hash_set? Because it's hard to manipulate with the address.
    unordered_map<long long, ListNode *> m1;
    //create base nodes. 4->2->1
    m1[1] = new ListNode(1, nullptr);
    m1[2] = new ListNode(2, m1[1]);
    m1[4] = new ListNode(4, m1[2]);

    //Initialize the range and promote users to enter.
    long long n = 0;
    cout << "Enter an integer equals to 1000000 or less: ";
    cin >> n;


    //maxCount stores the max count of nodes we discovered, and the maxPos stores what its name tells.
    int maxCount = INT_MIN;
    int maxPos = 0;
    ListNode *cur;

    //for loop till the up limit, each iteration we find the collatz path and get the max and stuffs.
    for (int i = 1; i <= n; i++) {
        LinkCollatz(i, m1);
        cur = m1[i];
        int count = 0;
        while (cur) {
            cur = cur->next;
            count++;
        }
        if (count > maxCount) {
            maxCount = count;
            maxPos = i;
        }
    }

    cur = m1[maxPos];       //repoint to the max one, and then traversal the nodes.
    cout << "In the range less or equals to " << n << ", the number " << maxPos
         << " has the longest collatz sequence of " << maxCount << " terms" << endl;
    cout << "The diagram showed below: " << endl;
    while (cur) {
        // no arrow in the end.
        if (!cur->next) {
            cout << cur->val;
            break;
        }
        cout << cur->val << "->";
        cur = cur->next;
    }
}
