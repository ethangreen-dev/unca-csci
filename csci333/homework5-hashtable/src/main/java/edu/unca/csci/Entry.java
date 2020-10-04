package edu.unca.csci;

public class Entry<T, E> {
    T key;
    E value;
    int hash;

    public Entry(T key, E value, int hash) {
        this.key = key;
        this.value = value;
        this.hash = hash;
    }
}
