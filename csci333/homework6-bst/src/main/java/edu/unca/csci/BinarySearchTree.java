package edu.unca.csci;

/**
 * Ethan Green - CSCI 333, Homework 6
 * 13th October, 2020
 * 
 * This is a BST implementation for Homework 6. Many of the functions are implemented recursively, so please note 
 * issues that may arise from stack recursion in large datasets.
 * 
 * The solutions here are heavily based on lectures and slides posted in the class Moodle. Sources -- if any -- are 
 * mentioned in the comments preceding each function.
 */
public class BinarySearchTree<T extends Comparable<T>> {
    private BSTNode<T> root;

    private int size;

    public BinarySearchTree() {
        this.root = null;
        this.size = 0;
    }

    /**
     * Returns the current size of the BST.
     * @return The size, in node count, of the tree.
     */
    public int getSize() {
        return this.size;
    }

    /**
     * Performs a pre-order traversal of the BST, starting at the root node.
     * The results of this traversal are written to stdout.
     */
    public void preOrderTraversal() {
        preOrderTraversal(this.root);
        System.out.println();
    }

    /**
     * Performs an in-order traversal of the BST, starting at the root node.
     * The results of this traversal are written to stdout.
     */
    public void inOrderTraversal() {
        inOrderTraversal(this.root);
        System.out.println();
    }

    /**
     * Performs a post-order traversal of the BST, starting at the root node.
     * The results of this traversal are written to stdout.
     */
    public void postOrderTraversal() {
        postOrderTraversal(this.root);
        System.out.println();
    }

    /**
     * Determine the minimum value in the tree.
     * Solution derived from: Ch 12 Binary Search Trees PTT, slide 15.
     * 
     * @return The minimum most node of the tree.
     */
    public BSTNode<T> getMinimum() {
        return minimum(this.root);
    }

    /**
     * Determine the maximum value in the tree.
     * Solution derived from CH 12 Binary Search Trees PPT, slide 15.
     * 
     * @return The maximum node of the tree.
     */
    public BSTNode<T> getMaxiumum() {
        return maximum(this.root);
    }

    /**
     * Iteratively search through the BST until a key has been found, or we get to the bottom of the tree.
     * Solution derived from: Ch 12 Binary Search Trees PPT, slide 14.
     * 
     * @param key The value to search for within the tree.
     * @return The node with matching value, or null if the key does not exist within the tree.
     */
    public BSTNode<T> search(T key) {
        return search(this.root, key);
    }

    /**
     * Determines the successor to a given node.
     * Solution derived from: Ch 12 Binary Search Trees PPT, slide 18.
     * 
     * @param searchRoot The node that is used to determine the successor.
     * @return The successor of the node.
     */
    public BSTNode<T> getSuccessor(BSTNode<T> searchRoot) {
        return successor(searchRoot);
    }

    /**
     * Determines the predecessor of a given node.
     * Solution derived from: Ch 12 Binary Search Trees PPT, slide 19.
     * 
     * @param searchRoot The node that is used to determine the predecessor.
     * @return The predecesor of the node.
     */
    public BSTNode<T> getPredecessor(BSTNode<T> searchRoot) {
        return predecessor(searchRoot);
    }

    /**
     * Inserts a new node into the BST.
     * Solution derived from: Ch 12 Binary Search Trees PPT, slide 21.
     * 
     * @param newNode The new node to insert into the tree.
     */
    public void insertKey(T key) {
        BSTNode<T> newNode = new BSTNode<>(key);
        insert(newNode);
    }

    /**
     * Delete the target node from the BST.
     * @param targetNode The node that will be deleted.
     */
    public void deleteNode(BSTNode<T> targetNode) {
        delete(targetNode);
    }

    private void preOrderTraversal(BSTNode<T> visitingNode) {
        if (visitingNode == null) {
            return;
        }

        System.out.print(visitingNode.getKey().toString() + " ");

        preOrderTraversal(visitingNode.getLeft());
        preOrderTraversal(visitingNode.getRight());
    }

    private void inOrderTraversal(BSTNode<T> visitingNode) {
        if (visitingNode == null) {
            return;
        }

        inOrderTraversal(visitingNode.getLeft());
        System.out.print(visitingNode.getKey().toString() + " ");
        inOrderTraversal(visitingNode.getRight());
    }

    private void postOrderTraversal(BSTNode<T> visitingNode) {
        if (visitingNode == null) {
            return;
        }

        postOrderTraversal(visitingNode.getLeft());
        postOrderTraversal(visitingNode.getRight());

        System.out.print(visitingNode.getKey().toString() + " ");
    }

    private BSTNode<T> minimum(BSTNode<T> searchRoot) {
        while (searchRoot.getLeft() != null) {
            searchRoot = searchRoot.getLeft();
        }

        return searchRoot;
    }

    private BSTNode<T> maximum(BSTNode<T> searchRoot) {
        while (searchRoot.getRight() != null) {
            searchRoot = searchRoot.getRight();
        }

        return searchRoot;
    }

    private BSTNode<T> search(BSTNode<T> searchRoot, T key) {
        if (this.root == null) {
            return null;
        }

        while (searchRoot != null && !searchRoot.getKey().equals(key)) {
            if (searchRoot.getKey().compareTo(key) > 0) {
                searchRoot = searchRoot.getLeft();
            }

            else {
                searchRoot = searchRoot.getRight();
            }
        }

        return searchRoot;
    }

    private BSTNode<T> successor(BSTNode<T> searchRoot) {
        if (searchRoot.getRight() != null) {
            return minimum(searchRoot.getRight());
        }

        while (!isRoot(searchRoot) && searchRoot.equals(searchRoot.getParent().getRight())) {
            searchRoot = searchRoot.getParent();
        }

        return searchRoot.getParent();
    }

    private BSTNode<T> predecessor(BSTNode<T> searchRoot) {
        if (searchRoot.getLeft() != null) {
            return maximum(searchRoot.getLeft());
        }

        while (!isRoot(searchRoot) && searchRoot.equals(searchRoot.getParent().getLeft())) {
            searchRoot = searchRoot.getParent();
        }

        return searchRoot.getParent();
    }

    private void insert(BSTNode<T> newNode) {
        this.size++;
        newNode.size = 1;

        if (this.root == null) {
            this.root = newNode;
            return;
        }

        BSTNode<T> iterator = this.root;
        BSTNode<T> oldParent = null;

        while (iterator != null) {
            oldParent = iterator;

            if (newNode.getKey().compareTo(iterator.getKey()) < 0) {
                iterator = iterator.getLeft();
            }

            else {
                iterator = iterator.getRight();
            }
        }

        newNode.setParent(oldParent);

        if (oldParent == null) {
            this.root = newNode;
        }

        else if (newNode.getKey().compareTo(oldParent.getKey()) < 0) {
            oldParent.setLeft(newNode);
        }

        else {
            oldParent.setRight(newNode);
        }
    }

    private void delete(BSTNode<T> targetNode) {
        this.size--;

        if (targetNode.getLeft() == null) {
            transplant(targetNode, targetNode.getRight());
            return;
        }

        else if (targetNode.getRight() == null) {
            transplant(targetNode, targetNode.getLeft());
            return;
        }

        BSTNode<T> successor = minimum(targetNode.getRight());

        if (!successor.getParent().equals(targetNode)) {
            transplant(successor, successor.getRight());

            successor.setRight(targetNode.getRight());
            successor.getRight().setParent(successor);
        }

        transplant(targetNode, successor);
        successor.setLeft(targetNode.getLeft());
        successor.getLeft().setParent(successor);
    }

    /**
     * A helper function with "transplants" one subtree into another.
     * Solution derived from: Ch 12 Binary Search Trees PPT, slide 30.
     * 
     * @param old 
     * @param transplant 
     */
    private void transplant(BSTNode<T> old, BSTNode<T> transplant) {
        if (isRoot(old)) {
            this.root = transplant;
        }

        else if (old == old.getParent().getLeft()) {
            old.getParent().setLeft(transplant);
        }

        else {
            old.getParent().setRight(transplant);
        }

        if (transplant != null) {
            transplant.setParent(old.getParent());
        }
    }

    /**
     * A QOL function which determines if a node is the root of the BST.
     * @param node The node to test.
     * @return True if the node is root, false if not.
     */
    private Boolean isRoot(BSTNode<T> node) {
        return node.getParent() == null;
    }
}
