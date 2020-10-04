package edu.unca.csci;

import java.util.Random;

public class App 
{
    public static void main( String[] args )
    {
        System.out.println("========== TESTING CHAINED HASH TABLE =========");
        testChained();

        System.out.println("\n\n========== TESTING OPEN ADDRESSED HASH TABLE =========");
        testOpen();

        System.out.println();
    }
    
    private static void testChained() {
        // Generate 100 random values and add them to the hashtable.
        Random gen = new Random();
        ChainedHashTable<Integer> hashTable = new ChainedHashTable<Integer>(100);
        final int bounds = 100;
        
        for (int i = 0; i < bounds; i++) {
            int ranVal = gen.nextInt(bounds);
            hashTable.insert(ranVal, ranVal);
        }

        System.out.println(hashTable.toString());
        System.out.println("\n\t===== DELETING 20 RANDOM VALUES =====");

        // Remove 20 random numbers.
        for (int i = 0; i < 20; i++) {
            int ranVal = gen.nextInt(bounds);

            hashTable.delete(ranVal);
        }

        System.out.println(hashTable.toString());
        System.out.println("\n\t===== SEARCHING FOR 20 RANDOM VALUES =====");

        // Search for 20 random numbers, return the results.
        for (int i = 0; i < 20; i++) {
            int ranVal = gen.nextInt(bounds);
            Integer value = hashTable.search(ranVal);

            if (value == null) {
                System.out.print("[" + ranVal + ":DNE] ");

                continue;
            }

            System.out.print("[" + ranVal + ":v=" + value + "] ");
        }
    }

    private static void testOpen() {
        // Generate 100 random values and add them to the hashtable.
        Random gen = new Random();
        OpenAddressedHashTable<Integer> hashTable = new OpenAddressedHashTable<Integer>(100);
        final int bounds = 100;
        
        for (int i = 0; i < bounds; i++) {
            int ranVal = gen.nextInt(bounds);
            hashTable.insert(ranVal, ranVal);
        }
        
        // Delete 20 random values.
        System.out.println(hashTable.toString());
        System.out.println("\n\t===== DELETING 20 RANDOM VALUES =====");

        // Remove 20 random numbers.
        for (int i = 0; i < 20; i++) {
            int ranVal = gen.nextInt(bounds);

            hashTable.delete(ranVal);
        }

        System.out.println(hashTable.toString());
        System.out.println("\n\t===== SEARCHING FOR 20 RANDOM VALUES =====");

        // Search for 20 random numbers, return the results.
        for (int i = 0; i < 20; i++) {
            int ranVal = gen.nextInt(bounds);
            Integer value = hashTable.search(ranVal);

            if (value == null) {
                System.out.print("[" + ranVal + ":DNE] ");

                continue;
            }

            System.out.print("[" + ranVal + ":v=" + value + "] ");
        }
    }
}
