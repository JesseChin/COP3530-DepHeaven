// Author: Jesse Chintanadilok
// Last modified: December 8, 2021

// Description: Given package name, return dependencies of package.
// This file must be in the same directory as lists/ directory!
#ifndef PARSEPACKAGES_H_
#define PARSEPACKAGES_H_

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 For our optional tasks. Ignore this for now!
struct Package {
  string name;
  string version;
  string relation;
  Package(string _name, string _version) : name{_name}, version{_version} {};
};
*/

struct Package {
  string name;
  string version;
  Package(string _name, string _version) : name{_name}, version{_version} {};
};

vector<Package> getDepends(string packageName);
vector<Package> readFile(string filename, string packageName);

vector<Package> getDepends(string packageName) {
  vector<Package> dependencies;

  // Read files until one returns a non empty vector.
  // When one has a non empty vector, return that vector.
  // If package name could not be found, return an empty vector.
  vector<string> searchList = {
      "lists/"
      "security.ubuntu.com_ubuntu_dists_focal-"
      "security_main_binary-amd64_Packages",
      "lists/"
      "security.ubuntu.com_ubuntu_dists_focal-security_main_binary-i386_"
      "Packages",
      "lists/"
      "security.ubuntu.com_ubuntu_dists_focal-security_multiverse_binary-amd64_"
      "Packages",
      "lists/"
      "security.ubuntu.com_ubuntu_dists_focal-security_multiverse_binary-i386_"
      "Packages",
      "lists/"
      "security.ubuntu.com_ubuntu_dists_focal-security_restricted_binary-amd64_"
      "Packages",
      "lists/"
      "security.ubuntu.com_ubuntu_dists_focal-security_restricted_binary-i386_"
      "Packages",
      "lists/"
      "security.ubuntu.com_ubuntu_dists_focal-security_universe_binary-amd64_"
      "Packages",
      "lists/"
      "security.ubuntu.com_ubuntu_dists_focal-security_universe_binary-i386_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-backports_main_binary-amd64_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-backports_main_binary-i386_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-backports_universe_binary-"
      "amd64_Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-backports_universe_binary-i386_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal_main_binary-amd64_Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal_main_binary-i386_Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal_multiverse_binary-amd64_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal_multiverse_binary-i386_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal_restricted_binary-amd64_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal_restricted_binary-i386_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal_universe_binary-amd64_Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal_universe_binary-i386_Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-updates_main_binary-amd64_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-updates_main_binary-i386_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-updates_multiverse_binary-"
      "amd64_Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-updates_multiverse_binary-i386_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-updates_restricted_binary-"
      "amd64_Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-updates_restricted_binary-i386_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-updates_universe_binary-amd64_"
      "Packages",
      "lists/"
      "us.archive.ubuntu.com_ubuntu_dists_focal-updates_universe_binary-i386_"
      "Packages"};

  // Search through package lists until package is found in one.
  for (int i = 0; i < searchList.size(); i++) {
    dependencies = readFile(searchList[i], packageName);
    if (dependencies.size() != 0)
      break;
  }
  return dependencies;
};

vector<Package> readFile(string filename, string packageName) {
  // Helper function for getDepends.

  // If did not find package, return an empty vector.
  vector<Package> deps;

  fstream file;
  file.open(filename, ios::in);

  if (file.is_open()) {
    string str;
    bool found = false;
    while (getline(file, str)) {
      // Read file until line has the signature:
      // "Package: packageName"
      // e.g. for the package apache2, "Package: apache2"
      stringstream stream(str);
      string word;
      stream >> word;
      if (word == "Package:") {
        stream >> word;
        if (word == packageName) {
          found = true;
          break;
        }
      }
    }
    if (found) {
      // Read until line begins with "Depends: "
      // From this, extract name & version from line, and place into a vector.
      // Return vector
      while (getline(file, str)) {
        stringstream stream(str);
        string word;
        stream >> word;
        if (word == "Depends:") {
          vector<string> rawNames;
          // Parse packages name in line.
          // Example format of line for package apache2:
          // Depends: apache2-bin (= 2.4.41-4ubuntu3.6), apache2-data
          // (= 2.4.41-4ubuntu3.6), apache2-utils (= 2.4.41-4ubuntu3.6),
          // lsb-base, mime-support, perl:any, procps
          char delimiter = ',';
          while (getline(stream, str, delimiter)) {
            // Item stored in string str
            // cout << "Package Name: " << str << endl;
            stringstream ss(str);
            string name;
            ss >> name;
            // Remove any leading spaces in front of parenthesis
            string version;
            try {
              version = str.substr(str.find('('), str.find(')'));
            } catch (std::out_of_range) {
              version = "";
            }
            Package temp(name, version);

            deps.push_back(temp);
          }

          break;
        }
      }
    }
  }

  return deps;
};

#endif // PARSEPACKAGES_H_
