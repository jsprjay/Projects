/*******************************************************************************
 * Filename: waterjugpuzzle.cpp
 * Author  : Jasper Tumbokon
 * Version : 1.0
 * Date    : October 22, 2022
 * Description: Solves the famous water jug puzzle using bfs.
 * Pledge  : 
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    State(int _a, int _b, int _c, string _directions, State *_parent) :
    	a{_a}, b{_b}, c{_c}, directions{_directions}, parent{_parent} { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

// Main water jug function. Takes in 6 int values and returns a string.
string waterjug(int cA, int cB, int cC, int gA, int gB, int gC) {
	queue<State> jugHold; // queue that holds all the possible jug pours.
	vector<State*> children; // vector that holds all the pointers to the parents.
	string result; // string that will hold the final print statement.
	State first = State(0, 0, cC, "Initial State."); // creates a state that holds the initial state.
	jugHold.push(first); // put it into the queue
	State fill = State(0, 0, 0, ""); // create filler states to check if visited or not.
	vector<vector<State>> jugs(cA + 1, vector<State> (cB + 1, fill)); // create a 2d vector (easier than 2d array).
	while(!jugHold.empty()) {
		State currJug = jugHold.front();
		jugHold.pop();
		if (currJug.a == gA && currJug.b == gB && currJug.c == gC) { // checks to see if the current jug is equal to the goal jug.
			result = "Initial state. " + first.to_string() + "\n";
			stack<State> almostDone; // create a stack to store each pour step.
			while (currJug.parent != nullptr) { // loop that stores each pour step.
				almostDone.push(currJug);
				currJug = *currJug.parent; // sets currJug to the parent of currJug.
			}
			while (!almostDone.empty()) { // iterates through the stack to print the steps in order.
				result +=  almostDone.top().directions + " " + almostDone.top().to_string() + "\n";
				almostDone.pop();
			}
			for (unsigned long i = 0; i < children.size(); i++) { // delete pointers to free up memory.
				delete children[i];
			}
		return result; // return the result string with all the added pours.
		}
		if (jugs[currJug.a][currJug.b].directions.empty()) { // checks to see if the directions at the current jug vector is empty (seen).
			int pour;
			string string; // string that denotes what is pouring into what.
			State* old; // creates a pointer to the current jug.
			jugs[currJug.a][currJug.b] = currJug; // sets the jug to seen.
			if (currJug.a < cA && currJug.c > 0) { // pour C to A.
				if (currJug.c < cA - currJug.a) { // checks how much to pour.
					pour = currJug.c;
				} else {
					pour = cA  - currJug.a;
				}
				if (pour == 1) { // checks if it is more than one gallon being poured.
					string = "Pour " + to_string(pour) + " gallon from C to A.";
				} else {
					string = "Pour " + to_string(pour) + " gallons from C to A.";
				}
				old = new State(currJug.a, currJug.b, currJug.c, currJug.directions, currJug.parent); // creates pointer to current jug (new parent).
				jugHold.push(State(currJug.a + pour, currJug.b, currJug.c - pour, string, old)); // pushes jug into the queue.
				children.push_back(old); // pushes pointer into vector.
			}
			if (currJug.a < cA && currJug.b > 0) { // pour B to A.
				if (currJug.b < cA - currJug.a) {
					pour = currJug.b;
				} else {
					pour = cA  - currJug.a;
				}
				if (pour == 1) {
					string = "Pour " + to_string(pour) + " gallon from B to A.";
				} else {
					string = "Pour " + to_string(pour) + " gallons from B to A.";
				}
				old = new State(currJug.a, currJug.b, currJug.c, currJug.directions, currJug.parent);
				jugHold.push(State(currJug.a + pour, currJug.b - pour, currJug.c, string, old));
				children.push_back(old);
			}
			if (currJug.b < cB && currJug.c > 0) { // pour C to B.
				if (currJug.c < cB - currJug.b) {
					pour = currJug.c;
				} else {
					pour = cB  - currJug.b;
				}
				if (pour == 1) {
					string = "Pour " + to_string(pour) + " gallon from C to B.";
				} else {
					string = "Pour " + to_string(pour) + " gallons from C to B.";
				}
				old = new State(currJug.a, currJug.b, currJug.c, currJug.directions, currJug.parent);
				jugHold.push(State(currJug.a, currJug.b + pour, currJug.c - pour, string, old));
				children.push_back(old);
			}
			if (currJug.b < cB && currJug.a > 0) { // pour A to B.
				if (currJug.a < cB - currJug.b) {
					pour = currJug.a;
				} else {
					pour = cB  - currJug.b;
				}
				if (pour == 1) {
					string = "Pour " + to_string(pour) + " gallon from A to B.";
				} else {
					string = "Pour " + to_string(pour) + " gallons from A to B.";
				}
				old = new State(currJug.a, currJug.b, currJug.c, currJug.directions, currJug.parent);
				jugHold.push(State(currJug.a - pour, currJug.b + pour, currJug.c, string, old));
				children.push_back(old);
			}
			if (currJug.c < cC && currJug.b > 0) { // pour B to C.
				if (currJug.b < cC - currJug.c) {
					pour = currJug.b;
				} else {
					pour = cC  - currJug.c;
				}
				if (pour == 1) {
					string = "Pour " + to_string(pour) + " gallon from B to C.";
				} else {
					string = "Pour " + to_string(pour) + " gallons from B to C.";
				}
				old = new State(currJug.a, currJug.b, currJug.c, currJug.directions, currJug.parent);
				jugHold.push(State(currJug.a, currJug.b - pour, currJug.c + pour, string, old));
				children.push_back(old);
			}
			if (currJug.c < cC && currJug.a > 0) { // pour A to C.
				if (currJug.a < cC - currJug.c) {
					pour = currJug.a;
				} else {
					pour = cC  - currJug.c;
				}
				if (pour == 1) {
					string = "Pour " + to_string(pour) + " gallon from A to C.";
				} else {
					string = "Pour " + to_string(pour) + " gallons from A to C.";
				}
				old = new State(currJug.a, currJug.b, currJug.c, currJug.directions, currJug.parent);
				jugHold.push(State(currJug.a - pour, currJug.b, currJug.c + pour, string, old));
				children.push_back(old);
			}
		}
	}
	for(unsigned long i = 0; i < children.size(); i++) { // deletes pointers to free up memory.
		delete children[i];
	}
	return "No solution."; // if the queue becomes empty with no answer, return no solution.
}

int main(int argc, char* argv[]) {
	int num;
	int capA;
	int capB;
	int capC;
	int goalA;
	int goalB;
	int goalC;
	istringstream iss; // input string stream variable
	if(!(argc == 7)) { // makes sure for correct number of inputs.
	cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
	return 1;
	}
	iss.str(argv[1]);
	if(!((iss >> num) && (num > 0))) { // checks for correct capacity for jug A.
		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
		return 1;
	}
	capA = num;
	iss.clear();
	iss.str(argv[2]);
	if(!((iss >> num) && (num > 0))) { // checks for correct capacity for jug B.
		cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
		return 1;
	}
	capB = num;
	iss.clear();
	iss.str(argv[3]);
	if(!((iss >> num) && (num > 0))) { // checks for correct capacity for jug C.
		cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
		return 1;
	}
	capC = num;
	iss.clear();
	iss.str(argv[4]);
	if(!((iss >> num) && (num >= 0))) { // checks for correct goal for jug A
		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
		return 1;
		}
	goalA = num;
	iss.clear();
	iss.str(argv[5]);
	if(!((iss >> num) && (num >= 0))) { // checks for correct goal for jug B.
		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
		return 1;
		}
	goalB = num;
	iss.clear();
	iss.str(argv[6]);
	if(!((iss >> num) && (num >= 0))) { // checks for correct goal for jug C.
		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
		return 1;
		}
	goalC = num;
	if(!(capA >= goalA)) { // checks if goal is less than capacity for jug A.
		cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		return 1;
		}
	if(!(capB >= goalB)) { // checks if goal is less than capacity for jug B.
		cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		return 1;
		}
	if(!(capC >= goalC)) { // checks if goal is less than capacity for jug C.
		cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		return 1;
		}
	if(!(capC == (goalA + goalB + goalC))) { // checks if total gallons is equal to capacity of jug C.
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}
	cout << waterjug(capA, capB, capC, goalA, goalB, goalC) << endl; // call waterjug to find optimal solution.
	return 0;
}
