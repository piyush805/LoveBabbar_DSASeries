#include <iostream>
#include <queue>

using namespace std;

int main()
{
    priority_queue<int> pq; // max heap bydefault
    pq.push(23);
    pq.push(45);
    pq.push(20);
    pq.push(13);
    pq.push(5);
    cout << pq.top() << endl; // root element
    pq.pop();                 // root deleted
    cout << pq.top() << endl; // updated root element
    cout << pq.size() << endl;
    cout << pq.empty() << endl;
    cout << endl
         << "Min heap:" << endl;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(23);
    minHeap.push(45);
    minHeap.push(20);
    minHeap.push(13);
    minHeap.push(5);
    cout << minHeap.top() << endl; // root element
    minHeap.pop();                 // root deleted
    cout << minHeap.top() << endl; // updated root element
    cout << minHeap.size() << endl;
    cout << minHeap.empty() << endl;
    return 0;
}