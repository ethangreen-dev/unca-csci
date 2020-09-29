package edu.unca.csci;

import java.util.LinkedList;

public class ChainedHashTable {
    LinkedList<Integer>[] store;   
    int storeSize;

    public ChainedHashTable(int inputCount) {
        // The size of the store will be the first power of 2 larger than inputCount.
        storeSize = (int)Math.pow(2, Math.ceil(Math.log(inputCount) / Math.log(2)));
        
        // Create the data store with size computed above.
        store = new LinkedList[storeSize];
    }
    
    public void insert(Integer value) {
        // Determine where in the data store this value will go.
        int index = hash(value);
        
        // If the value at this index is NOT null, it needs to be added onto the LinkedList element.
        if (store[index] != null) {
            store[index].add(0, value); // Add to the HEAD of the LinkedList.
            
            return;
        }
        
        // There is no value at this index, so we go ahead and initialize a new LinkedList and add the value.
        store[index] = new LinkedList<Integer>();
        store[index].add(value);
    }
    
    public void delete(Integer value) {
        // Determine where in the data store this value exists.
        int index = hash(value);
        
        // If the index is null, we don't have anything to do.
        if (store[index] == null) {
            return;
        }
        
        // If the LinkedList contains no elements after this removal, set it to null.
        if (store[index].size() == 1) {
            store[index].remove();
            store[index] = null;
            
            return;
        }

        // If the index contains a non-null LinkedList node, walk down. If we find our value, delete it from the linked list. 
        store[index].removeFirstOccurrence(value);
    }
    
    public Integer search(Integer value) {
        // Determine where in the data store this value exists.
        int index = hash(value);
        
        // If the index is null, we don't have anything to do. 
        if (store[index] == null || store[index].size() == 0) {
            return null;
        }
        
        // Use the built-in get function to return the first occurence that equals this value.
        return store[index].get(value);
    }
    
    public String toString() {
        String out = "";

        for (int i = 0; i < storeSize; i++) {

            // If there is nothing at the index. 
            if (store[i] == null || store[i].size() == 0) {
                continue;
            }

            out += i + ":" + store[i].toString() + " ";
        }
        
        return out;
    }
    
    private int hash(Integer value) {
        final double a = 0.6180339887; // As recommended by Donald Knuth, the Golden Ratio.
        final double m = storeSize;
        
        // Multiply the value by a and take the fractional part. 
        double frac = (value * a) - Math.floor(value * a);
        
        // Take this fractional part by m and floor it.
        double index = Math.floor(m * frac);
        
        return (int)index;
    }
}
