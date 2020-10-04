package edu.unca.csci;

public class OpenAddressedHashTable<T> {
    Entry<Integer, T>[] store;
    int storeSize;

    public OpenAddressedHashTable(int inputCount) {
        // The size of the store will be the first power of 2 larger than inputCount.
        storeSize = (int)Math.pow(2, Math.ceil(Math.log(inputCount) / Math.log(2)));
        
        // Create the data store with size computed above.
        store = new Entry[storeSize];
    }

    public void insert(Integer key, T value) {
        // Compute the index of which to insert the element.
        int index = hash(key);

        // Create a new entry with key and value arg. 
        Entry<Integer, T> entry = new Entry<Integer, T>(key, value, index);

        // If the entry at this index is null, we just set it to the new entry and return.
        if (store[index] == null || store[index].key == key) {
            store[index] = entry;

            return;
        }

        // Since there IS a non-null entry at this index, we need to iterate from the index + 1 to the end of the store to find the 
        // closest empty location.
        for (int i = index + 1; i < storeSize; i++) {

            // We've found an empty index, save the new entry here.
            if (store[i] == null || store[i].key == key) {
                store[i] = entry;
                return;
            }
        }

        // If we make it this far we can assume that something broke, or we ran out of space in the store.
    }

    public void delete(Integer key) {
        
        // First, we need to delete the entry with the key.
        int index = hash(key);

        store[index] = null;

        // We then need to search down the store to the end. If we find an entry with the same hash, we need to move it up.
        for (int i = index + 1; i < storeSize; i++) {
            if (store[i] == null) {
                continue;
            }

            if (store[i].hash == index) {
                store[index] = store[i];
                store[i] = null;

                return;
            }
        }
    }

    public T search(Integer key) {
        int hash = hash(key);

        return (store[hash] == null) ? null : store[hash].value;
    }

    public String toString() {
        String out = "";
        for (int i = 0; i < storeSize; i++) {
            if (store[i] == null) {
                continue;
            }

            out += "" + i + ":[k=" + store[i].key + "; v=" + store[i].value + "] ";
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
