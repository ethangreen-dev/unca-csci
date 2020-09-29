package edu.unca.csci;

import java.util.Random;

public class App 
{
    public static void main( String[] args )
    {
        System.out.println( "Hello World!" );
        test();
    }
    
    private static void test() {
        // Generate 100 random values and add them to the hashtable.
        Random gen = new Random();
        ChainedHashTable hashTable = new ChainedHashTable(100);
        final int bounds = 100;
        
        for (int i = 0; i < bounds; i++) {
            hashTable.insert(gen.nextInt(bounds));
        }
        
        // Remove all instances of a random number.
        
        System.out.println(hashTable.toString());
    }
}
