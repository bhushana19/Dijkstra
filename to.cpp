#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Node {
    int id;
    int distance;
    Node* previous;
    bool isClosed; // new field to indicate if the node is closed
};

struct Edge {
    int from;
    int to;
    int weight;
    bool isClosed; // new field to indicate if the edge is closed
};

vector<Node> nodes;
vector<Edge> edges;

void dijkstra(int startNode) {
    // Initialize distances and previous nodes
    for (Node& node : nodes) {
        node.distance = numeric_limits<int>::max();
        node.previous = nullptr;
    }

    nodes[startNode].distance = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, startNode});

    while (!pq.empty()) {
        int currentNode = pq.top().second;
        pq.pop();

        for (Edge& edge : edges) {
            if (edge.from == currentNode && !edge.isClosed) { // check if edge is not closed
                int neighbor = edge.to;
                int weight = edge.weight;

                if (!nodes[neighbor].isClosed) { // check if neighbor node is not closed
                    if (nodes[neighbor].distance > nodes[currentNode].distance + weight) {
                        nodes[neighbor].distance = nodes[currentNode].distance + weight;
                        nodes[neighbor].previous = &nodes[currentNode];
                        pq.push({nodes[neighbor].distance, neighbor});
                    }
                }
            }
        }
    }
}

void printShortestPath(int endNode) {
    vector<int> path;
    Node* currentNode = &nodes[endNode];

    while (currentNode != nullptr) {
        path.push_back(currentNode->id);
        currentNode = currentNode->previous;
    }

    std::reverse(path.begin(), path.end());

    cout << "Shortest path: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
}

int main() {
    // Example graph data
    nodes = {{0, false}, {1, false}, {2, false}, {3, false}, {4, false}};
    edges = {
        {0, 1, 2, false}, // 0 -> 1 (weight 2)
        {0, 2, 3, false}, // 0 -> 2 (weight 3)
        {1, 3, 1, false}, // 1 -> 3 (weight 1)
        {2, 3, 2, false}, // 2 -> 3 (weight 2)
        {2, 4, 4, false}, // 2 -> 4 (weight 4)
        {3, 4, 1, false}  // 3 -> 4 (weight 1)
    };

    // Display movement directions
    printf("Movement directions:\n");
    printf("0 -> 1 (east)\n");
    printf("0 -> 2 (south)\n");
    printf("1 -> 3 (east)\n");
    printf("2 -> 3 (east)\n");
    printf("2 -> 4 (south)\n");
    printf("3 -> 4 (east)\n");

    // Ask user for start and end nodes
    int startNode, endNode;
    cout << "Enter start node (0-4): ";
    cin >> startNode;
    cout << "Enter end node (0-4): ";
    cin >> endNode;

    dijkstra(startNode);
    printShortestPath(endNode);

    char choice;
    cout << "Do you want to avoid a particular road? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int avoidNode;
        cout << "Enter the node to avoid: ";
        cin >> avoidNode;

        nodes[avoidNode].isClosed = true;

        dijkstra(startNode);
        printShortestPath(endNode);
    }

    return 0;
}