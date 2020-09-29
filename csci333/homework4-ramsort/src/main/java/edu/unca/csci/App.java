package edu.unca.csci;

import java.util.Arrays;

public class App 
{
    public static void main( String[] args )
    {
        System.out.println( "Hello World!" );
        
        test(new int[] { 1, 4, 1, 2, 2, 4, 6, 7, 9 }, 9, 2);
        test(new int[] { 7, 10, 4, 3, 20, 15 }, 20, 2);
        test(new int[] { 7, 10, 4, 3, 20, 15 }, 20, 4);
        test(new int[] { 1, 4, 9, 100, 122, 999, 10 }, 999, 3);
        test(new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, 10, 7);
    }
    
    private static void test(int[] inArray, int largestValue, int k) {
        int[] sortedArray = new int[inArray.length];

        RAMSortSelect sort = new RAMSortSelect();
        sort.countingSort(inArray, sortedArray, largestValue);

        System.out.println("unsorted:  " + Arrays.toString(inArray));
        System.out.println("sorted:    " + Arrays.toString(sortedArray));

        System.out.println(k + " smallest value: " + sort.quickSelect(inArray, k));
        
        System.out.println();
    }
}
