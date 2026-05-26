#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;
Tree::Tree(): anker{ nullptr }, CurrentNodeChronologicalID{0} {}

/**
 * Rekursive Hilfsfunktion f�r die Suche nach einem Knoten mittels Namensvergleich.
 * Da der Name kein Alleinstellungsmerkmal ist, muss der gesamte Baum in Preorder durchlaufen und gepr�ft werden.
 * Eine Score ermittelt die Fundh�ufigkeit eines Namens.
 *
 * \param[in] node Aktueller Knoten im Baum
 * \param[in] Name String nach dem gesucht wird
 * \param[out] score Anzahl der gefundenen Knoten mit entsprechendem Namen
 */

Tree::~Tree() {}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void searchNode_RecHelper(TreeNode* node, std::string Name, int &score)
{
	if (node->getName() == Name)
	{
		node->print();
		score++;
	}
	if (node->getLeft() != nullptr)
		searchNode_RecHelper(node->getLeft(), Name, score);
	if (node->getRight() != nullptr)
		searchNode_RecHelper(node->getRight(), Name, score);
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


/**
 * Rekursive Suche nach Knoten (preorder)
 *
 * \string Name Der String der im Baum gesucht werden soll
 */
bool Tree::searchNode(std::string Name) 
{
	if (anker == nullptr) return false;
	
	int search_score = 0;
	searchNode_RecHelper(anker, Name, search_score);
	
	if(search_score > 0) return true;
	
	return false;
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


/**
 * Ausgabe aller Knoten in Tabellenform Levelorder-BST
 *
 */
void Tree::printAll() // Level-order traversal of the BST
{
	///////////////////////////////////////
	// Ihr Code hier:
	TreeNode* root = anker; // Setzt den Wurzelknoten des Baums
	queue<TreeNode*> q; // Queue für die Knoten
	//queue<int> level; 

	if (root == nullptr) // Überprüft, ob der Baum leer ist
	{
		cout << "Baum Leer" << endl;
		return;
	}

	q.push(root); // Wurzelknoten in die Queue einfügen
	//level.push(1); 

	while (!q.empty()) // Solange die Queue nicht leer ist
	{
		TreeNode* node = q.front(); // Nimmt den vordersten Knoten
		q.pop(); // Entfernt den vordersten Knoten aus der Queue

		// Ausgabe der Knoteninformationen
		cout << std::setw(4) << node->getNodeChronologicalID() << "|"
			<< setw(20) << node->getName() << "|"
			<< setw(8) << node->getAge() << "|"
			<< setw(8) << node->getIncome() << "|"
			<< setw(10) << node->getNodeOrderID() << "|"
			<< setw(3) << node->getRed() << endl;
		
		// Linken Kindknoten in die Queue einfügen, falls vorhanden
		if (node->getLeft() != nullptr) {
			q.push(node->getLeft());
		}
		// Rechten Kindknoten in die Queue einfügen, falls vorhanden
		if (node->getRight() != nullptr) {
			q.push(node->getRight());
		}
	}
	return;
	///////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Tree::printLevelOrder(void) // Level-order Traversal der schwarzen Knoten
{
	TreeNode* root = anker; // Setzt den Wurzelknoten des Baums
	queue<TreeNode*> q; // Queue für die Knoten
	queue<int> niv; // Queue für die Ebenen

	if (root == nullptr) // Überprüft, ob der Baum leer ist
	{
		cout << "Baum Leer" << endl;
		return;
	}

	q.push(root); // Wurzelknoten in die Queue einfügen
	niv.push(0); // Ebene der Wurzel ist 0
	int current_niv = 0; // Aktuelle Ebene
	int old_niv = -1; // Vorherige Ebene (initialisiert auf -1)

	while (!q.empty()) // Solange die Queue nicht leer ist
	{
		TreeNode* node = q.front(); // Nimmt den vordersten Knoten
		q.pop(); // Entfernt den vordersten Knoten aus der Queue
		current_niv = niv.front(); // Nimmt die vorderste Ebene
		niv.pop(); // Entfernt die vorderste Ebene aus der Queue
		
		if (current_niv != old_niv) // Wenn die Ebene sich ändert
		{
			cout << endl;
			cout << "Niv. " << current_niv << ": "; // Neue Ebene ausgeben
			old_niv = current_niv; // Aktualisiert die alte Ebene
		}
		
		cout << "(";

		// Linken Kindknoten behandeln
		if (node->getLeft() != nullptr) 
		{
			if (!node->getLeft()->getRed()) // Wenn der linke Nachfolger schwarz ist
			{
				q.push(node->getLeft());
				niv.push(current_niv + 1);
			}
			else // Wenn der linke Nachfolger rot ist
			{
				cout << node->getLeft()->getNodeOrderID() << ", ";
				if (node->getLeft()->getLeft() != nullptr) // Linken Kindknoten des roten Nachfolgers in die Queue einfügen
				{
					q.push(node->getLeft()->getLeft());
					niv.push(current_niv + 1);
				}
				if (node->getLeft()->getRight() != nullptr) // Rechten Kindknoten des roten Nachfolgers in die Queue einfügen
				{
					q.push(node->getLeft()->getRight());
					niv.push(current_niv + 1);
				}	
			}
		}

		cout << node->getNodeOrderID();
		
		// Rechten Kindknoten behandeln
		if (node->getRight() != nullptr) 
		{
			if (!node->getRight()->getRed()) // Wenn der rechte Nachfolger schwarz ist
			{
				q.push(node->getRight());
				niv.push(current_niv + 1);
			}
			else // Wenn der rechte Nachfolger rot ist
			{
				cout << ", " << node->getRight()->getNodeOrderID();
				if (node->getRight()->getLeft() != nullptr) // Linken Kindknoten des roten Nachfolgers in die Queue einfügen
				{
					q.push(node->getRight()->getLeft());
					niv.push(current_niv + 1);
				}
				if (node->getRight()->getRight() != nullptr) // Rechten Kindknoten des roten Nachfolgers in die Queue einfügen
				{
					q.push(node->getRight()->getRight());
					niv.push(current_niv + 1);
				}
			}
		}

		cout << ") ";
	}
	cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Tree::printLevelOrder(int niveau) // Level-order Traversal für eine bestimmte Ebene
{
	TreeNode* root = anker; // Setzt den Wurzelknoten des Baums
	queue<TreeNode*> q; // Queue für die Knoten
	queue<int> niv; // Queue für die Ebenen

	if (root == nullptr) // Überprüft, ob der Baum leer ist
	{
		cout << "Baum Leer" << endl;
		return;
	}

	q.push(root); // Wurzelknoten in die Queue einfügen
	niv.push(0); // Ebene der Wurzel ist 0
	int current_niv = 0; // Aktuelle Ebene

	cout << "Niv. " << niveau << ": ";

	while (!q.empty()) // Solange die Queue nicht leer ist
	{
		TreeNode* node = q.front(); // Nimmt den vordersten Knoten
		q.pop(); // Entfernt den vordersten Knoten aus der Queue
		current_niv = niv.front(); // Nimmt die vorderste Ebene
		niv.pop(); // Entfernt die vorderste Ebene aus der Queue
		
		// Linken Kindknoten behandeln
		if (node->getLeft() != nullptr) 
		{
			if (!node->getLeft()->getRed()) // Wenn der linke Nachfolger schwarz ist
			{
				q.push(node->getLeft());
				niv.push(current_niv + 1);
				if (niveau == current_niv)
				{
					cout << "(";
				}
			}
			else // Wenn der linke Nachfolger rot ist
			{
				if (node->getLeft()->getLeft() != nullptr)
				{
					q.push(node->getLeft()->getLeft());
					niv.push(current_niv + 1);
				}
				if (node->getLeft()->getRight() != nullptr)
				{
					q.push(node->getLeft()->getRight());
					niv.push(current_niv + 1);
				}
				if (niveau == current_niv)
				{
					cout << "(" << node->getLeft()->getNodeOrderID() << ", ";
				}
			}
		}
		else
		{
			if (niveau == current_niv)
			{
				cout << "(";
			}
		}

		if (niveau == current_niv)
		{
			cout << node->getNodeOrderID();
		}

		// Rechten Kindknoten behandeln
		if (node->getRight() != nullptr) 
		{
			if (!node->getRight()->getRed()) // Wenn der rechte Nachfolger schwarz ist
			{
				q.push(node->getRight());
				niv.push(current_niv + 1);
				if (niveau == current_niv)
				{
					cout << ") ";
				}
			}
			else // Wenn der rechte Nachfolger rot ist
			{
				if (node->getRight()->getLeft() != nullptr)
				{
					q.push(node->getRight()->getLeft());
					niv.push(current_niv + 1);
				}
				if (node->getRight()->getRight() != nullptr)
				{
					q.push(node->getRight()->getRight());
					niv.push(current_niv + 1);
				}
				if (niveau == current_niv)
				{
					cout << ", " << node->getRight()->getNodeOrderID() << ") ";
				}
			}
		}
		else
		{
			if (niveau == current_niv)
			{
				cout << ") ";
			}
		}
	}
	cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool Tree::split4Node(TreeNode* node)
{
	if (node->getRed()== true)// node muss schwarz sein
	{
		return false;
	}
	if (node->getLeft()!=nullptr && node->getRight()!= nullptr)// node muss zwei Nachfolger haben
	{
		if (node->getLeft()->getRed() && node->getRight()->getRed())// die zwei Nachfolger muessen rot sein
		{
			if (node != anker)// node umfaerben, wenn node nicht der wurzel ist 
			{
				node->setRed(true);
			}
			// die Nachfolger umfaerben 
			node->getLeft()->setRed(false);
			node->getRight()->setRed(false);
			return true;
		}
		
	}
	return false;
	
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


bool Tree::addNode(std::string Name, int Age, double Income, int  PostCode)
{
	int NodeOrderID = Age + Income + PostCode;
	TreeNode* neu_node= new TreeNode(NodeOrderID, CurrentNodeChronologicalID, Name, Age, Income, PostCode);
	
	TreeNode* child = anker;
	TreeNode* parent =nullptr;
	while (child != nullptr)
	{
		split4Node(child);//wenn ein 4-er-Knoten erkannt, mit der Methode split4Node()umgefaerbt.
		parent = child;//parent anpassen 

		if (neu_node->getNodeOrderID()< child->getNodeOrderID())
		{
			child= child->getLeft();
		}
		else
		{
			child= child->getRight();
		}
		
	}
	
	if (parent == nullptr)// Baum ist leer
	{
		neu_node->setRed(false);
		anker=neu_node;
		CurrentNodeChronologicalID++;
		
	}

	else if(neu_node->getNodeOrderID()< parent->getNodeOrderID())
	{
		parent->setLeft(neu_node);
		neu_node->setParent(parent);
		CurrentNodeChronologicalID++;
	}
	else
	{
		parent->setRight(neu_node);
		neu_node->setParent(parent);
		CurrentNodeChronologicalID++;
	}

	TreeNode* node = neu_node;
	int red_node=0;
	// Untersuchen vom eingefugten Blattknoten bis zur Wurzel (Bottom-Up), ob zwei rote Knoten aufeinanderfolgen
	while (node!= nullptr) 
	{
		if (node->getRed()==false)
		{
			red_node=0;
		}
		else
		{
			red_node++;
		}
		if (red_node==2)
		{
			balance(node);
		}
		node = node->getParent();
		
	}
	return true;
}
	
	
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Tree::balance(TreeNode* node) {
    // Links-Rechts-Knick => 1.LR -> 2.RR
    if (node->getParent() != nullptr && node->getRight() != nullptr) {
        if (node->getNodeOrderID() < node->getParent()->getNodeOrderID() && node->getRight()->getRed()) {
            cout << "1.LR(" << node->getNodeOrderID() << ", " << node->getRight()->getNodeOrderID() << ")" << endl;
            rotateTreeLeft(node->getRight());
            cout << "2.RR(" << node->getParent()->getParent()->getNodeOrderID() << ", " << node->getParent()->getNodeOrderID() << ")" << endl;
            rotateTreeRight(node->getParent());
            node->getParent()->setRed(false);
            node->getParent()->getRight()->setRed(true);

            return;
        }
    }

    // Rechts-Links-Knick => 1.RR-> 2.LR
    if (node->getParent() != nullptr && node->getLeft() != nullptr) {
        if (node->getNodeOrderID() > node->getParent()->getNodeOrderID() && node->getLeft()->getRed()) {
            cout << "1.RR(" << node->getNodeOrderID() << ", " << node->getLeft()->getNodeOrderID() << ")" << endl;
            rotateTreeRight(node->getLeft());
            cout << "2.LR(" << node->getParent()->getParent()->getNodeOrderID() << ", " << node->getParent()->getNodeOrderID() << ")" << endl;
            rotateTreeLeft(node->getParent());
            node->getParent()->setRed(false);
            node->getParent()->getLeft()->setRed(true);

            return;
        }
    }

    // Rotation ohne Knick -> LR
    if (node->getParent() != nullptr && node->getRight() != nullptr) {
        if (node->getNodeOrderID() > node->getParent()->getNodeOrderID() && node->getRight()->getRed()) {
            cout << "LR(" << node->getParent()->getNodeOrderID() << ", " << node->getNodeOrderID() << ")" << endl;
            rotateTreeLeft(node);
            node->setRed(false);
            node->getLeft()->setRed(true);

            return;
        }
    }

    // Rotation ohne Knick -> RR
    if (node->getParent() != nullptr && node->getLeft() != nullptr) {
        if (node->getNodeOrderID() < node->getParent()->getNodeOrderID() && node->getLeft()->getRed()) {
            cout << "RR(" << node->getParent()->getNodeOrderID() << ", " << node->getNodeOrderID() << ")" << endl;
            rotateTreeRight(node);
            node->setRed(false);
            node->getRight()->setRed(true);

            return;
        }
    }
}

bool Tree::rotateTreeLeft(TreeNode* child) {
    TreeNode* parent = child->getParent();
    TreeNode* p_parent = parent->getParent();

    // Wenn wir uns am Anker befinden
    if (parent == anker) {
        anker = child;
        child->setParent(nullptr);
    } else {
        // Entscheiden, ob child links oder rechts von p_parent steht
        if (p_parent->getNodeOrderID() > child->getNodeOrderID()) {
            p_parent->setLeft(child);
            child->setParent(p_parent);
        } else {
            p_parent->setRight(child);
            child->setParent(p_parent);
        }
    }

    // Die eigentliche Rotation
    parent->setParent(child);
    parent->setRight(child->getLeft());

    if (child->getLeft() != nullptr) {
        child->getLeft()->setParent(parent);
    }

    child->setLeft(parent);
    return true;
}

bool Tree::rotateTreeRight(TreeNode* child) {
    TreeNode* parent = child->getParent();
    TreeNode* p_parent = parent->getParent();

    // Wenn wir uns am Anker befinden
    if (anker == parent) {
        anker = child;
        child->setParent(nullptr);
    } else {
        // Entscheiden, ob child links oder rechts von p_parent steht
        if (p_parent->getNodeOrderID() > child->getNodeOrderID()) {
            p_parent->setLeft(child);
            child->setParent(p_parent);
        } else {
            p_parent->setRight(child);
            child->setParent(p_parent);
        }
    }

    // Die eigentliche Rotation
    parent->setParent(child);
    parent->setLeft(child->getRight());

    if (child->getRight() != nullptr) {
        child->getRight()->setParent(parent);
    }

    child->setRight(parent);
    return true;
}

int Tree::proofRBCriterion() {
    return proofRBCriterion(anker);
}

int Tree::proofRBCriterion(TreeNode* node) {
    if (node == nullptr) {
        return -1; // Ungültige Höhe für leeren Knoten
    }

    int leftHeight = proofRBCriterion(node->getLeft());
    int rightHeight = proofRBCriterion(node->getRight());

    // Fall 1: Blattknoten (beide Nachfolger existieren nicht)
    if (node->getLeft() == nullptr && node->getRight() == nullptr) {
        return 0;
    }

    // Fall 2: Beide Nachfolger sind rot
    if (node->getLeft() != nullptr && node->getRight() != nullptr &&
        node->getLeft()->getRed() && node->getRight()->getRed()) {
        if (leftHeight == rightHeight) {
            return leftHeight;
        }
    }

    // Fall 3: Einer der Nachfolger ist rot, der andere schwarz
    if (node->getLeft() != nullptr && node->getRight() != nullptr) {
        if (node->getLeft()->getRed() && !node->getRight()->getRed()) {
            if (leftHeight == rightHeight + 1) {
                return leftHeight;
            } else if (!node->getLeft()->getRed() && node->getRight()->getRed()) {
                if (leftHeight + 1 == rightHeight) {
                    return rightHeight;
                }
            }
        }
    }

    // Fall 4: Beide Nachfolger sind schwarz
    if (node->getLeft() != nullptr && node->getRight() != nullptr &&
        !node->getLeft()->getRed() && !node->getRight()->getRed()) {
        if (leftHeight == rightHeight) {
            return leftHeight + 1;
        }
    }

    // Fall 5: Einer der Nachfolger existiert nicht
    if ((node->getLeft() && !node->getRight()) || (!node->getLeft() && node->getRight())) {
        if (node->getLeft() && !node->getRight()) {
            if (node->getLeft()->getRed()) {
                return leftHeight;
            } else {
                return leftHeight + 1;
            }
        } else if (!node->getLeft() && node->getRight()) {
            if (node->getRight()->getRed()) {
                return rightHeight;
            } else {
                return rightHeight + 1;
            }
        }
    }

    return -1; // Ungültige Höhe für inkonsistente Fälle
}

void Tree::start() {
    int rootHeight = proofRBCriterion(anker);

    if (rootHeight == -1) {
        cout << "Der Baum ist nicht schwarzausgeglichen!" << endl;
    } else {
        cout << "Der Baum ist schwarzausgeglichen und die Höhe der Wurzel ist: " << rootHeight << endl;
    }
}
