package edu.unca.csci;

/**
 * Ethan Green
 * CSCI 333 - Homework 7 - DFS
 * 
 * This class contains a boolean matrix that describes the edges of a graph, as well as 
 * a Depth-First-Search algorithm which will use it.
 */
public class Graph {
    private final int COLOR_WHITE = 0;
    private final int COLOR_GRAY = 1;
    private final int COLOR_BLACK = 2;

    private int nodeCount;
    private int time;
    private Boolean[][] edges;
    private Node[] nodes;

    public Graph(Boolean[][] edges) {
        this.nodeCount = edges.length;
        this.time = 0;
        this.edges = edges;
        this.nodes = new Node[nodeCount];

        for (int i = 0; i < nodeCount; i++) {
            this.nodes[i] = new Node(i);
        }
    }

    public void depthFirstSearch() {
        for (int i = 0; i < this.nodeCount; i++) {
            if (this.nodes[i].getColor() != COLOR_WHITE) {
                continue;
            }

            dfsVisit(this.nodes[i]);
        }
    }

    @Override
    public String toString() {
        String out = "Nodes:\n";

        for (int i = 0; i < nodeCount; i++) {
            out += this.nodes[i].toString();
        }

        out += "\nEdge matrix:\n";

        for (int x = 0; x < this.edges.length; x++) {
            for (int y = 0; y < this.edges[x].length; y++) {
                out += edges[x][y] + " ";
            }

            out += "\n";
        }

        return out;
    }

    private void dfsVisit(Node node) {
        this.time++;

        node.setD(time);
        node.setColor(COLOR_GRAY);

        for (int i = 0; i < this.edges[node.getName()].length; i++) {
            if (!this.edges[node.getName()][i]) {
                continue;
            }

            if (this.nodes[i].getColor() == 0) {
                this.nodes[i].setParent(node.getName());
                dfsVisit(nodes[i]);
            }
        }

        node.setColor(COLOR_BLACK);
        this.time++;
        node.setF(time);
    }
}
