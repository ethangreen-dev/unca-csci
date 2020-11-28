package edu.unca.csci;

public class BSTNode<T extends Comparable<T>> {
    private BSTNode<T> parent;
    private BSTNode<T> left;
    private BSTNode<T> right;

    private T key;

    public int size;

    public BSTNode(T key) {
        this.left = null;
        this.right = null;

        this.key = key;

        this.size = 0;
    }

    public void setParent(BSTNode<T> parent) {
        this.parent = parent;
    }

    public void setLeft(BSTNode<T> left) {
        this.left = left;
    }

    public void setRight(BSTNode<T> right) {
        this.right = right;
    }

    public void setKey(T key) {
        this.key = key;
    }

    public BSTNode<T> getParent() {
        return this.parent;
    }

    public BSTNode<T> getLeft() {
        return this.left;
    }

    public BSTNode<T> getRight() {
        return this.right;
    }

    public T getKey() {
        return this.key;
    }
}
