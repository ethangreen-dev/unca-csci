package edu.unca.csci;

import java.util.Arrays;

public class App 
{
    public static void main(String[] args)
    {
        test(new Integer[] { 8781, 7649, 9291, 8668, 5718, 8490, 3726, 4558, 7404, 5322 });
        test(new Integer[] { 5323, 7637, 7683, 9085, 4765, 9104, 6281, -54, 355, 620 });
        test(new Integer[] { 108, 9460, 6542, 2703, 607, 184, 7412, 8850, 8384, 504 });
        test(new String[] { "KEpJdU","4Eerh5","6lQoyO","sFJc5K","l7Xgbd","lwCUXS","pL2miG","ZSm1uI","plEn8q","Wx7Ma9" });
        test(new String[] { "2EA5OX","1Ugn0d","DbZEU7","HxFQuS","mcMM96","JOMRmx","X1oUGr","phF8CN","3x80zs","uGsqFP" });
        test(new String[] { "oXRZRRkxwo","GfHZAziMC3","lVZy4KhlMF","0f8NQqK3nQ","JP3O5rGJiH","FulNyJXvuL","TV8X02pERT","VG64lMRQOT","aatb1a50vJ","yFYLkLIfyO" });

        
    }
    
    private static <T extends Comparable<T>> void test(T[] array) {
        T[] backup = array.clone();
        Quicksort sort = new Quicksort();

        System.out.println("unsorted:\t\t" + Arrays.toString(array));
        
        sort.quicksort(array);
        System.out.println("quicksort:\t\t" + Arrays.toString(array));
        
        sort.randomizedQuicksort(backup);
        System.out.println("randomized quicksort:   " + Arrays.toString(backup));
        
        System.out.println();
    }
}
