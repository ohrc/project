#include <iostream>
#include <string>
using namespace std;

// Declare the structure for the goods
struct Goods {
    int id;
    string name;
    double price;
    int quantity;
};

// Declare the structure for the search tree node
struct TreeNode {
    Goods data;
    TreeNode* left;
    TreeNode* right;
};

// Declare the functions for the search tree operations
void insert(TreeNode*& root, Goods item) {
    if (root == NULL) {
        root = new TreeNode{item, NULL, NULL};
    } else if (item.id < root->data.id) {
        insert(root->left, item);
    } else {
        insert(root->right, item);
    }
}

void remove(TreeNode*& root, int id) {
    if (root == NULL) {
        cout << "The list is empty." << endl;
        return;
    }

    if (id < root->data.id) {
        remove(root->left, id);
    } else if (id > root->data.id) {
        remove(root->right, id);
    } else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        } else if (root->left == NULL) {
            TreeNode* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right== NULL) {
            TreeNode* temp = root;
            root = root->left;
            delete temp;
        } else {
            TreeNode* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->data = temp->data;
            remove(root->right, temp->data.id);
        }
        cout << "The goods with ID " << id << " has been deleted." << endl;
    }
}

void display(TreeNode* root) {
    if (root == NULL) {
        cout << "The list is empty." << endl;
        return;
    }

    if (root->left != NULL) {
        display(root->left);
    }
    cout << root->data.id << "\t" << root->data.name << "\t" << root->data.price << "\t" << root->data.quantity << endl;
    if (root->right != NULL) {
        display(root->right);
    }
}

void modify(TreeNode* root, int id, string name, double price, int quantity) {
    if (root == NULL) {
        cout << "The goods with ID " << id << " was not found." << endl;
        return;
    }

    if (root->data.id == id) {
        root->data.name = name;
        root->data.price = price;
        root->data.quantity = quantity;
        cout << "The goods with ID" << id << " has been modified." << endl;
    } else if (id < root->data.id) {
        modify(root->left, id, name, price, quantity);
    } else {
        modify(root->right, id, name, price, quantity);
    }
}

int main() {
    // Initialize the search tree
    TreeNode* root = NULL;

    // Loop for the menu options
    int choice;
    while (true) {
        cout << endl;
        cout << "1. Add goods\n";
        cout <<"2. Delete goods\n";
        cout << "3. Display goods\n";
        cout << "4. Modify goods\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Add goods
        if (choice == 1) {
            int id, quantity;
            string name;
            double price;
            cout << "Enter the ID: ";
            cin >> id;
            cout << "Enter the name: ";
            cin >> name;
            cout << "Enter the price: ";
            cin >> price;
            cout << "Enter the quantity: ";
            cin >> quantity;
            Goods item{id, name, price, quantity};
            insert(root, item);
            cout << "The goods with ID " << id << " has been added." << endl;
        }

        // Delete goods
        else if (choice == 2){
            int id;
            cout << "Enter the ID of the goods to delete: ";
            cin >> id;
            remove(root, id);
        }

        // Display goods
        else if (choice == 3) {
            display(root);
        }

        // Modify goods
        else if (choice == 4) {
            int id, quantity;
            string name;
            double price;
            cout << "Enter the ID of the goods to modify: ";
            cin >> id;
            cout << "Enter the new name: ";
            cin >> name;
            cout << "Enter the new price:";
            cin >> price;
            cout << "Enter the new quantity: ";
            cin >> quantity;
            modify(root, id, name, price, quantity);
        }

        // Exit the program
        else if (choice == 5) {
            cout << "Exiting the program." << endl;
            break;
        }

        // Invalid input
        else {
            cout << "Invalid input. Please try again." << endl;
        }
    }

    return 0;
}
