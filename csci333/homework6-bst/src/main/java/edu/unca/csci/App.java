package edu.unca.csci;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main(String[] args)
    {
        testBST();
    }

    public static void testBST() {
        int[] input = new int[] { 77, 62, 28, 100, 15, 79, 27, 43, 73, 49, 53, 4, 84, 57, 6, 64, 22, 89, 44, 65 };
        BinarySearchTree<Integer> tree = new BinarySearchTree<Integer>();

        System.out.print("Filling the BST with 20 values: ");
        for (int i = 0; i < input.length; i++) {
            System.out.print(input[i] + " ");
            tree.insertKey(input[i]);
        }

        System.out.print("\n\n");

        System.out.print("Pre-order: ");
        tree.preOrderTraversal();
        System.out.print("In-order: ");
        tree.inOrderTraversal();
        System.out.print("Post-order: ");
        tree.postOrderTraversal();

        System.out.println();

        System.out.println("BST size: " + tree.getSize());

        System.out.println();

        System.out.println("Searching for 5 values -- expecting each to exist");
        System.out.println("\t- Searching for value: " + 62 + (tree.search(62) == null ? ", not found" : ", found"));
        System.out.println("\t- Searching for value: " + 15 + (tree.search(15) == null ? ", not found" : ", found"));
        System.out.println("\t- Searching for value: " + 49 + (tree.search(49) == null ? ", not found" : ", found"));
        System.out.println("\t- Searching for value: " + 6 + (tree.search(6) == null ? ", not found" : ", found"));
        System.out.println("\t- Searching for value: " + 44 + (tree.search(44) == null ? ", not found" : ", found"));

        System.out.println();

        System.out.println("Searching for 5 values -- expecting each to not exist");
        System.out.println("\t- Searching for value: " + 99 + (tree.search(99) == null ? ", not found" : ", found"));
        System.out.println("\t- Searching for value: " + 101 + (tree.search(101) == null ? ", not found" : ", found"));
        System.out.println("\t- Searching for value: " + 29 + (tree.search(29) == null ? ", not found" : ", found"));
        System.out.println("\t- Searching for value: " + 1 + (tree.search(1) == null ? ", not found" : ", found"));
        System.out.println("\t- Searching for value: " + 61 + (tree.search(61) == null ? ", not found" : ", found"));

        System.out.println();

        System.out.println("Deleting 5 items");
        System.out.println("\t- Deleting node with value: 62");
        tree.deleteNode(tree.search(62));
        System.out.println("\t- Deleting node with value: 15");
        tree.deleteNode(tree.search(15));
        System.out.println("\t- Deleting node with value: 49");
        tree.deleteNode(tree.search(49));
        System.out.println("\t- Deleting node with value: 6");
        tree.deleteNode(tree.search(6));
        System.out.println("\t- Deleting node with value: 44");
        tree.deleteNode(tree.search(44));

        System.out.println();

        System.out.print("In-order: ");
        tree.inOrderTraversal();
        System.out.println("BST size: " + tree.getSize());

        System.out.println();
    }
}
