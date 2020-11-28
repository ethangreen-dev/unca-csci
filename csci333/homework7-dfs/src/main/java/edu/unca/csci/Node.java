package edu.unca.csci;

/**
 * Ethan Green
 * CSCI 333 - Homework 7 - DFS
 * 
 * This class is a representation of an individual node on a graph.
 */
public class Node {
    private int name;
    private int parent;
    private int d;
    private int f;
    private int color;

    public Node(int name) {
        this.name = name;
        this.parent = -1;
        this.d = 0;
        this.f = 0;
        this.color = 0;
    }

    public int getName() {
        return this.name;
    }

    public int getParent() {
        return this.parent;
    }

    public void setParent(int parent) {
        this.parent = parent;
    }

    public int getD() {
        return this.d;
    }

    public void setD(int d) {
        this.d = d;
    }

    public int getF() {
        return this.f;
    }

    public void setF(int f) {
        this.f = f;
    }

    public int getColor() {
        return this.color;
    }

    public void setColor(int color) {
        this.color = color;
    }

    @Override
    public String toString() {
        return String.format("Name: %d, Parent: %d, Color: %d, D: %d, Time: %d%n", this.name, this.parent, this.color, this.d, this.f);
    }
}
