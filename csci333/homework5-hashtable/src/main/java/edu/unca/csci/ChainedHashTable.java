package edu.unca.csci;

import java.util.Iterator;
import java.util.LinkedList;

public class ChainedHashTable<T> {
    LinkedList<Entry<Integer, T>>[] store;   
    int storeSize;

    public ChainedHashTable(int inputCount) {
        // The size of the store will be the first power of 2 larger than inputCount.
        storeSize = (int)Math.pow(2, Math.ceil(Math.log(inputCount) / Math.log(2)));
        
        // Create the data store with size computed above.
        store = new LinkedList[storeSize];
    }
    
    public void insert(Integer key, T value) {
        // Determine where in the data store this value will go.
        int index = hash(key);

        // Create our new entry.
        Entry<Integer, T> entry = new Entry<Integer, T>(key, value, index);
        
        // If the value at this index is NOT null, it needs to be added onto the LinkedList element.
        if (store[index] != null) {
            store[index].add(0, entry); // Add to the HEAD of the LinkedList.
            
            return;
        }
        
        // There is no value at this index, so we go ahead and initialize a new LinkedList and add the value.
        store[index] = new LinkedList<Entry<Integer, T>>();
        store[index].add(entry);
    }
    
    public void delete(Integer key) {
        // Determine where in the data store this value exists.
        int index = hash(key);
        
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
        Iterator<Entry<Integer, T>> iter = store[index].descendingIterator();
        int count = 0;

        while (iter.hasNext()) {
            Entry<Integer, T> next = iter.next();

            if (next.key == key) {
                store[index].remove(count);

                return;
            }

            count++;
        }
    }
    
    public T search(Integer key) {
        // Determine where in the data store this value exists.
        int index = hash(key);
        
        // If the index is null, we don't have anything to do. 
        if (store[index] == null || store[index].size() == 0) {
            return null;
        }
        
        // Use the built-in get function to return the first occurence that equals this value.
        Iterator<Entry<Integer, T>> iter = store[index].descendingIterator();
        Entry<Integer, T> next;

        while (iter.hasNext()) {
            next = iter.next();

            if (next.key == key) {
                return next.value;
            }
        }

        return null;
    }
    
    public String toString() {
        String out = "";
        for (int i = 0; i < storeSize; i++) {
            if (store[i] == null) {
                continue;
            }

            out += i + ":";

            Iterator<Entry<Integer, T>> iter = store[i].descendingIterator();
            while (iter.hasNext()) {
                Entry<Integer, T> next = iter.next();
                out += "[k=" + next.key + "; v=" + next.value + "] ";
            }

            out += " ";
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
