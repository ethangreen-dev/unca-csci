package edu.unca.csci;

public class DepthFirstSearch {
    public static void main(String[] args) {
        Boolean[][] matrix = {
            {false, true, false, true, false, true, false},
            {true, false, true, false, true, false, true},
            {false, true, false, true, false, true, false},
            {false, true, true, false, true, false, false},
            {true, false, false, true, false, true, true},
            {true, true, true, false, true, false, false},
            {false, true, false, true, true, true, false}
        };

        Graph graph = new Graph(matrix);
        graph.depthFirstSearch();
        System.out.println(graph.toString());

        matrix = new Boolean[][]{
            {true, true, false, true, false, false},
            {false, true, true, false, true, true},
            {true, true, true, true, true, true},
            {false, false, false, true, false, false},
            {false, false, false, true, false, false},
            {false, true, true, false, true, true}
        };
        graph = new Graph(matrix);
        graph.depthFirstSearch();
        System.out.println(graph.toString());

        matrix = new Boolean[][] {
            {true, false, true},
            {false, true, false},
            {true, false, true}
        };
        graph = new Graph(matrix);
        graph.depthFirstSearch();
        System.out.println(graph.toString());
    }
}
