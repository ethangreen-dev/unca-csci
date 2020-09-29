package edu.unca.csci;

import java.util.Arrays;
import java.util.Random;

/**
 * Ethan Green - CSCI 333, 9/15/2020
 * 
 * A Random Quick Select and Counting Sort implementation.
 */
public class RAMSortSelect {
    /**
     * A counting sort algorithm.
     * @param unsortedArray An array to sort.
     * @param sortedArray The array in its sorted form.
     * @param largestValue The largest value in the array.
     */
    public void countingSort(int[] unsortedArray, int[] sortedArray, int largestValue) {
        // First, we need to create a frequency list of largestValue size.
        int[] frequency = new int[largestValue + 1];
        
        // Fill the frequencyList step by step as we move up the unsortedArray.
        for (int i = 0; i < unsortedArray.length; i++) {
            frequency[unsortedArray[i]]++;
        }
        
        // Now we coalesce the frequencies.
        for (int i = 1; i < largestValue + 1; i++) {
            frequency[i] += frequency[i - 1];
        }
        
        // Finally, iterate back through the unsorted list, inserting it into the frequency - 1 index of the sorted array.
        for (int i = 0; i < unsortedArray.length; i++) {
            frequency[unsortedArray[i]]--;
            sortedArray[frequency[unsortedArray[i]]] = unsortedArray[i];
        }
    }
    
    /**
     * A random quick select implementation based heavily on previously written quicksort code.
     * @param inputArray The array to search within.
     * @param k The k^th smallest value to find.
     * @return The k^th smallest value.
     */
    public int quickSelect(int[] inputArray, int k) {
        int[] inputArrayCopy = Arrays.copyOf(inputArray, inputArray.length);
        k--;
        
        return quickSelect(inputArrayCopy, 0, inputArrayCopy.length - 1, k);
    }
    
    private int quickSelect(int[] inputArray, int lowerIndex, int upperIndex, int k) {
        // If the lower and upper indexes are the same, we know the value we're searching for is in the lower.
        if (lowerIndex == upperIndex) {
            return inputArray[lowerIndex];
        }
        
        // Swap our values heres.
        Random random = new Random();
        int randomIndex = random.nextInt(upperIndex - lowerIndex);
        swap(inputArray, randomIndex + lowerIndex, upperIndex);
        
        // Run a quicksort partition to determine the index of our pivot.
        int pivot = partition(inputArray, lowerIndex, upperIndex);
        
        // If k is equal to our pivot, we know that the value is in the inputArray at index k.
        if (k == pivot) {
            return inputArray[k];
        }
        
        // If k is less than the pivot, we know the value is in the left region.
        if (k < pivot) {
            return quickSelect(inputArray, lowerIndex, upperIndex - 1, k);
        }
        
        // If k is greater than the pivot, we know the value is in the right region.
        if (k > pivot) {
            return quickSelect(inputArray, lowerIndex + 1, upperIndex, k);
        }
        
        return 0;
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
    private int partition(int[] array, int lowerIndex, int upperIndex) {
        // The upper is what we'll use to step down the array. 
        // The lower will step up. 
        int upper = upperIndex;
        int lower = lowerIndex;
        
        // Pick our pivot from the upper index.
        int pivot = array[upperIndex];
        
        // Step the upper down and the lower up until they meet each other.
        while (upper != lower) {
            if (pivot < array[lower]) {
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
    private void swap(int[] array, int firstIndex, int secondIndex) {
        int temp = array[firstIndex];
        array[firstIndex] = array[secondIndex];
        array[secondIndex] = temp;
    }
}
