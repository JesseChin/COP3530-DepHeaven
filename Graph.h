// Authors: Jesse Chintanadilok, Connor Buch
// Last modified: December 9, 2021

// Description: Implement graph class to store package dependencies. Graph is
// set up as an unweighted directed adjacency list. In the constructor, adds
// package name and it's packages into an adjacency list.

#ifndef GRAPH_H_
#define GRAPH_H_

#include "ParsePackages.h"
#include <set>
#include <stack>
#include <unordered_map>

using namespace std;
class Graph {
private:
  void addEdge(string name, vector<Package> dependencies);
  // void recurseAddPackage(string packageName);
  void addPackages(string packageName);

public:
  unordered_map<string, vector<Package>> adjList;

  void printAllDeps(); // Print out all packages in adjacency list, listing the
                       // package name and its dependencies.

  string rootNode;

  Graph(string packageName) {
    // cout << "testing";
    rootNode = packageName;
    addPackages(packageName);
  }
};

void Graph::addEdge(string name, vector<Package> dependencies) {
  adjList[name] = dependencies;
}

void Graph::addPackages(string packageName) {
  // Given a package name, search the package's dependencies. Then, for each
  // dependency, search for it's dependencies.
  // cout << "test";
  vector<Package> deps = getDepends(packageName);
  adjList[packageName] = deps;
  stack<string> s;
  set<string> visited;
  visited.insert(packageName);

  for (int i = 0; i < deps.size(); i++) {
    s.push(deps[i].name);
    visited.insert(deps[i].name);
  }
  while (!s.empty()) {
    string temp = s.top();
    s.pop();
    vector<Package> tempDeps = getDepends(temp);
    adjList[temp] = tempDeps;
    if (tempDeps.size() != 0) {
      for (int i = 0; i < tempDeps.size(); i++) {
        if (visited.count(tempDeps[i].name) == 0) {
          s.push(tempDeps[i].name);
          visited.insert(tempDeps[i].name);
        }
      }
    }
  }
}

void Graph::printAllDeps() {
  stack<string> s;
  set<string> visited;

  vector<Package> deps = adjList[rootNode];

  cout << "Root Package Name: " << rootNode << endl << "Depends: ";
  for (int i = 0; i < deps.size(); i++) {
    cout << deps[i].name;
    if (i != deps.size() - 1)
      cout << ", ";
    s.push(deps[i].name);
  }
  cout << endl;
  while (!s.empty()) {
    string temp = s.top();
    s.pop();
    vector<Package> tempDeps = getDepends(temp);
    cout << "Package Name: " << temp << endl << "Depends: ";
    if (tempDeps.size() != 0) {
      for (int i = 0; i < tempDeps.size(); i++) {
        cout << tempDeps[i].name;
        if (i != tempDeps.size() - 1)
          cout << ", ";
        if (visited.count(tempDeps[i].name) == 0) {
          s.push(tempDeps[i].name);
          visited.insert(tempDeps[i].name);
        }
      }
      cout << endl;
    }
  }
}

#endif // GRAPH_H_
