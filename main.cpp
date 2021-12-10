#include "Graph.h"
#include "ParsePackages.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void genGraph(unordered_map<string, vector<Package>> adjList) {
  ofstream file("output.dot", ios_base::out);
  if (file.is_open()) {
    file << "graph {" << endl;

    unordered_map<string, vector<Package>>::iterator iter = adjList.begin();
    while (iter != adjList.end()) {
      if (iter->second.size() != 0) {
        file << "    \"" << iter->first << "\" -- ";
        if (iter->second.size() == 1)
          file << " \"" << iter->second[0].name << "\";" << endl;
        else {
          file << " { ";
          for (int i = 0; i < iter->second.size(); i++)
            file << '"' << iter->second[i].name << "\" ";
          file << "};" << endl;
        }
      }
      iter++;
    }
    file << "}" << endl;

    system("dot -Tsvg output.dot > output.svg");
    cout << "Generated output.svg" << endl;
    system("xdg-open output.svg");
    system("dot -Tpng output.dot > output.png");
    cout << "Generated output.png" << endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    cout << "Searching for Dependencies of " << argv[1] << endl;
    Graph searchPackage(argv[1]);
    // searchPackage.printAllDeps();
    if (searchPackage.adjList.size() != 0)
      genGraph(searchPackage.adjList);
    else
      cout << "Error: invalid package name." << endl;
  }
  return 0;
}
