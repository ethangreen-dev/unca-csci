package edu.unca.csci;

import java.util.Random;

/**
 * Homework 3 - Quicksort
 * 
 * A Quicksort implementation by Ethan Green for CSCI 333 - Algorithms and Data Structures
 * 09/02/2020 (late)
 * 
 * @param <T> A type which extends Comparable<T>
 */
public class Quicksort<T extends Comparable<T>> {
    /**
     * A Quicksort implementation on a T[] array. 
     * Note that T must implement Comparable<T> for this sorting function to work.
     * 
     * WARNING: This implementation may fail on large (massive) input arrays as it is recursive. 
     * Stack overflows be warned.
     * 
     * @param array The array to sort.
     */
    public void quicksort(T[] array) {
        quicksort(array, 0, array.length - 1, false);
    }
    
    /**
     * A randomized Quicksort implementation on a T[] array.
     * Note that T must implement Comparable<T> for this sorting function to work.
     * 
     * Unlike quicksort(), this function chooses a random pivot each iteration.
     * 
     * WARNING: This implementation may fail on large (massive) input arrays as it is recursive.
     * Stack overflows be warned.
     * 
     * @param array The array to sort.
     */
    public void randomizedQuicksort(T[] array) {
        quicksort(array, 0, array.length - 1, true);
    }
    
    /**
     * A private, recursive version of quicksort. 
     * 
     * @param array The array to sort.
     * @param lowerIndex The upper region index to be sorted.
     * @param upperIndex The lower region index to be sorted.
     * @param isRandom Whether the pivot selection should be random or not.
     */
    private void quicksort(T[] array, int lowerIndex, int upperIndex, boolean isRandom) {
        // If we have a random quicksort, swap the upperIndex with a random value from the range 
        // lowerIndex (i) - upperIndex (x)
        if (isRandom && lowerIndex != upperIndex) {
            Random random = new Random();
            int randomIndex = random.nextInt(upperIndex - lowerIndex);
            
            swap(array, randomIndex + lowerIndex, upperIndex);
        }
        
        // All elements to the left and right of the pivot are in the correct positions.
        int partition = partition(array, lowerIndex, upperIndex);

        // Once we've partitioned a region of two elements we know they're in the right locations,
        // so we short-circuit here.
        if (upperIndex - lowerIndex <= 1) {
            return;
        }
        
        // Check to make sure we actually have elements to the left of the partitioning point.
        if (lowerIndex != partition) {

            // Recurse from the lower index to the element preceding the partition.
            quicksort(array, lowerIndex, partition - 1, isRandom);
        }
        
        // Make sure we have elements to the right of the paritioning point.
        if (upperIndex != partition) {

            // Recurse from the element following the partition to the end.
            quicksort(array, partition + 1, upperIndex, isRandom);
        }
    }
    
    /**
     * Will return the element at which the array needs to be partitioned at. Note that this element is NOT inclusive. 
     * The array is expected to the partitioned +-1 index from this point.
     * 
     * @param array The array that is being sorted.
     * @param lowerIndex The current lower bound of the array region.
     * @param upperIndex The current upper bound of the array region.
     * @param pivotIndex The last index of the pivot.
     * @return An index which +-1 will bisect the array into two regions.
     */
    private int partition(T[] array, int lowerIndex, int upperIndex) {
        // The upper is what we'll use to step down the array. 
        // The lower will step up. 
        int upper = upperIndex;
        int lower = lowerIndex;
        
        // Pick our pivot from the upper index.
        T pivot = array[upperIndex];
        
        // Step the upper down and the lower up until they meet each other.
        while (upper != lower) {
            if (pivot.compareTo(array[lower]) < 0) {
                // Swap index upper with the preceding index.
                swap(array, upper - 1, upper);
                
                // If the lower and upper are only a single index apart, we just need the above swap.
                if (upper - lower > 1) {
                    // Swap upper and lower.
                    swap(array, lower, upper);
                }
                
                // Decrement the upper.
                upper--;
                
                continue;
            }
            
            // The element at the lower index is in the correct position, so we just increment.
            lower++;
        }
        
        // At this point, the pivot is now in the correct position in the array.
        return upper;
    }
    
    /**
     * A helper method to swap the values of two indexes in an array.
     * 
     * @param array The array to swap values from.
     * @param firstIndex The first index.
     * @param secondIndex The second index.
     */
    private void swap(T[] array, int firstIndex, int secondIndex) {
        T temp = array[firstIndex];
        array[firstIndex] = array[secondIndex];
        array[secondIndex] = temp;
    }
}
